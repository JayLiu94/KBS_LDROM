/*-----------------------------------------------------------------------------------------------------------
 *  Nuvoton Technology Corporation Confidential
 *
 *  Copyright (c) 2018-2022 by Nuvoton Technology Corporation
 *  All rights reserved
 *
 *<<<----------------------------------------------------------------------------------------------------->>>
 * Filename: task_kbscan.c
 *      The keyboard matrix scan task handlers
 *
 * Project:
 *            Nuvoton Embedded Controller Firmware
 *---------------------------------------------------------------------------------------------------------*/
#include "prj_config.h"


/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/

#define I2C_SLAVE_CH        UI2C1
#define I2C_SLAVE_CH_IRQ    USCI1_IRQn

#define I2C_Slave_Addr_Default  0x15
#define I2C_RX_BUF_SIZE         128
#define I2C_TX_BUF_SIZE         128

#define evtI2CWrite         (1 << 0)
#define evtI2CRead          (1 << 1)
#define evtI2CWriteRead     (1 << 2)
#define evtI2CNAck          (1 << 3)
#define evtI2CStop          (1 << 4)
#define evtI2CError         (1 << 5)
#define evtI2CArbLose       (1 << 6)
#define evtI2CTimeout       (1 << 7)


static uint8_t I2C_Slave_Addr;
static uint8_t I2cSlvRxData[I2C_RX_BUF_SIZE];
static uint8_t I2cSlvTxData[I2C_TX_BUF_SIZE];
static volatile uint16_t I2cSlvRxCnt;
static volatile uint16_t I2cSlvTxCnt;
static volatile uint16_t I2cSlvTxIndex;
static volatile uint8_t I2cSlvAddr;

volatile enum UI2C_SLAVE_EVENT I2C_SlvCtrlState;

static volatile uint32_t TaskI2CSlvEvtGrp;

static UI2C_STOP_FUNC          I2C_StopCallback = NULL;
static UI2C_WRITE_FUNC         I2C_WriteCallback = NULL;
static UI2C_WRITE_READ_FUNC    I2C_WriteReadCallback = NULL;
static UI2C_READ_FUNC          I2C_ReadCallback = NULL;

void I2C_Write_Hanelder(void);
void I2C_Write_Read_Handler(void);
void I2C_Read_Handler(void);
void I2C_Slave_Send_Data(void);
void I2C_Stop_Handler(void);
void I2C_NAck_Handler(void);
void I2C_ArbLose_Handler(void);
void I2C_Error_Handler(void);
void I2C_Timeout_Handler(void);

uint32_t TaskI2CSlv_GetEventBits(void);
void TaskI2CSlv_SetEventBits(uint32_t uxBitsToSet);
void TaskI2CSlv_ClrEventBits(uint32_t uxBitsToSet);


void I2C_StopCallback_Config(UI2C_STOP_FUNC callback)
{
    I2C_StopCallback = callback;
}

void I2C_WriteCallback_Config(UI2C_WRITE_FUNC callback)
{
    I2C_WriteCallback = callback;
}

void I2C_WriteReadCallback_Config(UI2C_WRITE_READ_FUNC callback)
{
    I2C_WriteReadCallback = callback;
}

void I2C_ReadCallback_Config(UI2C_READ_FUNC callback)
{
    I2C_ReadCallback = callback;
}

void I2c_module_init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    TaskI2CSlvEvtGrp =0ul;

    I2C_Slave_Addr = I2C_Slave_Addr_Default;

    /* Enable USCI1 IP clock */
    CLK_EnableModuleClock(USCI1_MODULE);

    /* Reset IP USCI1 */
    SYS_ResetModule(USCI1_RST);
  
    /* Open UI2C1: 1 MHz */
    UI2C_Open(I2C_SLAVE_CH, 1000000);

    /* Set GPE multi-function pins for USCI I2C1 GPE5(SCL) and GPE6(SDA) */
    SYS->GPE_MFP = (SYS->GPE_MFP & ~(SYS_GPE_MFP_PE5MFP_Msk | SYS_GPE_MFP_PE6MFP_Msk)) | \
                   (SYS_GPE_MFP_PE5_I2C1_SCL | SYS_GPE_MFP_PE6_I2C1_SDA);

    /* Unlock protected registers */
    SYS_LockReg();

    /* Set USCI_I2C1 Slave Addresses */
    UI2C_SetSlaveAddr(I2C_SLAVE_CH, 0, I2C_Slave_Addr, UI2C_GCMODE_DISABLE);
    UI2C_SetSlaveAddrMask(I2C_SLAVE_CH, 0, 0x00);

    UI2C_ENABLE_PROT_INT(I2C_SLAVE_CH, (UI2C_PROTIEN_ACKIEN_Msk | UI2C_PROTIEN_NACKIEN_Msk | \
                                        UI2C_PROTIEN_STORIEN_Msk | UI2C_PROTIEN_STARIEN_Msk));
    NVIC_EnableIRQ(I2C_SLAVE_CH_IRQ);

    I2C_SlvCtrlState = SALVE_IDLE;
    I2cSlvRxCnt = 0;
    I2cSlvTxCnt = 0;
    I2cSlvTxIndex = 0;

    /* Assert ACK control. */
    UI2C_CLR_PROT_INT_FLAG(I2C_SLAVE_CH, (UI2C_PROTSTS_STARIF_Msk | UI2C_PROTSTS_ACKIF_Msk   | \
                                          UI2C_PROTSTS_NACKIF_Msk | UI2C_PROTSTS_STORIF_Msk  | \
                                          UI2C_PROTSTS_TOIF_Msk   | UI2C_PROTSTS_ARBLOIF_Msk | \
                                          UI2C_PROTSTS_ERRIF_Msk)); 
    UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
}

void USCI1_IRQHandler(void)
{
    volatile uint32_t u32Status;
    uint32_t temp;

    u32Status = UI2C_GET_PROT_STATUS(I2C_SLAVE_CH);

    if((u32Status & UI2C_PROTSTS_STARIF_Msk) == UI2C_PROTSTS_STARIF_Msk) 
    {
        /* Clear START INT Flag */
        UI2C_CLR_PROT_INT_FLAG(I2C_SLAVE_CH, UI2C_PROTSTS_STARIF_Msk);
        I2C_SlvCtrlState = SALVE_REPEAT_START;
        UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
    } 
    else if((u32Status & UI2C_PROTSTS_ACKIF_Msk) == UI2C_PROTSTS_ACKIF_Msk) 
    {
        /* Clear ACK INT Flag */
        UI2C_CLR_PROT_INT_FLAG(I2C_SLAVE_CH, UI2C_PROTSTS_ACKIF_Msk);  

        if(I2C_SlvCtrlState == SALVE_IDLE)
        {
            I2cSlvAddr = (unsigned char) UI2C_GET_DATA(I2C_SLAVE_CH);

            I2cSlvRxCnt = 0;
            I2cSlvTxCnt = 0;
            I2cSlvTxIndex = 0;  

            if((u32Status & UI2C_PROTSTS_SLAREAD_Msk) == UI2C_PROTSTS_SLAREAD_Msk) 
            {   
                /* Own SLA+R has been receive; ACK has been return */
                I2C_SlvCtrlState = SLAVE_TRANSMIT_DATA;

                /* prepare data that will send to host */
                //I2C_Read_Handler();
                TaskI2CSlv_SetEventBits(evtI2CRead);
            } 
            else 
            {
                /* Own SLA+W has been receive; ACK has been return */
                I2C_SlvCtrlState = SLAVE_RECEIVE_DATA;
                UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
            }
        } 
        else if((I2C_SlvCtrlState == SALVE_REPEAT_START))
        {
            I2cSlvAddr = (unsigned char) UI2C_GET_DATA(I2C_SLAVE_CH);

            if((u32Status & UI2C_PROTSTS_SLAREAD_Msk) == UI2C_PROTSTS_SLAREAD_Msk) 
            {   
                /* Own SLA+R has been receive; ACK has been return */
                I2C_SlvCtrlState = SLAVE_TRANSMIT_DATA;
                I2cSlvTxIndex = 0;

                /* prepare data that will send to host */
                if(I2cSlvRxCnt > 0)
                {
                    //I2C_Write_Read_Handler();
                    TaskI2CSlv_SetEventBits(evtI2CWriteRead);
                }
                else
                {
                    //I2C_Read_Handler();
                    TaskI2CSlv_SetEventBits(evtI2CRead);
                }
            } 
            else 
            {
                /* handle the previous host write command and data */
                if(I2cSlvRxCnt > 0)
                {
                    //I2C_Write_Hanelder();
                    TaskI2CSlv_SetEventBits(evtI2CWrite);
                }
                else
                {
                    /* Own SLA+W has been receive; ACK has been return */
                    I2C_SlvCtrlState = SLAVE_RECEIVE_DATA;
                    UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
                }
            }
        } 
        else if(I2C_SlvCtrlState == SLAVE_RECEIVE_DATA) 
        {
            /* Data has been received; ACK has been returned*/
            if(I2cSlvRxCnt < I2C_RX_BUF_SIZE)
            {
                I2cSlvRxData[I2cSlvRxCnt] = (unsigned char) UI2C_GET_DATA(I2C_SLAVE_CH);
                I2cSlvRxCnt++;
            }
            else
            {
                /* the recive buffer was full, dummy read the data */
                temp = (unsigned char)UI2C_GET_DATA(I2C_SLAVE_CH);
            }

            UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
        }
        else if(I2C_SlvCtrlState == SLAVE_TRANSMIT_DATA) 
        {
            /* data has received by master */
            I2C_Slave_Send_Data();
        }
    } 
    else if((u32Status & UI2C_PROTSTS_NACKIF_Msk) == UI2C_PROTSTS_NACKIF_Msk) 
    {   
        /* Data in TXDAT has been transmitted; NACK has been received */
        /* Clear NACK INT Flag */
        UI2C_CLR_PROT_INT_FLAG(I2C_SLAVE_CH, UI2C_PROTSTS_NACKIF_Msk); 
        I2C_SlvCtrlState = MASTERT_NACK;
        
        //I2C_NAck_Handler();
        TaskI2CSlv_SetEventBits(evtI2CNAck);
    } 
    else if((u32Status & UI2C_PROTSTS_STORIF_Msk) == UI2C_PROTSTS_STORIF_Msk) 
    {
        /* Clear STOP INT Flag */
        UI2C_CLR_PROT_INT_FLAG(I2C_SLAVE_CH, UI2C_PROTSTS_STORIF_Msk); 
        I2C_SlvCtrlState = BUS_STOP;

        //I2C_Stop_Handler();
        TaskI2CSlv_SetEventBits(evtI2CStop);
    }
    else if ((u32Status & UI2C_PROTSTS_TOIF_Msk) == UI2C_PROTSTS_TOIF_Msk) 
    {
        /* Clear USCI_I2C1 Timeout Flag */
        UI2C_CLR_PROT_INT_FLAG(I2C_SLAVE_CH, UI2C_PROTSTS_TOIF_Msk); 
        I2C_SlvCtrlState = BUS_TIMEOUT;

        //I2C_Timeout_Handler();
        TaskI2CSlv_SetEventBits(evtI2CTimeout);
    }
    else if ((u32Status & UI2C_PROTSTS_ARBLOIF_Msk) == UI2C_PROTSTS_ARBLOIF_Msk) 
    {
        I2C_SlvCtrlState = MASTER_ARBITRATION_LOST;
        UI2C_CLR_PROT_INT_FLAG(I2C_SLAVE_CH, UI2C_PROTSTS_ARBLOIF_Msk); 

        //I2C_ArbLose_Handler();
        TaskI2CSlv_SetEventBits(evtI2CArbLose);
    }
    else if ((u32Status & UI2C_PROTSTS_ERRIF_Msk) == UI2C_PROTSTS_ERRIF_Msk) 
    {
        I2C_SlvCtrlState = BUS_ERROR;
        UI2C_CLR_PROT_INT_FLAG(I2C_SLAVE_CH, UI2C_PROTSTS_ERRIF_Msk); 

        //I2C_Error_Handler();
        TaskI2CSlv_SetEventBits(evtI2CError);
    }
}

void I2C_Write_Hanelder(void)
{
    if(I2C_WriteCallback != NULL)
    {
        I2C_WriteCallback(I2cSlvRxCnt, I2cSlvRxData);
    }

    if(I2C_SlvCtrlState == SALVE_REPEAT_START)
    {
        I2cSlvRxCnt = 0;
        /* Own SLA+W has been receive; ACK has been return */
        I2C_SlvCtrlState = SLAVE_RECEIVE_DATA;
        UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
    }
}

void I2C_Slave_Send_Data(void)
{
    /* data has received by master */
    if((I2cSlvTxIndex < I2cSlvTxCnt) && (I2cSlvTxIndex < I2C_TX_BUF_SIZE))
    {
        UI2C_SET_DATA(I2C_SLAVE_CH, I2cSlvTxData[I2cSlvTxIndex]);
        I2cSlvTxIndex++;
    }
    else
    {
        /* return dummy data to master */
        UI2C_SET_DATA(I2C_SLAVE_CH, 0xFF);
    }

    UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
}

void I2C_Write_Read_Handler(void)
{
    if(I2C_WriteReadCallback != NULL)
    {
        I2cSlvTxCnt = I2C_WriteReadCallback(I2cSlvRxCnt, I2cSlvRxData, I2cSlvTxData);
    }

    I2cSlvRxCnt = 0;

    I2C_Slave_Send_Data();
}

void I2C_Read_Handler(void)
{
    if(I2C_ReadCallback != NULL)
    {
        I2cSlvTxCnt = I2C_ReadCallback(I2cSlvTxData);
    }

    I2C_Slave_Send_Data();
}

void I2C_Stop_Handler(void)
{
    /* handle the host write command and data */
    if(I2cSlvRxCnt > 0)
    {
        I2C_Write_Hanelder();
    }

    I2C_SlvCtrlState = SALVE_IDLE;
    I2cSlvRxCnt = 0;
    I2cSlvTxCnt = 0;
    I2cSlvTxIndex = 0;

    UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));

    if(I2C_StopCallback != NULL)
    {
        I2C_StopCallback();
    }
}

void I2C_NAck_Handler(void)
{
    UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
}

void I2C_ArbLose_Handler(void)
{
    I2C_SlvCtrlState = SALVE_IDLE;
    UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
}

void I2C_Error_Handler(void)
{
    I2C_SlvCtrlState = SALVE_IDLE;
    UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
}

void I2C_Timeout_Handler(void)
{
    I2C_SlvCtrlState = SALVE_IDLE;
    UI2C_SET_CONTROL_REG(I2C_SLAVE_CH, (UI2C_CTL_PTRG | UI2C_CTL_AA));
}

/*-----------------------------------------------------------------------------------------------------------
 * Function:    TaskI2CSlv_Handler
 * Description: The keyboard matrix scan task handler
 *
 * Parameters:  pvParameter - the task's paramter that passed into while task created
 *
 * Returns:     none
 *---------------------------------------------------------------------------------------------------------*/
void TaskI2CSlv_Handler(void)
{
    uint32_t     uxBits;

    uxBits = TaskI2CSlv_GetEventBits();

    if ((uxBits & evtI2CWrite) == evtI2CWrite)
    {
        TaskI2CSlv_ClrEventBits(evtI2CWrite);
        I2C_Write_Hanelder();
    }
    else if ((uxBits & evtI2CRead) == evtI2CRead)
    {
        TaskI2CSlv_ClrEventBits(evtI2CRead);
        I2C_Read_Handler();
    }
    else if ((uxBits & evtI2CWriteRead) == evtI2CWriteRead)
    {
        TaskI2CSlv_ClrEventBits(evtI2CWriteRead);
        I2C_Write_Read_Handler();
    }
    else if ((uxBits & evtI2CNAck) == evtI2CNAck)
    {
        TaskI2CSlv_ClrEventBits(evtI2CNAck);
        I2C_NAck_Handler();
    }
    else if ((uxBits & evtI2CStop) == evtI2CStop)
    {
        TaskI2CSlv_ClrEventBits(evtI2CStop);
        I2C_Stop_Handler();
    }
    else if ((uxBits & evtI2CError) == evtI2CError)
    {
        TaskI2CSlv_ClrEventBits(evtI2CError);
        I2C_Error_Handler();
    }
    else if ((uxBits & evtI2CArbLose) == evtI2CArbLose)
    {
        TaskI2CSlv_ClrEventBits(evtI2CArbLose);
        I2C_ArbLose_Handler();
    }
    else if ((uxBits & evtI2CTimeout) == evtI2CTimeout)
    {
        TaskI2CSlv_ClrEventBits(evtI2CTimeout);
        I2C_Timeout_Handler();
    }
}

uint32_t TaskI2CSlv_GetEventBits(void)
{
    uint32_t irq_state;
    uint32_t event_bits;

    irq_state = enter_critical_section();
    event_bits = TaskI2CSlvEvtGrp;
    exit_critical_section(irq_state);

    return event_bits;
}

/*-----------------------------------------------------------------------------------------------------------
 * Function:    TaskI2CSlv_SetEventBits
 * Description: This function...
 *
 * Parameters:  TBA
 *
 * Returns:     TBA
 *---------------------------------------------------------------------------------------------------------*/
void TaskI2CSlv_SetEventBits(uint32_t uxBitsToSet)
{
    uint32_t irq_state;

    irq_state = enter_critical_section();
    TaskI2CSlvEvtGrp |= uxBitsToSet;
    exit_critical_section(irq_state);

    set_service_flags(SERVICE_FLAG_I2C_IRQ);
}

void TaskI2CSlv_ClrEventBits(uint32_t uxBitsToSet)
{
    uint32_t irq_state;

    irq_state = enter_critical_section();
    TaskI2CSlvEvtGrp &= ~uxBitsToSet;
    exit_critical_section(irq_state);
}


/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 2020/08/07 14:36p $
 * @brief   NM1240 GDMA I2C SLAVE test
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "prj_config.h"

static volatile uint32_t FwServiceFlags = 0ul;


void Sys_Init(void);
void GPIO_IRQHandler(void);

typedef void (FUNC_PTR)(void);

#define APROM_FW_HEADER_OFFSET	0xC0
#define APROM_FW_SIZE_OFFSET	0xC8
#define APROM_FW_VERSION_OFFSET	0xCC

#define LDROM_FW_SIZE_OFFSET	0xC8
#define LDROM_FW_VERSION_OFFSET	0xCC

#define APROM_SINGNATURE_L      0x52504124
#define APROM_SINGNATURE_H      0x203A4D4F
#define FIRMWARE_UPDATE_FLAG_ADDR  (0x20001000)
static FUNC_PTR *ap_fw_entry;

uint32_t ld_fw_size;
uint32_t ld_fw_version;
uint32_t product_id;
uint32_t company_id;

uint32_t ap_fw_size;
uint32_t ap_fw_version;
uint32_t ap_fw_checksum;
uint32_t ap_rom_checksum;
uint32_t ap_fw_sig_l;
uint32_t ap_fw_sig_h;

struct fw_info_log_t {
    uint8_t info[32];
    uint32_t *value;
};

const struct fw_info_log_t Fw_Info_Log[] = 
{
    {"Product ID: ",                &product_id},
    {"Company ID: ",                &company_id},
    {"LDROM Firmware Size: ",       &ld_fw_size},
    {"LDROM Firmware Version: ",    &ld_fw_version},
    {"APROM Firmware Size: ",       &ap_fw_size},
    {"APROM Firmware Version: ",    &ap_fw_version},
    {"APROM Firmware Checksum: ",   &ap_fw_checksum},
    {"APROM Data Checksum: ",       &ap_rom_checksum},
    {"APROM Reset Handler: ",       (void *) &ap_fw_entry},
};

#define Fw_Info_Log_Cnt     (sizeof(Fw_Info_Log)/sizeof(struct fw_info_log_t))

const uint8_t Aprom_Flag_Info[][64] =
{
    "APROM firmware singanature is wrong.\n",
    "APROM firmware reset handler is wrong.\n",
    "APROM firmware size is wrong.\n",
    "APROM firmware checksum calculate fail.\n",
    "APROM firmware checksum is not matched.\n",
    "Fail to Set vector table of startup APROM address.\n",
};
#define Aprom_Flag_Cnt     (sizeof(Aprom_Flag_Info)/64)

#define AP_SINGANATURE_ERRO     (0x01 << 0)
#define AP_RESET_HANDLER_ERROR  (0x01 << 1)
#define AP_FIRMWARE_SIZE_ERROR  (0x01 << 2)
#define AP_GET_CHECKSUM_ERROR   (0x01 << 3)
#define AP_CHECKSUM_NOT_MATCHED (0x01 << 4)
#define AP_SET_VECTOR_FAIL      (0x01 << 5)

uint32_t enter_critical_section(void)
{
    uint32_t irq_state;

    // get the interrupt state, 0:interrupt enabled/non-zero: interrupt disabled.
    irq_state = __get_PRIMASK();
    __disable_irq();

    return(irq_state);
}

void exit_critical_section(uint32_t irq_state)
{
    if(irq_state == 0)
    {
        __enable_irq();
    }
}

void set_service_flags(uint32_t service_flag)
{
    uint32_t irq_state;

    irq_state = enter_critical_section();
    FwServiceFlags |= service_flag;
    exit_critical_section(irq_state);
}

void clear_service_flags(uint32_t service_flag)
{
    uint32_t irq_state;

    irq_state = enter_critical_section();
    FwServiceFlags &= ~service_flag;
    exit_critical_section(irq_state);
}

uint32_t get_service_flags(void)
{
    uint32_t irq_state;
    uint32_t service_flag;

    irq_state = enter_critical_section();
    service_flag = FwServiceFlags;
    exit_critical_section(irq_state);

    return(service_flag);
}

uint32_t identify_aprom_firmware(void)
{
    int         ret;
    uint32_t fw_flags = 0;

    ap_fw_entry = (FUNC_PTR *) FMC_Read(FMC_APROM_BASE+4);
    ap_fw_sig_l = FMC_Read(FMC_APROM_BASE + APROM_FW_HEADER_OFFSET);
    ap_fw_sig_h = FMC_Read(FMC_APROM_BASE + APROM_FW_HEADER_OFFSET+4);
    ap_fw_size = FMC_Read(FMC_APROM_BASE + APROM_FW_SIZE_OFFSET);
    ap_fw_version = FMC_Read(FMC_APROM_BASE + APROM_FW_VERSION_OFFSET);
    ap_fw_checksum = FMC_Read(FMC_APROM_BASE + ap_fw_size);

    if((ap_fw_entry == NULL) || ((uint32_t) ap_fw_entry < 0x100) || ((uint32_t) ap_fw_entry >= FMC_APROM_END))
    {
        fw_flags |= AP_RESET_HANDLER_ERROR;
    }
    else if((ap_fw_size <= 0x200) || (ap_fw_size > FMC_APROM_END))
    {
        fw_flags |= AP_FIRMWARE_SIZE_ERROR;
    }
    else if((ap_fw_sig_l != APROM_SINGNATURE_L) || (ap_fw_sig_h != APROM_SINGNATURE_H))
    {
        fw_flags |= AP_SINGANATURE_ERRO;
    }
    else
    {
       	ap_rom_checksum = 0ul;
        ret = FMC_GetCRC32Sum(FMC_APROM_BASE, ap_fw_size, &ap_rom_checksum);
        if (ret < 0)
        {
            fw_flags |= AP_GET_CHECKSUM_ERROR;
        }
        else if(ap_fw_checksum != ap_rom_checksum)
        {
            fw_flags |= AP_CHECKSUM_NOT_MATCHED;
        }
    }

    return(fw_flags);
}


/*-----------------------------------------------------------------------------------------------------------
 *---------------------------------------------------------------------------------------------------------*/
int main()
{
    uint16_t    index;
    uint32_t    service_flags;
    uint32_t    aprom_flags;
    __disable_irq();

	/* Prepare the hardware. */
    /* Initial system clock */
    Sys_Init();

    /* Initial UCSI UART module  */
    Ucsi_Uart_Module_Init();



    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable FMC ISP function */
    FMC_Open();

    /* Initial I2C module  */
    T2B_I2C_Init();

    product_id = SYS_ReadPDID();
    company_id = FMC_ReadCID();

    ld_fw_size = FMC_Read(FMC_LDROM_BASE + LDROM_FW_SIZE_OFFSET);
    ld_fw_version = FMC_Read(FMC_LDROM_BASE + LDROM_FW_VERSION_OFFSET);

    aprom_flags = identify_aprom_firmware();

    if(aprom_flags == 0x00)
    {
        if(false == FMC_ISP_Config_Vector_Base(FMC_APROM_BASE))
        {
            aprom_flags |= AP_SET_VECTOR_FAIL;
        }
    }

    /* re-configure the vector base to LDROM base */
    if(aprom_flags & AP_SET_VECTOR_FAIL)
    {
        FMC_ISP_Config_Vector_Base(FMC_LDROM_BASE);
    }

    if (*(volatile uint32_t *)FIRMWARE_UPDATE_FLAG_ADDR == 0x1)
    {
        //LDROM_FirmwareUpdate();  
    	uart_send_string(UUART2, "\nJUMP TO LDROM.\n");
    	uart_wait_send_done(UUART2);
    }

    FMC_Close();

    /* Lock protected Register */
    SYS_LockReg();

    for(index = 0; index < Fw_Info_Log_Cnt; index++)
    {
        uart_send_string(UUART2, (uint8_t *) Fw_Info_Log[index].info);
        uart_send_hex(UUART2, *(uint32_t *) Fw_Info_Log[index].value, 4);
        uart_send_char(UUART2, '\n');
        uart_wait_send_done(UUART2);
    }

    if(aprom_flags == 0x00)
    {
    	uart_send_string(UUART2, "\nEnter APROM.\n");
        uart_wait_send_done(UUART2);
        ap_fw_entry();
    }

    uart_send_string(UUART2, "APROM Firmware check status: ");
    uart_send_hex(UUART2, aprom_flags, 1);
    uart_send_char(UUART2, '\n');
    
    for(index = 0; index < Aprom_Flag_Cnt; index++)
    {
        if(aprom_flags & (0x01 << index))
        {
            uart_send_string(UUART2, (uint8_t *) Aprom_Flag_Info[index]);
            uart_wait_send_done(UUART2);
        }
    }

    uart_send_string(UUART2, "\nFirmware is running at LDROM.\n");
    uart_wait_send_done(UUART2);

    __enable_irq();

    //I2c_module_init();
    //T2B_I2C_Init();

    /*------------------------------------------------------------------------------
     * If all is well, the scheduler will now be running, and the following line will never be reached.
     * If the following line does execute, then there was insufficient FreeRTOS heap memory available for
     * the idle and/or timer tasks to be created.
     * See the memory management section on the FreeRTOS web site for more details.
     *----------------------------------------------------------------------------*/
    while(1)
    {
        service_flags = get_service_flags();

        if(service_flags & SERVICE_FLAG_I2C_IRQ)
        {
            clear_service_flags(SERVICE_FLAG_I2C_IRQ);
            TaskI2CSlv_Handler();
        }
        else if(service_flags & SERVICE_FLAG_UART_IRQ)
        {
            clear_service_flags(SERVICE_FLAG_UART_IRQ);
        }
        else if(service_flags & SERVICE_FLAG_FMC_IRQ)
        {
            clear_service_flags(SERVICE_FLAG_FMC_IRQ);
        }
    }

    return(0);
}

void Sys_Init(void)
{    
    /* Unlock protected registers */
    SYS_UnlockReg();

    /*-------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                         */
    /*-------------------------------------------------------------------------------------------*/
    /* Enable HIRC clock */
    CLK_SetCoreClock(FREQ_60MHZ);

    /* Waiting for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and 
       CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Unlock protected registers */
    SYS_LockReg();
}

void Timer_Module_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    CLK_SetModuleClock(TMR0_MODULE, CLK_TMR0_SRC_HCLK, 0);
    CLK_SetModuleClock(TMR1_MODULE, CLK_TMR1_SRC_HCLK, 0);

    /* enable TMR0 module clock */
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_EnableModuleClock(TMR1_MODULE);

    /* Unlock protected registers */
    SYS_LockReg();
}


/**
 * @brief       PortA/PortB/PortC/PortD IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The PortA~PortF default IRQ, declared in startup_NM1240.s.
 */
void GPIO_IRQHandler(void)
{
    uint8_t index;
    GPIO_T * port;
    uint32_t GpioIntFlag[PORT_MAX];

    //printf("GPIO_IRQHandler\r\n");

    for(index = PORT_A; index < PORT_MAX; index++)
    {
        port = get_gpio_port_ptr(index);
        /* get GPIO interrupt flag */
        GpioIntFlag[index] = GPIO_GET_INT_FLAG(port, 0xFF);
        /* clear GPIO interrupt flag */
        GPIO_CLR_INT_FLAG(port, GpioIntFlag[index]);
    }
}

/*** (C) COPYRIGHT 2020 Nuvoton Technology Corp. ***/

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

#define RXBUFSIZE   256

uint8_t g_u8RecData[RXBUFSIZE]  = {0};
volatile uint32_t g_u32comRbytes = 0;
volatile uint32_t g_u32comRhead  = 0;
volatile uint32_t g_u32comRtail  = 0;
volatile int32_t g_bWait         = TRUE;

/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle USCI UART interrupt event                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
void USCI2_IRQHandler(void)
{
    uint32_t u32IntSts = UUART2->PROTSTS;

    if(u32IntSts & UUART_PROTSTS_RXENDIF_Msk) {
        /* Clear RX end interrupt flag*/
        UUART_CLR_PROT_INT_FLAG(UUART2, UUART_PROTSTS_RXENDIF_Msk);
        Usci_Uart_Rx_Handle();
    }

    if(u32IntSts & UUART_PROTSTS_TXENDIF_Msk) {
        /* Clear TX end interrupt flag*/
        UUART_CLR_PROT_INT_FLAG(UUART2, UUART_PROTSTS_TXENDIF_Msk);	
        Usci_Uart_Tx_Handle();
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/* USCI UART Callback function                                                                             */
/*---------------------------------------------------------------------------------------------------------*/
void Usci_Uart_Rx_Handle(void)
{
    uint8_t u8InChar = 0xFF;

    /* Get all the input characters */
    while(!UUART_IS_RX_EMPTY(UUART2)) {
        /* Get the character from USCI UART Buffer */
        u8InChar = UUART_READ(UUART2);

        if(u8InChar == '0') {
            g_bWait = FALSE;
        }

        /* Check if buffer full */
        if(g_u32comRbytes < RXBUFSIZE) {
            /* Enqueue the character */
            g_u8RecData[g_u32comRtail] = u8InChar;
            g_u32comRtail = (g_u32comRtail == (RXBUFSIZE - 1)) ? 0 : (g_u32comRtail + 1);
            g_u32comRbytes++;
        }
    }
}

void Usci_Uart_Tx_Handle(void)
{
    ;
}

void Ucsi_Uart_Irq_Enable(bool enable)
{
    if(enable == true)
    {
        /* Enable USCI UART receive and transmit end interrupt */
        UUART_ENABLE_TRANS_INT(UUART2, UUART_INTEN_RXENDIEN_Msk | UUART_INTEN_TXENDIEN_Msk);
        NVIC_EnableIRQ(USCI2_IRQn);
    }
    else
    {
        /* Disable USCI UART receive and transmit end interrupt */
        UUART_DISABLE_TRANS_INT(UUART2, UUART_INTEN_RXENDIEN_Msk  | UUART_INTEN_TXENDIEN_Msk);
        NVIC_DisableIRQ(USCI2_IRQn);
    }
}

void Ucsi_Uart_Pin_Select(void)
{
    /* USCI-Uart2-GPD7(TX) + GPE0(RX) */
    /* Set GPD/GPE multi-function pins for USCI UART2 GPD7(TX) and GPE0(RX) */
    SYS->GPD_MFP = (SYS->GPD_MFP & ~SYS_GPD_MFP_PD7MFP_Msk) | SYS_GPD_MFP_PD7_UART2_TXD;
    SYS->GPE_MFP = (SYS->GPE_MFP & ~SYS_GPE_MFP_PE0MFP_Msk) | SYS_GPE_MFP_PE0_UART2_RXD;

    /* Set GPD7 as output mode and GPE0 as Input mode */
    PD->MODE = (PD->MODE & ~GPIO_MODE_MODE7_Msk) | (GPIO_MODE_OUTPUT << GPIO_MODE_MODE7_Pos);
    PE->MODE = (PE->MODE & ~GPIO_MODE_MODE0_Msk) | (GPIO_MODE_INPUT << GPIO_MODE_MODE0_Pos);
}

void Ucsi_Uart_Module_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable USCI2 IP clock */
    CLK_EnableModuleClock(USCI2_MODULE);

    /* Reset IP USCI2 */
    SYS_ResetModule(USCI2_RST);
  
    /* Open USCI2: 115200 */
	UUART_Open(UUART2, 115200);	

    /* USCI-Uart2-GPD7(TX) + GPE0(RX) */
    Ucsi_Uart_Pin_Select();

    /* Enable USCI UART receive and transmit end interrupt */
    //Ucsi_Uart_Irq_Enable(true);

    /* Unlock protected registers */
    SYS_LockReg();
}

void uart_wait_send_done(UUART_T* uuart)
{
	while(uuart->BUFSTS & UUART_BUFSTS_TXFULL_Msk);
}

void uart_send_char(UUART_T* uuart, int ch)
{
    while(uuart->BUFSTS & UUART_BUFSTS_TXFULL_Msk) ;

    if(ch == '\n')
    {
        uuart->TXDAT = '\r';
        while(uuart->BUFSTS & UUART_BUFSTS_TXFULL_Msk);
    }

    uuart->TXDAT = ch;
}

void uart_send_hex(UUART_T* uuart, uint32_t value, uint8_t size)
{
    uint8_t index;
    uint8_t hex;

    if(size > 4)
    {
    	size = 8;
    }
    else
    {
    	size = size * 2;
    }

    for(index = 0; index < size; index++)
    {
    	hex = (value >> (4 * (size - index - 1))) & 0x0F;
    	if(hex < 0x0A)
    	{
    		hex = hex + 0x30;
    	}
    	else
    	{
    		hex = (hex - 0x0A) + 0x41;
    	}

    	while(uuart->BUFSTS & UUART_BUFSTS_TXFULL_Msk) ;
    	uuart->TXDAT = hex;
    }
}

uint32_t uart_send_string (UUART_T* uuart, uint8_t *pu8TxBuf)
{
    uint32_t  u32Count;
    uint32_t  u32delayno;

    u32Count = 0;
    while(pu8TxBuf[u32Count])
    {
        u32delayno = 0;
        while(uuart->BUFSTS & UUART_BUFSTS_TXFULL_Msk) 
        {
            u32delayno++;
            if(u32delayno >= 0x40000000)
            {
                return u32Count;
            }
        }

        if(pu8TxBuf[u32Count] == '\n')
        {
            uuart->TXDAT = '\r';
            while(uuart->BUFSTS & UUART_BUFSTS_TXFULL_Msk);
        }

        uuart->TXDAT = pu8TxBuf[u32Count];
        u32Count++;
	}

    return u32Count;
}

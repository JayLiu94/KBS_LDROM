/*-----------------------------------------------------------------------------------------------------------
 *  Nuvoton Technology Corporation Confidential
 *
 *  Copyright (c) 2018-2022 by Nuvoton Technology Corporation
 *  All rights reserved
 *
 *<<<----------------------------------------------------------------------------------------------------->>>
 * Filename: task_kbscan.h
 *      The keyboard matrix scan task handlers
 *
 * Project:
 *            Nuvoton Embedded Controller Firmware
 *---------------------------------------------------------------------------------------------------------*/

#ifndef __UART_CTRL_H__
#define __UART_CTRL_H__

void USCI2_IRQHandler(void);
void Usci_Uart_Rx_Handle(void);
void Usci_Uart_Tx_Handle(void);
void Ucsi_Uart_Irq_Enable(bool enable);
void Ucsi_Uart_Pin_Select(void);
void Ucsi_Uart_Module_Init(void);

void uart_wait_send_done(UUART_T* uuart);
void uart_send_char(UUART_T* uuart, int ch);
void uart_send_hex(UUART_T* uuart, uint32_t value, uint8_t size);
uint32_t uart_send_string (UUART_T* uuart, uint8_t *pu8TxBuf);

#endif /* __UART_CTRL_H__ */

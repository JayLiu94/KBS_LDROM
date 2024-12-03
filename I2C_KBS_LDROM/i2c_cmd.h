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

#ifndef __T2B_I2C_CMD_H__
#define __T2B_I2C_CMD_H__


void T2B_I2C_Init(void);
void T2B_I2C_Stop_Hanelder(void);
void T2B_I2C_Write_Hanelder(uint16_t I2cRxCnt, uint8_t *I2cRxBuf);
uint16_t T2B_I2C_Write_Read_Handler(uint16_t I2cRxCnt, uint8_t *I2cRxBuf, uint8_t *I2cTxBuf);
uint16_t T2B_I2C_Read_Handler(uint8_t *I2cTxBuf);

#endif /* __T2B_I2C_CMD_H__ */

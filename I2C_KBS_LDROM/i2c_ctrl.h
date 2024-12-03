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

#ifndef __I2C_CTRL_H__
#define __I2C_CTRL_H__

enum UI2C_SLAVE_STATE {
    SALVE_IDLE  = 0,
    SALVE_START,
    SALVE_REPEAT_START,
    MASTER_ARBITRATION_LOST,
    SLAVE_RECEIVE_DATA,               /*!< Slave Get Data from Master (Write CMD) */
    SLAVE_TRANSMIT_DATA,              /*!< Slave Send Data to Master (Read CMD) */
    BUS_STOP,
    MASTERT_NACK,    /* master return NACK after receive data */
    BUS_TIMEOUT, /* transaction timeout occured */
    BUS_ERROR,
};

typedef void (*UI2C_STOP_FUNC)(void);
typedef void (*UI2C_WRITE_FUNC)(uint16_t I2cRxCnt, uint8_t *I2cRxBuf);
typedef uint16_t (*UI2C_WRITE_READ_FUNC)(uint16_t I2cRxCnt, uint8_t *I2cRxBuf, uint8_t *I2cTxBuf);
typedef uint16_t (*UI2C_READ_FUNC)(uint8_t *I2cTxBuf);

void I2c_module_init(void);
void I2C_StopCallback_Config(UI2C_STOP_FUNC callback);
void I2C_WriteCallback_Config(UI2C_WRITE_FUNC callback);
void I2C_WriteReadCallback_Config(UI2C_WRITE_READ_FUNC callback);
void I2C_ReadCallback_Config(UI2C_READ_FUNC callback);

void TaskI2CSlv_Handler(void);
void TaskI2CSlv_SetEventBits(uint32_t uxBitsToSet);

#endif /* __I2C_CTRL_H__ */

/*-----------------------------------------------------------------------------------------------------------
 *  Nuvoton Technology Corporation Confidential
 *
 *  Copyright (c) 2018-2022 by Nuvoton Technology Corporation
 *  All rights reserved
 *
 *<<<----------------------------------------------------------------------------------------------------->>>
 * Filename: prj_config.h
 *      The keyboard matrix scan task handlers
 *
 * Project:
 *            Nuvoton Embedded Controller Firmware
 *---------------------------------------------------------------------------------------------------------*/

#ifndef __PRJ_CONFIG_H__
#define __PRJ_CONFIG_H__

//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <stdint.h>
#include <stdbool.h>
#include "NM1240.h"

#include "i2c_ctrl.h"
#include "uart_ctrl.h"
#include "i2c_cmd.h"
#include "aprom_isp.h"

typedef enum {
    PORT_A = 0,
    PORT_B,
    PORT_C,
    PORT_D,
    PORT_E,
    PORT_F,
    PORT_MAX,
} GPIO_PORT_T;

typedef enum {
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_MAX,
} GPIO_PIN_T;

typedef enum {
    B_PWM = 0,
    E_PWM,
} PWM_MODULE_T;

typedef enum {
    PWM_0 = 0,
    PWM_1,
    PWM_2,
    PWM_3,
    PWM_4,
    PWM_5,
} PWM_CHANNEL_T;

struct PWM_LED_CFG_T {
    uint8_t gpio_port;
    uint8_t gpio_pin;
    uint8_t pwm_port;
    uint8_t pwm_channel;
    uint32_t funct_mode;
};


#define MAX_KSI_PIN_NUM     8
#define MAX_KSO_PIN_NUM     12

extern const uint8_t KSI_Pin_Table[8][2];
extern const uint8_t KSO_Pin_Table[12][2];

#define PRODUCT_VERSION     0x01
#define MACHINE_VERSION     0x02

extern uint32_t ld_fw_size;
extern uint32_t ld_fw_version;
extern uint32_t product_id;
extern uint32_t company_id;

extern uint32_t ap_fw_size;
extern uint32_t ap_fw_version;
extern uint32_t ap_fw_checksum;
extern uint32_t ap_rom_checksum;
extern uint32_t ap_fw_sig_l;
extern uint32_t ap_fw_sig_h;


#define SERVICE_FLAG_I2C_IRQ    (1ul << 0)
#define SERVICE_FLAG_UART_IRQ    (1ul << 1)
#define SERVICE_FLAG_FMC_IRQ    (1ul << 2)


#define SERVICE_FLAG_APROM_IDENTIFY     (1ul << 8)
#define SERVICE_FLAG_APROM_ERASE        (1ul << 8)
#define SERVICE_FLAG_APROM_READ         (1ul << 8)
#define SERVICE_FLAG_APROM_WRITE        (1ul << 8)

extern uint32_t Aprom_isp_addr;
extern uint32_t Aprom_isp_size;
extern uint32_t Aprom_isp_status;
extern uint32_t Aprom_isp_data_buf[16];

uint32_t enter_critical_section(void);
void exit_critical_section(uint32_t irq_state);
void set_service_flags(uint32_t service_flag);
void clear_service_flags(uint32_t service_flag);
uint32_t get_service_flags(void);

void SYS_SetPinFunct(uint8_t port, uint8_t pin, uint32_t pin_funct);
void Gpio_SetPinMode(uint8_t port, uint8_t pin, uint32_t mode);
GPIO_T * get_gpio_port_ptr(uint8_t port);
void kbs_gpio_init(void);

#endif /* __PRJ_CONFIG_H__ */

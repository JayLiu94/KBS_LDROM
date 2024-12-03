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

/*
    PA0: KSO_9                  PB0: KSO_5      PC0: KSO_10                             PE0: UART2_RXD      PF0: KBL_DET#
    PA1: CAPS_LED#              PB1: KSI_7      PC1: KSO_1          PD1: ICE_CLK        PE1: TP9            PF1: KB_BL_PWM#
    PA2: FN_KEY_LED#            PB2: KSI_0      PC2: KSI_6          PD2: TP18           PE2: TP10           PF2: KSO_11
    PA3: PRIVACY_LED#           PB3: KSI_4      PC3: KSI_5          PD3: TP15           PE3: TP11           PF3: KSO_0
    PA4: NUM_LOCK_LED#          PB4: KSI_2      PC4: KSI_3          PD4: TP16           PE4: INT_KB         PF4: KSO_2
    PA5: LED_PWRSTBY#_CNTR      PB5: KSI_1      PC5: KSO_4          PD5: ICE_DAT        PE5: I2C_SCL_KB      
    PA6: TP13                   PB6: KSO_3      PC6: KSO_7          PD6: TP12           PE6: I2C_SDA_KB      
    PA7: TP14                   PB7: KSO_8      PC7: KSO_6          PD7: UART2_TXD      PE7: TP17              
*/

typedef enum {
    CAPS_LED = 0,
    FN_KEY_LED,
    PRIVACY_LED,
    NUM_LOCK_LED,
    LED_PWRSTBY,
    KB_BL_PWM,
} LED_PIN_T;

const uint8_t KSI_Pin_Table[8][2] = {
    {PORT_B, PIN_2},    // PB2: KSI_0
    {PORT_B, PIN_5},    // PB5: KSI_1
    {PORT_B, PIN_4},    // PB4: KSI_2
    {PORT_C, PIN_4},    // PC4: KSI_3
    {PORT_B, PIN_3},    // PB3: KSI_4
    {PORT_C, PIN_3},    // PC3: KSI_5
    {PORT_C, PIN_2},    // PC2: KSI_6
    {PORT_B, PIN_1},    // PB1: KSI_7
};

const uint8_t KSO_Pin_Table[12][2] = {
    {PORT_F, PIN_3},    // PF3: KSO_0
    {PORT_C, PIN_1},    // PC1: KSO_1
    {PORT_F, PIN_4},    // PF4: KSO_2
    {PORT_B, PIN_6},    // PB6: KSO_3
    {PORT_C, PIN_5},    // PC5: KSO_4
    {PORT_B, PIN_0},    // PB0: KSO_5
    {PORT_C, PIN_7},    // PC7: KSO_6
    {PORT_C, PIN_6},    // PC6: KSO_7
    {PORT_B, PIN_7},    // PB7: KSO_8
    {PORT_A, PIN_0},    // PA0: KSO_9
    {PORT_C, PIN_0},    // PC0: KSO_10
    {PORT_F, PIN_2},    // PF2: KSO_11
};

const uint8_t Coustom_Pin_Table[16][2] = {
    {PORT_A, PIN_6},    // PA6: TP13
    {PORT_A, PIN_7},    // PA7: TP14
    {PORT_D, PIN_1},    // PD1: ICE_CLK
    {PORT_D, PIN_2},    // PD2: TP18
    {PORT_D, PIN_3},    // PD3: TP15
    {PORT_D, PIN_4},    // PD4: TP16
    {PORT_D, PIN_5},    // PD5: ICE_DAT
    {PORT_D, PIN_6},    // PD6: TP12
    {PORT_D, PIN_7},    // PD7: UART2_TXD
    {PORT_E, PIN_0},    // PE0: UART2_RXD
    {PORT_E, PIN_1},    // PE1: TP9
    {PORT_E, PIN_2},    // PE2: TP10
    {PORT_E, PIN_3},    // PE3: TP11
    {PORT_E, PIN_4},    // PE4: INT_KB
    {PORT_E, PIN_7},    // PE7: TP17
    {PORT_F, PIN_0},    // PF0: KBL_DET#
};

const struct PWM_LED_CFG_T LED_Pin_Table[6] = {
    {PORT_A, PIN_1, E_PWM, PWM_1, SYS_GPA_MFP_PA1_EPWM_CH1},    // PA1: CAPS_LED#
    {PORT_A, PIN_2, E_PWM, PWM_2, SYS_GPA_MFP_PA2_EPWM_CH2},    // PA2: FN_KEY_LED#
    {PORT_A, PIN_3, E_PWM, PWM_0, SYS_GPA_MFP_PA3_EPWM_CH0},    // PA3: PRIVACY_LED#
    {PORT_A, PIN_4, E_PWM, PWM_4, SYS_GPA_MFP_PA4_EPWM_CH4},    // PA4: NUM_LOCK_LED#
    {PORT_A, PIN_5, E_PWM, PWM_5, SYS_GPA_MFP_PA5_EPWM_CH5},    // PA5: LED_PWRSTBY#_CNTR
    {PORT_F, PIN_1, E_PWM, PWM_3, SYS_GPF_MFP_PF1_EPWM_CH3},    // PF1: KB_BL_PWM#
};

static uint32_t volatile * const s_pSysMfp[6] = { &SYS->GPA_MFP,
                                                  &SYS->GPB_MFP,
                                                  &SYS->GPC_MFP,
                                                  &SYS->GPD_MFP,
                                                  &SYS->GPE_MFP,
                                                  &SYS->GPF_MFP};

const GPIO_T *s_pGpioPort[6] = {PA, PB, PC, PD, PE, PF};

void SYS_SetPinFunct(uint8_t port, uint8_t pin, uint32_t pin_funct)
{
    uint32_t    pin_funct_msk;
    uint32_t  volatile  *pSysMfp;

    pin_funct_msk = 0x0ful << (pin * 4);

    *s_pSysMfp[port] = (*s_pSysMfp[port] & ~(pin_funct_msk)) | pin_funct;
}

void Gpio_SetPinMode(uint8_t port, uint8_t pin, uint32_t mode)
{
    uint32_t    pin_mode;
    uint32_t    pin_mode_msk;
    GPIO_T *    gpio_port;

    pin_mode_msk = 0x03ul << (pin * 2);
    pin_mode = (mode & 0x03ul) << (pin * 2);

    gpio_port = get_gpio_port_ptr(port);
    gpio_port->MODE = (gpio_port->MODE & ~(pin_mode_msk)) | pin_mode;
}

GPIO_T * get_gpio_port_ptr(uint8_t port)
{
    return ((GPIO_T *) s_pGpioPort[port]);
}

void kbs_gpio_init(void)
{
    uint8_t index;
    GPIO_T * port;
    uint32_t u32PinMask;

    /* configure KBL_DET# pin */
    port = get_gpio_port_ptr(PORT_F);
    u32PinMask = 1ul << PIN_0;

    SYS_SetPinFunct(PORT_F, PIN_0, 0ul);
    Gpio_SetPinMode(PORT_F, PIN_0, GPIO_MODE_INPUT);
    GPIO_DISABLE_PULL_LOW(port, u32PinMask);
    GPIO_DISABLE_PULL_UP(port, u32PinMask);
    GPIO_ENABLE_DIGITAL_PATH(port, u32PinMask);

    /* configure INT_KB pin */
    port = get_gpio_port_ptr(PORT_E);
    u32PinMask = 1ul << PIN_4;

    SYS_SetPinFunct(PORT_E, PIN_4, 0ul);
    Gpio_SetPinMode(PORT_E, PIN_4, GPIO_MODE_OPEN_DRAIN);
    GPIO_DISABLE_PULL_LOW(port, u32PinMask);
    GPIO_ENABLE_PULL_UP(port, u32PinMask);
    GPIO_PIN_DATA(PORT_E, PIN_4) = 1;
    GPIO_ENABLE_DIGITAL_PATH(port, u32PinMask);
}

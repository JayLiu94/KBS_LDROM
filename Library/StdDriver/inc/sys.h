/**************************************************************************//**
 * @file     sys.h
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 2020/05/29 14:22 $
 * @brief    NM1240 Series SYS Driver Header File
 *
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NM1240_Device_Driver NM1240 Device Driver
  @{
*/

/** @addtogroup NM1240_SYS_Driver SYS Driver
  @{
*/

/** @addtogroup NM1240_SYS_EXPORTED_CONSTANTS SYS Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Module Reset Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_RST            (SYS_IPRST1_GPIORST_Msk)    /*!< GPIO reset is one of the SYS_ResetModule parameter  */
#define TMR0_RST            (SYS_IPRST1_TMR0RST_Msk)    /*!< TMR0 reset is one of the SYS_ResetModule parameter  */
#define TMR1_RST            (SYS_IPRST1_TMR1RST_Msk)    /*!< TMR1 reset is one of the SYS_ResetModule parameter  */
#define TMR2_RST            (SYS_IPRST1_TMR2RST_Msk)    /*!< TMR2 reset is one of the SYS_ResetModule parameter  */
#define ECAP_RST            (SYS_IPRST1_CAPRST_Msk)     /*!< ECAP reset is one of the SYS_ResetModule parameter  */
#define OP_RST              (SYS_IPRST1_OPRST_Msk)      /*!< OP  reset is one of the SYS_ResetModule parameter   */
#define BPWM_RST            (SYS_IPRST1_BPWMRST_Msk)    /*!< BPWM reset is one of the SYS_ResetModule parameter  */
#define EPWM_RST            (SYS_IPRST1_EPWMRST_Msk)    /*!< EPWM reset is one of the SYS_ResetModule parameter  */
#define USCI1_RST           (SYS_IPRST1_USCI1RST_Msk)   /*!< USCI1 reset is one of the SYS_ResetModule parameter */
#define USCI2_RST           (SYS_IPRST1_USCI2RST_Msk)   /*!< USCI2 reset is one of the SYS_ResetModule parameter */
#define ADC_RST             (SYS_IPRST1_ADCRST_Msk)     /*!< ADC reset is one of the SYS_ResetModule parameter   */
#define ACMP_RST            (SYS_IPRST1_ACMPRST_Msk)    /*!< ACMP reset is one of the SYS_ResetModule parameter  */


/*---------------------------------------------------------------------------------------------------------*/
/*  Brown Out Detector Threshold Voltage Selection constant definitions.                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_BODCTL_BOD_RST_EN        (1UL<<SYS_BODCTL_BODRSTEN_Pos)     /*!< Brown-out Reset Enable */
#define SYS_BODCTL_BOD_VL_2_0V       (0UL<<SYS_BODCTL_BODVL_Pos)        /*!< Setting Brown Out Detector Threshold Voltage as 2.0V */
#define SYS_BODCTL_BOD_VL_2_2V       (1UL<<SYS_BODCTL_BODVL_Pos)        /*!< Setting Brown Out Detector Threshold Voltage as 2.2V */
#define SYS_BODCTL_BOD_VL_2_4V       (2UL<<SYS_BODCTL_BODVL_Pos)        /*!< Setting Brown Out Detector Threshold Voltage as 2.4V */
#define SYS_BODCTL_BOD_VL_2_7V       (3UL<<SYS_BODCTL_BODVL_Pos)        /*!< Setting Brown Out Detector Threshold Voltage as 2.7V */
#define SYS_BODCTL_BOD_VL_3_0V       (4UL<<SYS_BODCTL_BODVL_Pos)        /*!< Setting Brown Out Detector Threshold Voltage as 3.0V */
#define SYS_BODCTL_BOD_VL_3_7V       (5UL<<SYS_BODCTL_BODVL_Pos)        /*!< Setting Brown Out Detector Threshold Voltage as 3.7V */
#define SYS_BODCTL_BOD_VL_4_0V       (6UL<<SYS_BODCTL_BODVL_Pos)        /*!< Setting Brown Out Detector Threshold Voltage as 4.0V */
#define SYS_BODCTL_BOD_VL_4_3V       (7UL<<SYS_BODCTL_BODVL_Pos)        /*!< Setting Brown Out Detector Threshold Voltage as 4.3V */


/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/

/* How to use below #define?
Example: If user want to set PA.0 as EPWM_CH0 and PA.1 as EPWM_CH1 in initial function,
         user can issue following command to achieve it.

         SYS->GPA_MFP  = SYS_GPA_MFP_PA0_EPWM_CH0  | SYS_GPA_MFP_PA1_EPWM_CH1;
*/

/********************* Bit definition of GPA_MFP register **********************/
/* PA.0 */
#define SYS_GPA_MFP_PA0_GPIO        (0x0UL<<SYS_GPA_MFP_PA0MFP_Pos)     /*!< GPA_MFP PA0 setting for GPIO       */
#define SYS_GPA_MFP_PA0_CLKO        (0x1UL<<SYS_GPA_MFP_PA0MFP_Pos)     /*!< GPA_MFP PA0 setting for CLKO       */
#define SYS_GPA_MFP_PA0_EPWM_CH0    (0x3UL<<SYS_GPA_MFP_PA0MFP_Pos)     /*!< GPA_MFP PA0 setting for EPWM_CH0   */
#define SYS_GPA_MFP_PA0_I2C1_SCL    (0x8UL<<SYS_GPA_MFP_PA0MFP_Pos)     /*!< GPA_MFP PA0 setting for I2C1_SCL   */
#define SYS_GPA_MFP_PA0_SPI1_CLK    (0xAUL<<SYS_GPA_MFP_PA0MFP_Pos)     /*!< GPA_MFP PA0 setting for SPI1_CLK   */
#define SYS_GPA_MFP_PA0_UART1_TXD   (0xBUL<<SYS_GPA_MFP_PA0MFP_Pos)     /*!< GPA_MFP PA0 setting for UART1_TXD  */
#define SYS_GPA_MFP_PA0_EPWM_CH1    (0xFUL<<SYS_GPA_MFP_PA0MFP_Pos)     /*!< GPA_MFP PA0 setting for EPWM_CH1   */

/* PA.1 */
#define SYS_GPA_MFP_PA1_GPIO        (0x0UL<<SYS_GPA_MFP_PA1MFP_Pos)     /*!< GPA_MFP PA1 setting for GPIO       */
#define SYS_GPA_MFP_PA1_EPWM_CH1    (0x3UL<<SYS_GPA_MFP_PA1MFP_Pos)     /*!< GPA_MFP PA1 setting for EPWM_CH1   */
#define SYS_GPA_MFP_PA1_T2          (0x7UL<<SYS_GPA_MFP_PA1MFP_Pos)     /*!< GPA_MFP PA1 setting for T2         */
#define SYS_GPA_MFP_PA1_I2C1_SDA    (0x8UL<<SYS_GPA_MFP_PA1MFP_Pos)     /*!< GPA_MFP PA1 setting for I2C1_SDA   */
#define SYS_GPA_MFP_PA1_SPI1_MOSI   (0xAUL<<SYS_GPA_MFP_PA1MFP_Pos)     /*!< GPA_MFP PA1 setting for SPI1_MOSI  */
#define SYS_GPA_MFP_PA1_UART1_RXD   (0xBUL<<SYS_GPA_MFP_PA1MFP_Pos)     /*!< GPA_MFP PA1 setting for UART1_RXD  */
#define SYS_GPA_MFP_PA1_SPI1_MISO   (0xEUL<<SYS_GPA_MFP_PA1MFP_Pos)     /*!< GPA_MFP PA1 setting for SPI1_MISO  */
#define SYS_GPA_MFP_PA1_EPWM_CH3    (0xFUL<<SYS_GPA_MFP_PA1MFP_Pos)     /*!< GPA_MFP PA1 setting for EPWM_CH3   */

/* PA.2 */
#define SYS_GPA_MFP_PA2_GPIO        (0x0UL<<SYS_GPA_MFP_PA2MFP_Pos)     /*!< GPA_MFP PA2 setting for GPIO       */
#define SYS_GPA_MFP_PA2_EPWM_CH2    (0x3UL<<SYS_GPA_MFP_PA2MFP_Pos)     /*!< GPA_MFP PA2 setting for EPWM_CH2   */
#define SYS_GPA_MFP_PA2_T0          (0x7UL<<SYS_GPA_MFP_PA2MFP_Pos)     /*!< GPA_MFP PA2 setting for T0         */
#define SYS_GPA_MFP_PA2_SPI1_MISO   (0xAUL<<SYS_GPA_MFP_PA2MFP_Pos)     /*!< GPA_MFP PA2 setting for SPI1_MISO  */
#define SYS_GPA_MFP_PA2_SPI1_MOSI   (0xEUL<<SYS_GPA_MFP_PA2MFP_Pos)     /*!< GPA_MFP PA2 setting for SPI1_MOSI  */
#define SYS_GPA_MFP_PA2_EPWM_CH5    (0xFUL<<SYS_GPA_MFP_PA2MFP_Pos)     /*!< GPA_MFP PA2 setting for EPWM_CH5   */

/* PA.3 */
#define SYS_GPA_MFP_PA3_GPIO        (0x0UL<<SYS_GPA_MFP_PA3MFP_Pos)     /*!< GPA_MFP PA3 setting for GPIO       */
#define SYS_GPA_MFP_PA3_CLKO        (0x1UL<<SYS_GPA_MFP_PA3MFP_Pos)     /*!< GPA_MFP PA3 setting for CLKO       */
#define SYS_GPA_MFP_PA3_EPWM_CH3    (0x3UL<<SYS_GPA_MFP_PA3MFP_Pos)     /*!< GPA_MFP PA3 setting for EPWM_CH3   */
#define SYS_GPA_MFP_PA3_SPI1_SS     (0xAUL<<SYS_GPA_MFP_PA3MFP_Pos)     /*!< GPA_MFP PA3 setting for SPI1_SS    */
#define SYS_GPA_MFP_PA3_UART0_TXD   (0xBUL<<SYS_GPA_MFP_PA3MFP_Pos)     /*!< GPA_MFP PA3 setting for UART0_TXD  */
#define SYS_GPA_MFP_PA3_EPWM_CH0    (0xFUL<<SYS_GPA_MFP_PA3MFP_Pos)     /*!< GPA_MFP PA3 setting for EPWM_CH0   */

/* PA.4 */
#define SYS_GPA_MFP_PA4_GPIO        (0x0UL<<SYS_GPA_MFP_PA4MFP_Pos)     /*!< GPA_MFP PA4 setting for GPIO       */
#define SYS_GPA_MFP_PA4_EPWM_CH4    (0x3UL<<SYS_GPA_MFP_PA4MFP_Pos)     /*!< GPA_MFP PA4 setting for EPWM_CH4   */
#define SYS_GPA_MFP_PA4_I2C2_SCL    (0x8UL<<SYS_GPA_MFP_PA4MFP_Pos)     /*!< GPA_MFP PA4 setting for I2C2_SCL   */
#define SYS_GPA_MFP_PA4_UART2_TXD   (0xBUL<<SYS_GPA_MFP_PA4MFP_Pos)     /*!< GPA_MFP PA4 setting for UART2_TXD  */
#define SYS_GPA_MFP_PA4_EPWM_CH2    (0xFUL<<SYS_GPA_MFP_PA4MFP_Pos)     /*!< GPA_MFP PA4 setting for EPWM_CH2   */

/* PA.5 */
#define SYS_GPA_MFP_PA5_GPIO        (0x0UL<<SYS_GPA_MFP_PA5MFP_Pos)     /*!< GPA_MFP PA5 setting for GPIO       */
#define SYS_GPA_MFP_PA5_EPWM_CH5    (0x3UL<<SYS_GPA_MFP_PA5MFP_Pos)     /*!< GPA_MFP PA5 setting for EPWM_CH5   */
#define SYS_GPA_MFP_PA5_ACMP0_O     (0x4UL<<SYS_GPA_MFP_PA5MFP_Pos)     /*!< GPA_MFP PA5 setting for ACMP0_O    */
#define SYS_GPA_MFP_PA5_I2C2_SDA    (0x8UL<<SYS_GPA_MFP_PA5MFP_Pos)     /*!< GPA_MFP PA5 setting for I2C2_SDA   */
#define SYS_GPA_MFP_PA5_UART2_RXD   (0xBUL<<SYS_GPA_MFP_PA5MFP_Pos)     /*!< GPA_MFP PA5 setting for UART2_RXD  */
#define SYS_GPA_MFP_PA5_EPWM_CH4    (0xFUL<<SYS_GPA_MFP_PA5MFP_Pos)     /*!< GPA_MFP PA5 setting for EPWM_CH4   */

/* PA.6 */
#define SYS_GPA_MFP_PA6_GPIO        (0x0UL<<SYS_GPA_MFP_PA6MFP_Pos)     /*!< GPA_MFP PA6 setting for GPIO       */
#define SYS_GPA_MFP_PA6_EPWM_CH5    (0x3UL<<SYS_GPA_MFP_PA6MFP_Pos)     /*!< GPA_MFP PA6 setting for EPWM_CH5   */
#define SYS_GPA_MFP_PA6_I2C2_SCL    (0xEUL<<SYS_GPA_MFP_PA6MFP_Pos)     /*!< GPA_MFP PA6 setting for I2C2_SCL   */
#define SYS_GPA_MFP_PA6_BPWM_CH0    (0xFUL<<SYS_GPA_MFP_PA6MFP_Pos)     /*!< GPA_MFP PA6 setting for BPWM_CH0   */

/* PA.7 */
#define SYS_GPA_MFP_PA7_GPIO        (0x0UL<<SYS_GPA_MFP_PA7MFP_Pos)     /*!< GPA_MFP PA7 setting for GPIO       */
#define SYS_GPA_MFP_PA7_EPWM_CH4    (0x3UL<<SYS_GPA_MFP_PA7MFP_Pos)     /*!< GPA_MFP PA7 setting for EPWM_CH4   */
#define SYS_GPA_MFP_PA7_ACMP0_O     (0x4UL<<SYS_GPA_MFP_PA7MFP_Pos)     /*!< GPA_MFP PA7 setting for ACMP0_O    */
#define SYS_GPA_MFP_PA7_I2C2_SDA    (0xEUL<<SYS_GPA_MFP_PA7MFP_Pos)     /*!< GPA_MFP PA7 setting for I2C2_SDA   */
#define SYS_GPA_MFP_PA7_BPWM_CH1    (0xFUL<<SYS_GPA_MFP_PA7MFP_Pos)     /*!< GPA_MFP PA7 setting for BPWM_CH1   */

/********************* Bit definition of GPB_MFP register **********************/
/* PB.0 */
#define SYS_GPB_MFP_PB0_GPIO        (0x0UL<<SYS_GPB_MFP_PB0MFP_Pos)     /*!< GPB_MFP PB0 setting for GPIO       */
#define SYS_GPB_MFP_PB0_ADC0_P0     (0x2UL<<SYS_GPB_MFP_PB0MFP_Pos)     /*!< GPB_MFP PB0 setting for ADC0_P0    */
#define SYS_GPB_MFP_PB0_ACMP0_P0    (0x4UL<<SYS_GPB_MFP_PB0MFP_Pos)     /*!< GPB_MFP PB0 setting for ACMP0_P0   */
#define SYS_GPB_MFP_PB0_UART1_TXD   (0xBUL<<SYS_GPB_MFP_PB0MFP_Pos)     /*!< GPB_MFP PB0 setting for UART1_TXD  */
#define SYS_GPB_MFP_PB0_ECAP0       (0xCUL<<SYS_GPB_MFP_PB0MFP_Pos)     /*!< GPB_MFP PB0 setting for ECAP0      */

/* PB.1 */
#define SYS_GPB_MFP_PB1_GPIO        (0x0UL<<SYS_GPB_MFP_PB1MFP_Pos)     /*!< GPB_MFP PB1 setting for GPIO       */
#define SYS_GPB_MFP_PB1_ADC0_P1     (0x2UL<<SYS_GPB_MFP_PB1MFP_Pos)     /*!< GPB_MFP PB1 setting for ADC0_P1    */
#define SYS_GPB_MFP_PB1_ACMP0_P1    (0x4UL<<SYS_GPB_MFP_PB1MFP_Pos)     /*!< GPB_MFP PB1 setting for ACMP0_P1   */
#define SYS_GPB_MFP_PB1_UART1_RXD   (0xBUL<<SYS_GPB_MFP_PB1MFP_Pos)     /*!< GPB_MFP PB1 setting for UART1_RXD  */
#define SYS_GPB_MFP_PB1_ECAP1       (0xCUL<<SYS_GPB_MFP_PB1MFP_Pos)     /*!< GPB_MFP PB1 setting for ECAP1      */

/* PB.2 */
#define SYS_GPB_MFP_PB2_GPIO        (0x0UL<<SYS_GPB_MFP_PB2MFP_Pos)     /*!< GPB_MFP PB2 setting for GPIO       */
#define SYS_GPB_MFP_PB2_ADC0_P2     (0x2UL<<SYS_GPB_MFP_PB2MFP_Pos)     /*!< GPB_MFP PB2 setting for ADC0_P2    */
#define SYS_GPB_MFP_PB2_BPWM_CH1    (0x3UL<<SYS_GPB_MFP_PB2MFP_Pos)     /*!< GPB_MFP PB2 setting for BPWM_CH1   */
#define SYS_GPB_MFP_PB2_ACMP0_P2    (0x4UL<<SYS_GPB_MFP_PB2MFP_Pos)     /*!< GPB_MFP PB2 setting for ACMP0_P2   */
#define SYS_GPB_MFP_PB2_UART1_TXD   (0xBUL<<SYS_GPB_MFP_PB2MFP_Pos)     /*!< GPB_MFP PB2 setting for UART1_TXD  */
#define SYS_GPB_MFP_PB2_ECAP2       (0xCUL<<SYS_GPB_MFP_PB2MFP_Pos)     /*!< GPB_MFP PB2 setting for ECAP2      */
#define SYS_GPB_MFP_PB2_T2          (0xEUL<<SYS_GPB_MFP_PB2MFP_Pos)     /*!< GPB_MFP PB2 setting for T2         */

/* PB.3 */
#define SYS_GPB_MFP_PB3_GPIO        (0x0UL<<SYS_GPB_MFP_PB3MFP_Pos)     /*!< GPB_MFP PB3 setting for GPIO       */
#define SYS_GPB_MFP_PB3_ADC0_P9     (0x2UL<<SYS_GPB_MFP_PB3MFP_Pos)     /*!< GPB_MFP PB3 setting for ADC0_P9    */
#define SYS_GPB_MFP_PB3_T0          (0x7UL<<SYS_GPB_MFP_PB3MFP_Pos)     /*!< GPB_MFP PB3 setting for T0         */
#define SYS_GPB_MFP_PB3_UART1_RXD   (0xBUL<<SYS_GPB_MFP_PB3MFP_Pos)     /*!< GPB_MFP PB3 setting for UART1_RXD  */

/* PB.4 */
#define SYS_GPB_MFP_PB4_GPIO        (0x0UL<<SYS_GPB_MFP_PB4MFP_Pos)     /*!< GPB_MFP PB4 setting for GPIO       */
#define SYS_GPB_MFP_PB4_ADC1_P0     (0x2UL<<SYS_GPB_MFP_PB4MFP_Pos)     /*!< GPB_MFP PB4 setting for ADC1_P0    */
#define SYS_GPB_MFP_PB4_ACMP0_N     (0x4UL<<SYS_GPB_MFP_PB4MFP_Pos)     /*!< GPB_MFP PB4 setting for ACMP0_N    */
#define SYS_GPB_MFP_PB4_T1          (0x7UL<<SYS_GPB_MFP_PB4MFP_Pos)     /*!< GPB_MFP PB4 setting for T1         */
#define SYS_GPB_MFP_PB4_SPI1_SS     (0xAUL<<SYS_GPB_MFP_PB4MFP_Pos)     /*!< GPB_MFP PB4 setting for SPI1_SS    */
#define SYS_GPB_MFP_PB4_UART2_TXD   (0xBUL<<SYS_GPB_MFP_PB4MFP_Pos)     /*!< GPB_MFP PB4 setting for UART2_TXD  */

/* PB.5 */
#define SYS_GPB_MFP_PB5_GPIO        (0x0UL<<SYS_GPB_MFP_PB5MFP_Pos)     /*!< GPB_MFP PB5 setting for GPIO       */
#define SYS_GPB_MFP_PB5_ADC0_P5     (0x2UL<<SYS_GPB_MFP_PB5MFP_Pos)     /*!< GPB_MFP PB5 setting for ADC0_P5    */
#define SYS_GPB_MFP_PB5_DAC0        (0x4UL<<SYS_GPB_MFP_PB5MFP_Pos)     /*!< GPB_MFP PB5 setting for DAC0       */
#define SYS_GPB_MFP_PB5_CCAP_P0     (0x7UL<<SYS_GPB_MFP_PB5MFP_Pos)     /*!< GPB_MFP PB5 setting for CCAP_P0    */
#define SYS_GPB_MFP_PB5_SPI1_CLK    (0xAUL<<SYS_GPB_MFP_PB5MFP_Pos)     /*!< GPB_MFP PB5 setting for SPI1_CLK   */
#define SYS_GPB_MFP_PB5_UART2_RXD   (0xBUL<<SYS_GPB_MFP_PB5MFP_Pos)     /*!< GPB_MFP PB5 setting for UART2_RXD  */

/* PB.6 */
#define SYS_GPB_MFP_PB6_GPIO        (0x0UL<<SYS_GPB_MFP_PB6MFP_Pos)     /*!< GPB_MFP PB6 setting for GPIO       */
#define SYS_GPB_MFP_PB6_ADC0_P6     (0x2UL<<SYS_GPB_MFP_PB6MFP_Pos)     /*!< GPB_MFP PB6 setting for ADC0_P6    */
#define SYS_GPB_MFP_PB6_PWM_BRK_P1  (0x3UL<<SYS_GPB_MFP_PB6MFP_Pos)     /*!< GPB_MFP PB6 setting for PWM_BRK_P1 */
#define SYS_GPB_MFP_PB6_CCAP_P0     (0x7UL<<SYS_GPB_MFP_PB6MFP_Pos)     /*!< GPB_MFP PB6 setting for CCAP_P0    */
#define SYS_GPB_MFP_PB6_SPI1_MISO   (0xAUL<<SYS_GPB_MFP_PB6MFP_Pos)     /*!< GPB_MFP PB6 setting for SPI1_MISO  */
#define SYS_GPB_MFP_PB6_ECAP1       (0xCUL<<SYS_GPB_MFP_PB6MFP_Pos)     /*!< GPB_MFP PB6 setting for ECAP1      */
#define SYS_GPB_MFP_PB6_T1          (0xEUL<<SYS_GPB_MFP_PB6MFP_Pos)     /*!< GPB_MFP PB6 setting for T1         */

/* PB.7 */
#define SYS_GPB_MFP_PB7_GPIO        (0x0UL<<SYS_GPB_MFP_PB7MFP_Pos)     /*!< GPB_MFP PB7 setting for GPIO       */
#define SYS_GPB_MFP_PB7_ADC0_P7     (0x2UL<<SYS_GPB_MFP_PB7MFP_Pos)     /*!< GPB_MFP PB7 setting for ADC0_P7    */
#define SYS_GPB_MFP_PB7_PWM_BRK_P2  (0x3UL<<SYS_GPB_MFP_PB7MFP_Pos)     /*!< GPB_MFP PB7 setting for DAC0       */
#define SYS_GPB_MFP_PB7_CCAP_P0     (0x7UL<<SYS_GPB_MFP_PB7MFP_Pos)     /*!< GPB_MFP PB7 setting for CCAP_P0    */
#define SYS_GPB_MFP_PB7_SPI1_MOSI   (0xAUL<<SYS_GPB_MFP_PB7MFP_Pos)     /*!< GPB_MFP PB7 setting for SPI1_MOSI  */
#define SYS_GPB_MFP_PB7_ECAP0       (0xCUL<<SYS_GPB_MFP_PB7MFP_Pos)     /*!< GPB_MFP PB7 setting for ECAP0      */
#define SYS_GPB_MFP_PB7_EPWM_CH0    (0xEUL<<SYS_GPB_MFP_PB7MFP_Pos)     /*!< GPB_MFP PB7 setting for EPWM_CH0   */
#define SYS_GPB_MFP_PB7_EPWM_CH1    (0xFUL<<SYS_GPB_MFP_PB7MFP_Pos)     /*!< GPB_MFP PB7 setting for EPWM_CH1   */

/********************* Bit definition of GPC_MFP register **********************/
/* PC.0 */
#define SYS_GPC_MFP_PC0_GPIO        (0x0UL<<SYS_GPC_MFP_PC0MFP_Pos)     /*!< GPC_MFP PC0 setting for GPIO       */
#define SYS_GPC_MFP_PC0_ADC0_P3     (0x2UL<<SYS_GPC_MFP_PC0MFP_Pos)     /*!< GPC_MFP PC0 setting for ADC0_P3    */
#define SYS_GPC_MFP_PC0_BPWM_CH0    (0x3UL<<SYS_GPC_MFP_PC0MFP_Pos)     /*!< GPC_MFP PC0 setting for BPWM_CH0   */
#define SYS_GPC_MFP_PC0_I2C1_SCL    (0x8UL<<SYS_GPC_MFP_PC0MFP_Pos)     /*!< GPC_MFP PC0 setting for I2C1_SCL   */
#define SYS_GPC_MFP_PC0_SPI1_CLK    (0xAUL<<SYS_GPC_MFP_PC0MFP_Pos)     /*!< GPC_MFP PC0 setting for SPI1_CLK   */
#define SYS_GPC_MFP_PC0_UART1_TXD   (0xBUL<<SYS_GPC_MFP_PC0MFP_Pos)     /*!< GPC_MFP PC0 setting for UART1_TXD  */

/* PC.1 */
#define SYS_GPC_MFP_PC1_GPIO        (0x0UL<<SYS_GPC_MFP_PC1MFP_Pos)     /*!< GPC_MFP PC1 setting for GPIO       */
#define SYS_GPC_MFP_PC1_ADC0_P4     (0x2UL<<SYS_GPC_MFP_PC1MFP_Pos)     /*!< GPC_MFP PC1 setting for ADC0_P4    */
#define SYS_GPC_MFP_PC1_STADC       (0x3UL<<SYS_GPC_MFP_PC1MFP_Pos)     /*!< GPC_MFP PC1 setting for STADC      */
#define SYS_GPC_MFP_PC1_ACMP0_P3    (0x4UL<<SYS_GPC_MFP_PC1MFP_Pos)     /*!< GPC_MFP PC1 setting for ACMP0_P3   */
#define SYS_GPC_MFP_PC1_CCAP_P1     (0x7UL<<SYS_GPC_MFP_PC1MFP_Pos)     /*!< GPC_MFP PC1 setting for CCAP_P1    */
#define SYS_GPC_MFP_PC1_I2C1_SDA    (0x8UL<<SYS_GPC_MFP_PC1MFP_Pos)     /*!< GPC_MFP PC1 setting for I2C1_SDA   */
#define SYS_GPC_MFP_PC1_SPI1_MISO   (0xAUL<<SYS_GPC_MFP_PC1MFP_Pos)     /*!< GPC_MFP PC1 setting for SPI1_MISO  */
#define SYS_GPC_MFP_PC1_UART1_RXD   (0xBUL<<SYS_GPC_MFP_PC1MFP_Pos)     /*!< GPC_MFP PC1 setting for UART1_RXD  */

/* PC.2 */
#define SYS_GPC_MFP_PC2_GPIO        (0x0UL<<SYS_GPC_MFP_PC2MFP_Pos)     /*!< GPC_MFP PC2 setting for GPIO       */
#define SYS_GPC_MFP_PC2_ADC1_P2     (0x2UL<<SYS_GPC_MFP_PC2MFP_Pos)     /*!< GPC_MFP PC2 setting for ADC1_P2    */
#define SYS_GPC_MFP_PC2_PWM_BRK_P0  (0x3UL<<SYS_GPC_MFP_PC2MFP_Pos)     /*!< GPC_MFP PC2 setting for PWM_BRK_P0 */
#define SYS_GPC_MFP_PC2_CCAP_P1     (0x7UL<<SYS_GPC_MFP_PC2MFP_Pos)     /*!< GPC_MFP PC2 setting for CCAP_P1    */
#define SYS_GPC_MFP_PC2_I2C1_SDA    (0x8UL<<SYS_GPC_MFP_PC2MFP_Pos)     /*!< GPC_MFP PC2 setting for I2C1_SDA   */
#define SYS_GPC_MFP_PC2_SPI1_MOSI   (0xAUL<<SYS_GPC_MFP_PC2MFP_Pos)     /*!< GPC_MFP PC2 setting for SPI1_MOSI  */
#define SYS_GPC_MFP_PC2_UART1_RXD   (0xBUL<<SYS_GPC_MFP_PC2MFP_Pos)     /*!< GPC_MFP PC2 setting for UART1_RXD  */

/* PC.3 */
#define SYS_GPC_MFP_PC3_GPIO        (0x0UL<<SYS_GPC_MFP_PC3MFP_Pos)     /*!< GPC_MFP PC3 setting for GPIO       */
#define SYS_GPC_MFP_PC3_EXT_CLK     (0x1UL<<SYS_GPC_MFP_PC3MFP_Pos)     /*!< GPC_MFP PC3 setting for EXT_CLK    */
#define SYS_GPC_MFP_PC3_PWM_BRK_P1  (0x3UL<<SYS_GPC_MFP_PC3MFP_Pos)     /*!< GPC_MFP PC3 setting for PWM_BRK_P1 */
#define SYS_GPC_MFP_PC3_SPI1_SS     (0xAUL<<SYS_GPC_MFP_PC3MFP_Pos)     /*!< GPC_MFP PC3 setting for SPI1_SS    */

/* PC.4 */
#define SYS_GPC_MFP_PC4_GPIO        (0x0UL<<SYS_GPC_MFP_PC4MFP_Pos)     /*!< GPC_MFP PC4 setting for GPIO       */
#define SYS_GPC_MFP_PC4_PWM_BRK_P2  (0x3UL<<SYS_GPC_MFP_PC4MFP_Pos)     /*!< GPC_MFP PC4 setting for PWM_BRK_P2 */
#define SYS_GPC_MFP_PC4_ECAP0       (0x7UL<<SYS_GPC_MFP_PC4MFP_Pos)     /*!< GPC_MFP PC4 setting for ECAP0      */
#define SYS_GPC_MFP_PC4_I2C2_SCL    (0x8UL<<SYS_GPC_MFP_PC4MFP_Pos)     /*!< GPC_MFP PC4 setting for I2C2_SCL   */
#define SYS_GPC_MFP_PC4_SPI1_SS     (0xAUL<<SYS_GPC_MFP_PC4MFP_Pos)     /*!< GPC_MFP PC4 setting for SPI1_SS    */
#define SYS_GPC_MFP_PC4_UART2_TXD   (0xBUL<<SYS_GPC_MFP_PC4MFP_Pos)     /*!< GPC_MFP PC4 setting for UART2_TXD  */
#define SYS_GPC_MFP_PC4_ECAP2       (0xCUL<<SYS_GPC_MFP_PC4MFP_Pos)     /*!< GPC_MFP PC4 setting for ECAP2      */

/* PC.5 */
#define SYS_GPC_MFP_PC5_GPIO        (0x0UL<<SYS_GPC_MFP_PC5MFP_Pos)     /*!< GPC_MFP PC5 setting for GPIO       */
#define SYS_GPC_MFP_PC5_ADC1_P5     (0x2UL<<SYS_GPC_MFP_PC5MFP_Pos)     /*!< GPC_MFP PC5 setting for ADC1_P5    */
#define SYS_GPC_MFP_PC5_PWM_BRK_P0  (0x3UL<<SYS_GPC_MFP_PC5MFP_Pos)     /*!< GPC_MFP PC5 setting for PWM_BRK_P0 */
#define SYS_GPC_MFP_PC5_CCAP_P1     (0x7UL<<SYS_GPC_MFP_PC5MFP_Pos)     /*!< GPC_MFP PC5 setting for CCAP_P1    */
#define SYS_GPC_MFP_PC5_ECAP2       (0xCUL<<SYS_GPC_MFP_PC5MFP_Pos)     /*!< GPC_MFP PC5 setting for ECAP2      */
#define SYS_GPC_MFP_PC5_EPWM_CH1    (0xEUL<<SYS_GPC_MFP_PC5MFP_Pos)     /*!< GPC_MFP PC5 setting for EPWM_CH1   */
#define SYS_GPC_MFP_PC5_EPWM_CH3    (0xFUL<<SYS_GPC_MFP_PC5MFP_Pos)     /*!< GPC_MFP PC5 setting for EPWM_CH3   */

/* PC.6 */
#define SYS_GPC_MFP_PC6_GPIO        (0x0UL<<SYS_GPC_MFP_PC6MFP_Pos)     /*!< GPC_MFP PC6 setting for GPIO       */
#define SYS_GPC_MFP_PC6_ADC1_P6     (0x2UL<<SYS_GPC_MFP_PC6MFP_Pos)     /*!< GPC_MFP PC6 setting for ADC1_P6    */
#define SYS_GPC_MFP_PC6_EPWM_CH2    (0x3UL<<SYS_GPC_MFP_PC6MFP_Pos)     /*!< GPC_MFP PC6 setting for EPWM_CH2   */
#define SYS_GPC_MFP_PC6_DAC1        (0x5UL<<SYS_GPC_MFP_PC6MFP_Pos)     /*!< GPC_MFP PC6 setting for DAC1       */
#define SYS_GPC_MFP_PC6_T2          (0x7UL<<SYS_GPC_MFP_PC6MFP_Pos)     /*!< GPC_MFP PC6 setting for T2         */
#define SYS_GPC_MFP_PC6_I2C2_SCL    (0x8UL<<SYS_GPC_MFP_PC6MFP_Pos)     /*!< GPC_MFP PC6 setting for I2C2_SCL   */
#define SYS_GPC_MFP_PC6_UART2_TXD   (0xBUL<<SYS_GPC_MFP_PC6MFP_Pos)     /*!< GPC_MFP PC6 setting for UART2_TXD  */
#define SYS_GPC_MFP_PC6_EPWM_CH5    (0xFUL<<SYS_GPC_MFP_PC6MFP_Pos)     /*!< GPC_MFP PC6 setting for EPWM_CH5   */

/* PC.7 */
#define SYS_GPC_MFP_PC7_GPIO        (0x0UL<<SYS_GPC_MFP_PC7MFP_Pos)     /*!< GPC_MFP PC7 setting for GPIO       */
#define SYS_GPC_MFP_PC7_ADC1_P7     (0x2UL<<SYS_GPC_MFP_PC7MFP_Pos)     /*!< GPC_MFP PC7 setting for ADC1_P7    */
#define SYS_GPC_MFP_PC7_ECAP1       (0xCUL<<SYS_GPC_MFP_PC7MFP_Pos)     /*!< GPC_MFP PC7 setting for ECAP1      */

/********************* Bit definition of GPD_MFP register **********************/
/* PD.1 */
#define SYS_GPD_MFP_PD1_GPIO        (0x0UL<<SYS_GPD_MFP_PD1MFP_Pos)     /*!< GPD_MFP PD1 setting for GPIO       */
#define SYS_GPD_MFP_PD1_ICE_CLK     (0x1UL<<SYS_GPD_MFP_PD1MFP_Pos)     /*!< GPD_MFP PD1 setting for ICE_CLK    */
#define SYS_GPD_MFP_PD1_SPI1_SS     (0xAUL<<SYS_GPD_MFP_PD1MFP_Pos)     /*!< GPD_MFP PD1 setting for SPI1_SS    */

/* PD.2 */
#define SYS_GPD_MFP_PD2_GPIO        (0x0UL<<SYS_GPD_MFP_PD2MFP_Pos)     /*!< GPD_MFP PD2 setting for GPIO       */
#define SYS_GPD_MFP_PD2_ADC1_P1     (0x2UL<<SYS_GPD_MFP_PD2MFP_Pos)     /*!< GPD_MFP PD2 setting for ADC1_P1    */
#define SYS_GPD_MFP_PD2_CCAP_P0     (0x7UL<<SYS_GPD_MFP_PD2MFP_Pos)     /*!< GPD_MFP PD2 setting for CCAP_P0    */
#define SYS_GPD_MFP_PD2_SPI1_MISO   (0xAUL<<SYS_GPD_MFP_PD2MFP_Pos)     /*!< GPD_MFP PD2 setting for SPI1_MISO  */

/* PD.3 */
#define SYS_GPD_MFP_PD3_GPIO        (0x0UL<<SYS_GPD_MFP_PD3MFP_Pos)     /*!< GPD_MFP PD3 setting for GPIO       */
#define SYS_GPD_MFP_PD3_BPWM_CH1    (0x3UL<<SYS_GPD_MFP_PD3MFP_Pos)     /*!< GPD_MFP PD3 setting for BPWM_CH1   */
#define SYS_GPD_MFP_PD3_I2C1_SCL    (0x8UL<<SYS_GPD_MFP_PD3MFP_Pos)     /*!< GPD_MFP PD3 setting for I2C1_SCL   */
#define SYS_GPD_MFP_PD3_UART1_TXD   (0xBUL<<SYS_GPD_MFP_PD3MFP_Pos)     /*!< GPD_MFP PD3 setting for UART1_TXD  */

/*  PD.4*/
#define SYS_GPD_MFP_PD4_GPIO        (0x0UL<<SYS_GPD_MFP_PD4MFP_Pos)     /*!< GPD_MFP PD4 setting for GPIO       */
#define SYS_GPD_MFP_PD4_BPWM_CH0    (0x3UL<<SYS_GPD_MFP_PD4MFP_Pos)     /*!< GPD_MFP PD4 setting for BPWM_CH0   */
#define SYS_GPD_MFP_PD4_I2C1_SDA    (0x8UL<<SYS_GPD_MFP_PD4MFP_Pos)     /*!< GPD_MFP PD4 setting for I2C1_SDA   */
#define SYS_GPD_MFP_PD4_UART1_RXD   (0xBUL<<SYS_GPD_MFP_PD4MFP_Pos)     /*!< GPD_MFP PD4 setting for UART1_RXD  */
#define SYS_GPD_MFP_PD4_ECAP0       (0xCUL<<SYS_GPD_MFP_PD4MFP_Pos)     /*!< GPD_MFP PD4 setting for ECAP0      */

/* PD.5 */
#define SYS_GPD_MFP_PD5_GPIO        (0x0UL<<SYS_GPD_MFP_PD5MFP_Pos)     /*!< GPD_MFP PD5 setting for GPIO       */
#define SYS_GPD_MFP_PD5_ICE_DAT     (0x1UL<<SYS_GPD_MFP_PD5MFP_Pos)     /*!< GPD_MFP PD5 setting for ICE_DAT    */
#define SYS_GPD_MFP_PD5_ECAP1       (0xCUL<<SYS_GPD_MFP_PD5MFP_Pos)     /*!< GPD_MFP PD5 setting for ECAP1      */
#define SYS_GPD_MFP_PD5_UART1_TXD   (0xEUL<<SYS_GPD_MFP_PD5MFP_Pos)     /*!< GPD_MFP PD5 setting for UART1_TXD  */
#define SYS_GPD_MFP_PD5_UART2_TXD   (0xFUL<<SYS_GPD_MFP_PD5MFP_Pos)     /*!< GPD_MFP PD5 setting for UART2_TXD  */

/* PD.6 */
#define SYS_GPD_MFP_PD6_GPIO        (0x0UL<<SYS_GPD_MFP_PD6MFP_Pos)     /*!< GPD_MFP PD6 setting for GPIO       */
#define SYS_GPD_MFP_PD6_I2C2_SDA    (0x8UL<<SYS_GPD_MFP_PD6MFP_Pos)     /*!< GPD_MFP PD6 setting for I2C2_SDA   */
#define SYS_GPD_MFP_PD6_SPI1_SS     (0xAUL<<SYS_GPD_MFP_PD6MFP_Pos)     /*!< GPD_MFP PD6 setting for SPI1_SS    */
#define SYS_GPD_MFP_PD6_ECAP2       (0xCUL<<SYS_GPD_MFP_PD6MFP_Pos)     /*!< GPD_MFP PD6 setting for ECAP2      */
#define SYS_GPD_MFP_PD6_UART1_RXD   (0xEUL<<SYS_GPD_MFP_PD6MFP_Pos)     /*!< GPD_MFP PD6 setting for UART1_RXD  */
#define SYS_GPD_MFP_PD6_UART2_RXD   (0xFUL<<SYS_GPD_MFP_PD6MFP_Pos)     /*!< GPD_MFP PD6 setting for UART2_RXD  */

/* PD.7 */
#define SYS_GPD_MFP_PD7_GPIO        (0x0UL<<SYS_GPD_MFP_PD7MFP_Pos)     /*!< GPD_MFP PD7 setting for GPIO       */
#define SYS_GPD_MFP_PD7_ECAP0       (0x7UL<<SYS_GPD_MFP_PD7MFP_Pos)     /*!< GPD_MFP PD7 setting for ECAP0      */
#define SYS_GPD_MFP_PD7_I2C2_SCL    (0x8UL<<SYS_GPD_MFP_PD7MFP_Pos)     /*!< GPD_MFP PD7 setting for I2C2_SCL   */
#define SYS_GPD_MFP_PD7_SPI1_CLK    (0xAUL<<SYS_GPD_MFP_PD7MFP_Pos)     /*!< GPD_MFP PD7 setting for SPI1_CLK   */
#define SYS_GPD_MFP_PD7_UART2_TXD   (0xBUL<<SYS_GPD_MFP_PD7MFP_Pos)     /*!< GPD_MFP PD7 setting for UART2_TXD  */
#define SYS_GPD_MFP_PD7_ECAP2       (0xCUL<<SYS_GPD_MFP_PD7MFP_Pos)     /*!< GPD_MFP PD7 setting for ECAP2      */

/********************* Bit definition of GPE_MFP register **********************/
/* PE.0 */
#define SYS_GPE_MFP_PE0_GPIO        (0x0UL<<SYS_GPE_MFP_PE0MFP_Pos)     /*!< GPE_MFP PE0 setting for GPIO       */
#define SYS_GPE_MFP_PE0_I2C1_SCL    (0x8UL<<SYS_GPE_MFP_PE0MFP_Pos)     /*!< GPE_MFP PE0 setting for I2C1_SCL   */
#define SYS_GPE_MFP_PE0_SPI1_MISO   (0xAUL<<SYS_GPE_MFP_PE0MFP_Pos)     /*!< GPE_MFP PE0 setting for SPI1_MISO  */
#define SYS_GPE_MFP_PE0_UART2_RXD   (0xBUL<<SYS_GPE_MFP_PE0MFP_Pos)     /*!< GPE_MFP PE0 setting for UART2_RXD  */
#define SYS_GPE_MFP_PE0_ECAP0       (0xCUL<<SYS_GPE_MFP_PE0MFP_Pos)     /*!< GPE_MFP PE0 setting for ECAP0      */

/* PE.1 */
#define SYS_GPE_MFP_PE1_GPIO        (0x0UL<<SYS_GPE_MFP_PE1MFP_Pos)     /*!< GPE_MFP PE1 setting for GPIO       */
#define SYS_GPE_MFP_PE1_I2C1_SDA    (0x8UL<<SYS_GPE_MFP_PE1MFP_Pos)     /*!< GPE_MFP PE1 setting for I2C1_SDA   */
#define SYS_GPE_MFP_PE1_SPI1_MOSI   (0xAUL<<SYS_GPE_MFP_PE1MFP_Pos)     /*!< GPE_MFP PE1 setting for SPI1_MOSI  */
#define SYS_GPE_MFP_PE1_ECAP1       (0xCUL<<SYS_GPE_MFP_PE1MFP_Pos)     /*!< GPE_MFP PE1 setting for ECAP1      */

/* PE.2 */
#define SYS_GPE_MFP_PE2_GPIO        (0x0UL<<SYS_GPE_MFP_PE2MFP_Pos)     /*!< GPE_MFP PE2 setting for GPIO       */
#define SYS_GPE_MFP_PE2_BPWM_CH1    (0x3UL<<SYS_GPE_MFP_PE2MFP_Pos)     /*!< GPE_MFP PE2 setting for BPWM_CH1   */
#define SYS_GPE_MFP_PE2_OP1_O       (0x6UL<<SYS_GPE_MFP_PE2MFP_Pos)     /*!< GPE_MFP PE2 setting for OP1_O      */
#define SYS_GPE_MFP_PE2_I2C2_SCL    (0x8UL<<SYS_GPE_MFP_PE2MFP_Pos)     /*!< GPE_MFP PE2 setting for I2C2_SCL   */
#define SYS_GPE_MFP_PE2_UART2_TXD   (0xBUL<<SYS_GPE_MFP_PE2MFP_Pos)     /*!< GPE_MFP PE2 setting for UART2_TXD  */

/* PE.3 */
#define SYS_GPE_MFP_PE3_GPIO        (0x0UL<<SYS_GPE_MFP_PE3MFP_Pos)     /*!< GPE_MFP PE3 setting for GPIO       */
#define SYS_GPE_MFP_PE3_ADC1_P8     (0x2UL<<SYS_GPE_MFP_PE3MFP_Pos)     /*!< GPE_MFP PE3 setting for ADC1_P8    */
#define SYS_GPE_MFP_PE3_OP1_N       (0x6UL<<SYS_GPE_MFP_PE3MFP_Pos)     /*!< GPE_MFP PE3 setting for OP1_N      */
#define SYS_GPE_MFP_PE3_T1          (0x7UL<<SYS_GPE_MFP_PE3MFP_Pos)     /*!< GPE_MFP PE3 setting for T1         */
#define SYS_GPE_MFP_PE3_I2C2_SDA    (0x8UL<<SYS_GPE_MFP_PE3MFP_Pos)     /*!< GPE_MFP PE3 setting for I2C2_SDA   */
#define SYS_GPE_MFP_PE3_UART2_RXD   (0xBUL<<SYS_GPE_MFP_PE3MFP_Pos)     /*!< GPE_MFP PE3 setting for UART2_RXD  */

/* PE.4 */
#define SYS_GPE_MFP_PE4_GPIO        (0x0UL<<SYS_GPE_MFP_PE4MFP_Pos)     /*!< GPE_MFP PE4 setting for GPIO       */
#define SYS_GPE_MFP_PE4_ADC1_P9     (0x2UL<<SYS_GPE_MFP_PE4MFP_Pos)     /*!< GPE_MFP PE4 setting for ADC1_P9    */
#define SYS_GPE_MFP_PE4_OP1_P       (0x6UL<<SYS_GPE_MFP_PE4MFP_Pos)     /*!< GPE_MFP PE4 setting for OP1_P      */

/* PE.5 */
#define SYS_GPE_MFP_PE5_GPIO        (0x0UL<<SYS_GPE_MFP_PE5MFP_Pos)     /*!< GPE_MFP PE5 setting for GPIO       */
#define SYS_GPE_MFP_PE5_BPWM_CH0    (0x3UL<<SYS_GPE_MFP_PE5MFP_Pos)     /*!< GPE_MFP PE5 setting for BPWM_CH0   */
#define SYS_GPE_MFP_PE5_I2C1_SCL    (0x8UL<<SYS_GPE_MFP_PE5MFP_Pos)     /*!< GPE_MFP PE5 setting for I2C1_SCL   */
#define SYS_GPE_MFP_PE5_SPI1_CLK    (0xAUL<<SYS_GPE_MFP_PE5MFP_Pos)     /*!< GPE_MFP PE5 setting for SPI1_CLK   */
#define SYS_GPE_MFP_PE5_UART1_TXD   (0xBUL<<SYS_GPE_MFP_PE5MFP_Pos)     /*!< GPE_MFP PE5 setting for UART1_TXD  */

/* PE.6 */
#define SYS_GPE_MFP_PE6_GPIO        (0x0UL<<SYS_GPE_MFP_PE6MFP_Pos)     /*!< GPE_MFP PE6 setting for GPIO       */
#define SYS_GPE_MFP_PE6_T0          (0x7UL<<SYS_GPE_MFP_PE6MFP_Pos)     /*!< GPE_MFP PE6 setting for T0         */
#define SYS_GPE_MFP_PE6_I2C1_SDA    (0x8UL<<SYS_GPE_MFP_PE6MFP_Pos)     /*!< GPE_MFP PE6 setting for I2C1_SDA   */
#define SYS_GPE_MFP_PE6_SPI1_MISO   (0xAUL<<SYS_GPE_MFP_PE6MFP_Pos)     /*!< GPE_MFP PE6 setting for SPI1_MISO  */
#define SYS_GPE_MFP_PE6_UART1_RXD   (0xBUL<<SYS_GPE_MFP_PE6MFP_Pos)     /*!< GPE_MFP PE6 setting for UART1_RXD  */

/* PE.7 */
#define SYS_GPE_MFP_PE7_GPIO        (0x0UL<<SYS_GPE_MFP_PE7MFP_Pos)     /*!< GPE_MFP PE7 setting for GPIO       */
#define SYS_GPE_MFP_PE7_I2C2_SCL    (0x8UL<<SYS_GPE_MFP_PE7MFP_Pos)     /*!< GPE_MFP PE7 setting for I2C2_SCL   */
#define SYS_GPE_MFP_PE7_SPI1_MOSI   (0xAUL<<SYS_GPE_MFP_PE7MFP_Pos)     /*!< GPE_MFP PE7 setting for SPI1_MOSI  */
#define SYS_GPE_MFP_PE7_UART2_TXD   (0xBUL<<SYS_GPE_MFP_PE7MFP_Pos)     /*!< GPE_MFP PE7 setting for UART2_TXD  */

/********************* Bit definition of GPF_MFP register **********************/
/* PF.0 */
#define SYS_GPF_MFP_PF0_GPIO        (0x0UL<<SYS_GPF_MFP_PF0MFP_Pos)     /*!< GPF_MFP PF0 setting for GPIO       */
#define SYS_GPF_MFP_PF0_I2C2_SDA    (0x8UL<<SYS_GPF_MFP_PF0MFP_Pos)     /*!< GPF_MFP PF0 setting for I2C2_SDA   */
#define SYS_GPF_MFP_PF0_SPI1_SS     (0xAUL<<SYS_GPF_MFP_PF0MFP_Pos)     /*!< GPF_MFP PF0 setting for SPI1_SS    */
#define SYS_GPF_MFP_PF0_UART2_RXD   (0xBUL<<SYS_GPF_MFP_PF0MFP_Pos)     /*!< GPF_MFP PF0 setting for UART2_RXD  */
#define SYS_GPF_MFP_PF0_ECAP0       (0xCUL<<SYS_GPF_MFP_PF0MFP_Pos)     /*!< GPF_MFP PF0 setting for ECAP0      */

/* PF.1 */
#define SYS_GPF_MFP_PF1_GPIO        (0x0UL<<SYS_GPF_MFP_PF1MFP_Pos)     /*!< GPF_MFP PF1 setting for GPIO       */
#define SYS_GPF_MFP_PF1_EPWM_CH3    (0x3UL<<SYS_GPF_MFP_PF1MFP_Pos)     /*!< GPF_MFP PF1 setting for EPWM_CH3   */
#define SYS_GPF_MFP_PF1_I2C2_SCL    (0x8UL<<SYS_GPF_MFP_PF1MFP_Pos)     /*!< GPF_MFP PF1 setting for I2C2_SCL   */
#define SYS_GPF_MFP_PF1_UART2_TXD   (0xBUL<<SYS_GPF_MFP_PF1MFP_Pos)     /*!< GPF_MFP PF1 setting for UART2_TXD  */
#define SYS_GPF_MFP_PF1_ECAP1       (0xCUL<<SYS_GPF_MFP_PF1MFP_Pos)     /*!< GPF_MFP PF1 setting for ECAP1      */

/* PF.2 */
#define SYS_GPF_MFP_PF2_GPIO        (0x0UL<<SYS_GPF_MFP_PF2MFP_Pos)     /*!< GPF_MFP PF2 setting for GPIO       */
#define SYS_GPF_MFP_PF2_ADC0_P8     (0x2UL<<SYS_GPF_MFP_PF2MFP_Pos)     /*!< GPF_MFP PF2 setting for ADC0_P8    */
#define SYS_GPF_MFP_PF2_EPWM_CH2    (0x3UL<<SYS_GPF_MFP_PF2MFP_Pos)     /*!< GPF_MFP PF2 setting for EPWM_CH2   */
#define SYS_GPF_MFP_PF2_I2C2_SDA    (0x8UL<<SYS_GPF_MFP_PF2MFP_Pos)     /*!< GPF_MFP PF2 setting for I2C2_SDA   */
#define SYS_GPF_MFP_PF2_UART2_RXD   (0xBUL<<SYS_GPF_MFP_PF2MFP_Pos)     /*!< GPF_MFP PF2 setting for UART2_RXD  */
#define SYS_GPF_MFP_PF2_ECAP2       (0xCUL<<SYS_GPF_MFP_PF2MFP_Pos)     /*!< GPF_MFP PF2 setting for ECAP2      */

/* PF.3 */
#define SYS_GPF_MFP_PF3_GPIO        (0x0UL<<SYS_GPF_MFP_PF3MFP_Pos)     /*!< GPF_MFP PF3 setting for GPIO       */
#define SYS_GPF_MFP_PF3_ADC1_P3     (0x2UL<<SYS_GPF_MFP_PF3MFP_Pos)     /*!< GPF_MFP PF3 setting for ADC1_P3    */
#define SYS_GPF_MFP_PF3_EPWM_CH1    (0x3UL<<SYS_GPF_MFP_PF3MFP_Pos)     /*!< GPF_MFP PF3 setting for EPWM_CH1   */

/* PF.4 */
#define SYS_GPF_MFP_PF4_GPIO        (0x0UL<<SYS_GPF_MFP_PF4MFP_Pos)     /*!< GPF_MFP PF4 setting for GPIO       */
#define SYS_GPF_MFP_PF4_ADC1_P4     (0x2UL<<SYS_GPF_MFP_PF4MFP_Pos)     /*!< GPF_MFP PF4 setting for ADC1_P4    */
#define SYS_GPF_MFP_PF4_EPWM_CH0    (0x3UL<<SYS_GPF_MFP_PF4MFP_Pos)     /*!< GPF_MFP PF4 setting for EPWM_CH0   */

/*@}*/ /* end of group NM1240_SYS_EXPORTED_CONSTANTS */

/** @addtogroup NM1240_SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/


/**
  * @brief      Clear Brown-out detector interrupt flag
  * @param      None
  * @return     None
  * @details    This macro clear Brown-out detector interrupt flag.
  */
#define SYS_CLEAR_BOD_INT_FLAG()        (SYS->BODCTL |= SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Get Brown-out detector interrupt flag
  * @param      None
  * @retval     0   Brown-out detect interrupt flag is not set.
  * @retval     >=1 Brown-out detect interrupt flag is set.
  * @details    This macro get Brown-out detector interrupt flag.
  */
#define SYS_GET_BOD_INT_FLAG()          ((SYS->BODCTL & SYS_BODCTL_BODIF_Msk) >> SYS_BODCTL_BODIF_Pos)

/**
  * @brief      Enable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_BOD()                (SYS->BODCTL |= SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Disable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro disable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_BOD()               (SYS->BODCTL &= ~SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Enable Low Voltage Reset Low Power mode
  * @param      None
  * @return     None
  * @details    This macro enable Low Voltage Reset Low Power mode.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_LVRLPM()              (SYS->BODCTL |= SYS_BODCTL_LVRLPM_Msk)

/**
  * @brief      Disable Low Voltage Reset Low Power mode
  * @param      None
  * @return     None
  * @details    This macro disable Low Voltage Reset Low Power mode.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_LVRLPM()             (SYS->BODCTL &= ~SYS_BODCTL_LVRLPM_Msk)

/**
  * @brief      Get Brown-out detector status
  * @param      None
  * @retval     0   System voltage is higher than BOD threshold voltage setting or BOD function is disabled.
  * @retval     >=1 System voltage is lower than BOD threshold voltage setting.
  * @details    This macro get Brown-out detector output status.
  *             If the BOD function is disabled, this function always return 0.
  */
#define SYS_GET_BOD_OUTPUT()            (SYS->BODCTL & SYS_BODCTL_BODOUT_Msk)

/**
  * @brief      Disable Brown-out detector reset function
  * @param      None
  * @return     None
  * @details    This macro disable Brown-out detector reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_BOD_RST()           (SYS->BODCTL &= ~SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Enable Brown-out detector reset function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detect reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_BOD_RST()            (SYS->BODCTL |= SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Set Brown-out detector voltage level
  * @param[in]  u32Level is Brown-out voltage level. Including :
  *             - \ref SYS_BODCTL_BOD_VL_2_0V
  *             - \ref SYS_BODCTL_BOD_VL_2_2V
  *             - \ref SYS_BODCTL_BOD_VL_2_4V
  *             - \ref SYS_BODCTL_BOD_VL_2_7V
  *             - \ref SYS_BODCTL_BOD_VL_3_0V
  *             - \ref SYS_BODCTL_BOD_VL_3_7V
  *             - \ref SYS_BODCTL_BOD_VL_4_0V
  *             - \ref SYS_BODCTL_BOD_VL_4_3V
  * @return     None
  * @details    This macro set Brown-out detector voltage level.
  *             The write-protection function should be disabled before using this macro.
  */
#define SYS_SET_BOD_LEVEL(u32Level)     (SYS->BODCTL = (SYS->BODCTL & ~SYS_BODCTL_BODVL_Msk) | (u32Level))

/**
  * @brief      Get reset source is from Brown-out detector reset
  * @param      None
  * @retval     0   Previous reset source is not from Brown-out detector reset
  * @retval     >=1 Previous reset source is from Brown-out detector reset
  * @details    This macro get previous reset source is from Brown-out detect reset or not.
  */
#define SYS_IS_BOD_RST()                (SYS->RSTSTS & SYS_RSTSTS_BODRF_Msk)

/**
  * @brief      Get reset source is from Low-voltage reset
  * @param      None
  * @retval     0   Previous reset source is not from Low-voltage reset
  * @retval     >=1 Previous reset source is from Low-voltage reset
  * @details    This macro get previous reset source is from Low-voltage reset or not.
  */
#define SYS_IS_LVR_RST()                (SYS->RSTSTS & SYS_RSTSTS_LVRF_Msk)

/**
  * @brief      Get reset source is from CPU reset
  * @param      None
  * @retval     0   Previous reset source is not from CPU reset
  * @retval     >=1 Previous reset source is from CPU reset
  * @details    This macro get previous reset source is from CPU reset.
  */
#define SYS_IS_CPU_RST()                (SYS->RSTSTS & SYS_RSTSTS_CPURF_Msk)

/**
  * @brief      Get reset source is from Power-on Reset
  * @param      None
  * @retval     0   Previous reset source is not from Power-on Reset
  * @retval     >=1 Previous reset source is from Power-on Reset
  * @details    This macro get previous reset source is from Power-on Reset.
  */
#define SYS_IS_POR_RST()                (SYS->RSTSTS & SYS_RSTSTS_PORF_Msk)

/**
  * @brief      Get reset source is from reset pin reset
  * @param      None
  * @retval     0   Previous reset source is not from reset pin reset
  * @retval     >=1 Previous reset source is from reset pin reset
  * @details    This macro get previous reset source is from reset pin reset.
  */
#define SYS_IS_RSTPIN_RST()             (SYS->RSTSTS & SYS_RSTSTS_PINRF_Msk)

/**
  * @brief      Get reset source is from system reset
  * @param      None
  * @retval     0   Previous reset source is not from system reset
  * @retval     >=1 Previous reset source is from system reset
  * @details    This macro get previous reset source is from system reset.
  */
#define SYS_IS_SYSTEM_RST()             (SYS->RSTSTS & SYS_RSTSTS_SYSRF_Msk)

/**
  * @brief      Get reset source is from window watch dog reset
  * @param      None
  * @retval     0   Previous reset source is not from window watch dog reset
  * @retval     >=1 Previous reset source is from window watch dog reset
  * @details    This macro get previous reset source is from window watch dog reset.
  */
#define SYS_IS_WDT_RST()                (SYS->RSTSTS & SYS_RSTSTS_WDTRF_Msk)

/**
  * @brief      Get reset source is from hard fault reset
  * @param      None
  * @retval     0   Previous reset source is not from hard fault reset
  * @retval     >=1 Previous reset source is from hard fault reset
  * @details    This macro get previous reset source is from hard fault reset.
  */
#define SYS_IS_HARDFAULT_RST()                (SYS->RSTSTS & SYS_RSTSTS_HARDFAULRF_Msk)

/**
  * @brief      Disable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_LVR()               (SYS->BODCTL &= ~SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Enable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_LVR()                (SYS->BODCTL |= SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Disable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_POR()               (SYS->PORCTL = 0x5AA5)

/**
  * @brief      Enable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_POR()                (SYS->PORCTL = 0)

/**
  * @brief      Clear reset source flag
  * @param[in]  u32RstSrc is reset source. Including:
  *             - \ref SYS_RSTSTS_HARDFAULRF_Msk
  *             - \ref SYS_RSTSTS_CPURF_Msk
  *             - \ref SYS_RSTSTS_SYSRF_Msk
  *             - \ref SYS_RSTSTS_BODRF_Msk
  *             - \ref SYS_RSTSTS_LVRF_Msk
  *             - \ref SYS_RSTSTS_WDTRF_Msk
  *             - \ref SYS_RSTSTS_PINRF_Msk
  *             - \ref SYS_RSTSTS_PORF_Msk
  * @return     None
  * @details    This macro clear reset source flag.
  */
#define SYS_CLEAR_RST_SOURCE(u32RstSrc) (SYS->RSTSTS |= (u32RstSrc))

/**
  * @brief      Disable register write-protection function
  * @param      None
  * @return     None
  * @details    This function disable register write-protection function.
  *             To unlock the protected register to allow write access.
  */
__STATIC_INLINE void SYS_UnlockReg(void)
{
    UNLOCKREG();
}

/**
  * @brief      Enable register write-protection function
  * @param      None
  * @return     None
  * @details    This function is used to enable register write-protection function.
  *             To lock the protected register to forbid write access.
  */
__STATIC_INLINE void SYS_LockReg(void)
{
    LOCKREG();
}

void     SYS_ClearResetSrc(uint32_t u32Src);
uint32_t SYS_GetBODStatus(void);
uint32_t SYS_GetResetSrc(void);
uint32_t SYS_IsRegLocked(void);
void     SYS_LockReg(void);
void     SYS_UnlockReg(void);
uint32_t SYS_ReadPDID(void);
void     SYS_ResetChip(void);
void     SYS_ResetCPU(void);
void     SYS_ResetGDMA(void);
void     SYS_ResetModule(uint32_t u32ModuleIndex);
void     SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel);
void     SYS_DisableBOD(void);


/*@}*/ /* end of group NM1240_SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NM1240_SYS_Driver */

/*@}*/ /* end of group NM1240_Device_Driver */


#ifdef __cplusplus
}
#endif

#endif /* __SYS_H__ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
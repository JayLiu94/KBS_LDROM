/**************************************************************************//**
 * @file     ecap.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 2020/06/03 11:32 $
 * @brief    NM1240 ECAP driver source file
 *
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NM1240.h"

/** @addtogroup NM1240_Device_Driver NM1240 Device Driver
  @{
*/

/** @addtogroup NM1240_ECAP_Driver ECAP Driver
  @{
*/


/** @addtogroup NM1240_ECAP_EXPORTED_FUNCTIONS ECAP Exported Functions
  @{
*/

/**
  * @brief      Enable ECAP function
  * @param[in]  ecap        The pointer of the specified ECAP module
  * @param[in]  u32FuncMask Input Capture function select
  *                         - \ref ECAP_DISABLE_COMPARE_RELOAD
  *                         - \ref ECAP_COMPARE_FUNCTION
  *                         - \ref ECAP_RELOAD_FUNCTION
  *                         - \ref ECAP_RELOAD_COMPARE_FUNCTION
  * @return     None
  * @details    This macro enable input capture function and select compare and reload function.
  */
void ECAP_Open(ECAP_T* ecap, uint32_t u32FuncMask)
{
    /* Clear Input capture mode*/
    ecap->CTL0 = ecap->CTL0 & ~(ECAP_CTL0_RLDEN_Msk | ECAP_CTL0_CMPEN_Msk);

    /* Enable Input Capture and set mode */
    ecap->CTL0 |= ECAP_CTL0_CAPEN_Msk |
                  ((u32FuncMask) << ECAP_CTL0_RLDEN_Pos);
}

/**
  * @brief      Disable whole ECAP module
  * @param[in]  ecap    The pointer of the specified ECAP module
  * @return     None
  * @details    This macro disable input capture function.
  */
void ECAP_Close(ECAP_T *ecap)
{
    ecap->CTL0 &= ~ECAP_CTL0_CAPEN_Msk;
}

/**
  * @brief      This function is used to enable input channel interrupt
  * @param[in]  ecap    The pointer of the specified ECAP module
  * @param[in]  u32Mask The input channel Mask
  *                     - \ref ECAP_CTL0_CAPTF0IEN_Msk
  *                     - \ref ECAP_CTL0_CAPTF1IEN_Msk
  *                     - \ref ECAP_CTL0_CAPTF2IEN_Msk
  *                     - \ref ECAP_CTL0_CAPOVIEN_Msk
  *                     - \ref ECAP_CTL0_CAPCMPIEN_Msk
  * @return     None
  * @details    This macro will enable the input channel interrupt.
  */
void ECAP_EnableINT(ECAP_T* ecap, uint32_t u32Mask)
{
    /* Enable input channel interrupt */
    ecap->CTL0 |= u32Mask;

    /* Enable NVIC ECAP IRQ */
    NVIC_EnableIRQ(ECAP_IRQn);
}

/**
  * @brief      This function is used to disable input channel interrupt
  * @param[in]  ecap    The pointer of the specified ECAP module
  * @param[in]  u32Mask The input channel number
  *                     - \ref ECAP_CTL0_CAPTF0IEN_Msk
  *                     - \ref ECAP_CTL0_CAPTF1IEN_Msk
  *                     - \ref ECAP_CTL0_CAPTF2IEN_Msk
  *                     - \ref ECAP_CTL0_CAPOVIEN_Msk
  *                     - \ref ECAP_CTL0_CAPCMPIEN_Msk
  * @return     None
  * @details    This macro will disable the input channel_n interrupt.
  */
void ECAP_DisableINT(ECAP_T* ecap, uint32_t u32Mask)
{
    /* Disable input channel interrupt */
    ecap->CTL0 &= ~u32Mask;

    /* Disable NVIC ECAP IRQ */
    NVIC_DisableIRQ(ECAP_IRQn);
}

/*@}*/ /* end of group NM1240_ECAP_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NM1240_ECAP_Driver */

/*@}*/ /* end of group NM1240_Device_Driver */

/*** (C) COPYRIGHT 2020 Nuvoton Technology Corp. ***/

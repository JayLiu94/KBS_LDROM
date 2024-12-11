/**************************************************************************//**
 * @file     fmc.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 2020/06/08 11:32 $
 * @brief    NM1240 series FMC driver source file
 *
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/  

//* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "NM1240.h"
#include "fmc.h"

/** @addtogroup NM1240_Device_Driver NM1240 Device Driver
  @{
*/

/** @addtogroup NM1240_FMC_Driver FMC Driver
  @{
*/


/** @addtogroup NM1240_FMC_EXPORTED_FUNCTIONS FMC Exported Functions
  @{
*/



/**
  * @brief    Disable all FMC functions
  *
  * @return   None
  */
void FMC_Close(void)
{
    FMC->ISPCTL &= ~FMC_ISPCTL_ISPEN_Msk;
}


/**
  * @brief    Erase a page. The page size is 512 bytes. 
  * @param[in]    u32PageAddr   Flash page address. Must be a 512-byte aligned address.
  * @retval   0   Success
  * @retval   -1   Erase failed
  */
int32_t FMC_Erase(uint32_t u32PageAddr)
{
    FMC->ISPCMD = FMC_ISPCMD_PAGE_ERASE;
    FMC->ISPADDR = u32PageAddr;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;

    if (FMC->ISPCTL & FMC_ISPCTL_ISPFF_Msk)
    {
        FMC->ISPCTL |= FMC_ISPCTL_ISPFF_Msk;
        return -1;
    }
    return 0;
}


/**
  * @brief Execute FMC_ISPCMD_PAGE_ERASE command to erase SPROM. The page size is 512 bytes.
  * @param[in]    u32PageAddr   SPROM Flash page address. Must be a 512-byte aligned address.
  * @return   SPROM page erase success or not.
  * @retval   0  Success
  * @retval   -1  Erase failed
  */
int32_t FMC_Erase_SPROM(uint32_t u32PageAddr)
{
    FMC->ISPCMD = FMC_ISPCMD_PAGE_ERASE;
    FMC->ISPADDR = u32PageAddr;
    FMC->ISPDAT = 0x0055AA03;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;

    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;

    if (FMC->ISPCTL & FMC_ISPCTL_ISPFF_Msk) {
        FMC->ISPCTL |= FMC_ISPCTL_ISPFF_Msk;
        return -1;
    }
    return 0;
}


/**
  * @brief    get the current boot source
  * @retval   0   This chip is currently booting from APROM
  * @retval   1   This chip is currently booting from LDROM
  */
int32_t FMC_GetBootSource (void)
{
    if (FMC->ISPCTL & FMC_ISPCTL_BS_Msk)
        return 1;
    else
        return 0;
}


/**
  * @brief    Enable FMC ISP function
  */
void FMC_Open(void)
{
    FMC->ISPCTL |=  FMC_ISPCTL_ISPEN_Msk;
}


/**
  * @brief    Read a word from specified flash address. 
  * @param[in]    u32Addr   Flash word address. Must be a word aligned address.
  * @return       The word data stored in the flash address "u32Addr".
  */
uint32_t FMC_Read(uint32_t u32Addr)
{ 

    FMC->ISPCMD = FMC_ISPCMD_READ;
    FMC->ISPADDR = u32Addr;

    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 

    while ((FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) || (FMC->ISPSTS & FMC_ISPSTS_ISPBUSY_Msk)) ;
    // while ((tout-- > 0) && (FMC->ISPTRG)) {}
    // if (tout <= 0)
    // {
    //     uart_send_string(UUART2, "\nFMC_Read tout <= 0\n");
    //     g_FMC_i32ErrCode = -1;
    //     return 0xFFFFFFFF;
    // }
    // {
    //   if (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk)
    //     {
    //         uart_send_string(UUART2, "ISPGO: 1, ");
    //     }
    //     else
    //     {
    //         uart_send_string(UUART2, "ISPGO: 0, ");
    //     }

       
    //     if (FMC->ISPSTS & FMC_ISPSTS_ISPBUSY_Msk)
    //     {
    //         uart_send_string(UUART2, "ISPBUSY: 1\n");
    //     }
    //     else
    //     {
    //         uart_send_string(UUART2, "ISPBUSY: 0\n");
    //     }
    // }
    // uart_send_string(UUART2, "FMC_Read ISPADDR: 0x");
    // uart_send_hex(UUART2, FMC->ISPADDR, 4);
    // uart_send_char(UUART2, '\n');
    // uart_send_string(UUART2, "FMC_Read ISPDAT: 0x");
    // uart_send_hex(UUART2, FMC->ISPDAT, 4);
    // uart_send_char(UUART2, '\n');
    return FMC->ISPDAT;
}


/**
  * @brief    Read company ID.
  * @return   The company ID.
  */
uint32_t FMC_ReadCID(void)  
{
    FMC->ISPCMD = FMC_ISPCMD_READ_CID;
    FMC->ISPADDR = 0x0;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;
    return FMC->ISPDAT; 
}


/**
  * @brief    Read product ID.
  * @return   The product ID.
  */
uint32_t FMC_ReadPID(void)  
{
    FMC->ISPCMD = FMC_ISPCMD_READ_PID;
    FMC->ISPADDR = 0x04;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;
    return FMC->ISPDAT; 
}



/**
  * @brief    This function reads one of the four UCID. 
  * @param[in]    u32Index   index of the UCID to read. u32Index must be 0, 1, 2, or 3. 
  * @return   The UCID.
  */
uint32_t FMC_ReadUCID(uint32_t u32Index)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_UID;
    FMC->ISPADDR = (0x04 * u32Index) + 0x10;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;

    return FMC->ISPDAT; 
}


/**
  * @brief    This function reads one of the three UID. 
  * @param[in]    u32Index  Index of the UID to read. u32Index must be 0, 1, or 2. 
  * @return   The UID.
  */
uint32_t FMC_ReadUID(uint32_t u32Index)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_UID;
    FMC->ISPADDR = 0x04 * u32Index;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;

    return FMC->ISPDAT; 
}


/**
  * @brief    Get the base address of Data Flash if enabled.
  * @return   The base address of Data Flash
  */
uint32_t FMC_ReadDataFlashBaseAddr(void)
{
    return FMC->DFBA; 
}


/**
  * @brief    Set the base address of Data Flash if enabled.
  * @return   The base address of Data Flash
  */
int32_t FMC_SetDataFlashBase(uint32_t u32DFBA)
{
    uint32_t au32Config[2];

    /* Read current User Configuration */
    if (FMC_ReadConfig(au32Config, 2) != 0)
        return -1;

    /* Just return when Data Flash has been enabled */
    if ((!(au32Config[0] & 0x1)) && (au32Config[1] == u32DFBA))
        return 0;

    /* Enable User Configuration Update */
    FMC_ENABLE_CFG_UPDATE(); 

    /* Erase User Configuration */
    if (FMC_Erase(FMC_CONFIG_BASE) != 0)
        return -1;

    /* Write User Configuration to Enable Data Flash */
    au32Config[0] &= ~0x1;
    au32Config[1] = u32DFBA;

    if (FMC_WriteConfig(au32Config, 2))
        return -1;

    /* Perform chip reset to make new User Config take effect */
    SYS->IPRST0 |= SYS_IPRST0_CHIPRST_Msk;

    return 0;
}


/**
  * @brief    This function will force re-map assigned flash page to CPU address 0x0.
  * @param[in]    u32PageAddr   Address of the page to be mapped to CPU address 0x0.
  * @return   None
  */
void FMC_SetVectorPageAddr(uint32_t u32PageAddr)
{
    FMC->ISPCMD = FMC_ISPCMD_VECMAP;
    FMC->ISPADDR = u32PageAddr;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;
}


/**
  * @brief    Obtain the current vector page address setting. 
  * @return   The vector page address.
  */
uint32_t FMC_GetVectorPageAddr(void)
{ 
    return (FMC->ISPSTS & 0x0FFFFF00ul);
}


int32_t  g_FMC_i32ErrCode;
/**
  * @brief    Writes a word data to specified flash address.
  * @param[in]   u32Addr  Destination address
  * @param[in]   u32Data  Word data to be written
  * @return   None
  */
int32_t FMC_Write(uint32_t u32Addr, uint32_t u32Data)
{
    //int32_t  tout = FMC_TIMEOUT_WRITE;
    FMC->ISPCMD = FMC_ISPCMD_PROGRAM;
    FMC->ISPADDR = u32Addr;
    FMC->ISPDAT = u32Data;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    while ((FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) || (FMC->ISPSTS & FMC_ISPSTS_ISPBUSY_Msk)) ;
    // {
    //    if (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk)
    //     {
    //         uart_send_string(UUART2, "ISPGO: 1, ");
    //     }
    //     else
    //     {
    //         uart_send_string(UUART2, "ISPGO: 0, ");
    //     }

       
    //     if (FMC->ISPSTS & FMC_ISPSTS_ISPBUSY_Msk)
    //     {
    //         uart_send_string(UUART2, "ISPBUSY: 1\n");
    //     }
    //     else
    //     {
    //         uart_send_string(UUART2, "ISPBUSY: 0\n");
    //     }
    // }
    // uart_send_string(UUART2, "FMC_Write ISPADDR: 0x");
    // uart_send_hex(UUART2, FMC->ISPADDR, 4);
    // uart_send_char(UUART2, '\n');
    // uart_send_string(UUART2, "FMC_Write ISPDAT: 0x");
    // uart_send_hex(UUART2, FMC->ISPDAT, 4);
    // uart_send_char(UUART2, '\n');
    return 0;
}


/**
  * @brief    Read the User Configuration words. 
  * @param[in]    u32Config   The word array to store data.
  * @param[in]    u32Count    Maximum length of "u32Config".
  * @retval   0   Success
  * @retval   -1  Failed
  */
int32_t FMC_ReadConfig(uint32_t *u32Config, uint32_t u32Count)
{ 
	if (u32Count < 1)
		return 0;
		
    u32Config[0] = FMC_Read(FMC_CONFIG_BASE);
    if (u32Count < 2)
        return 0;
        
    u32Config[1] = FMC_Read(FMC_CONFIG_BASE+4);
    return 0;
}


/**
  * @brief    Write User Configuration 
  * @param[in]    u32Config  The word array to store data.
  * @param[in]    u32Count   Maximum length of "u32Config".
  * @retval   0   Success
  * @retval   -1  Failed
  */
int32_t FMC_WriteConfig(uint32_t *u32Config, uint32_t u32Count)
{       
	if (u32Count < 1)
		return 0;

    FMC_ENABLE_CFG_UPDATE();   
    FMC_Erase(FMC_CONFIG_BASE);
    FMC_Write(FMC_CONFIG_BASE, u32Config[0]);

	if (u32Count < 2)
		return 0;

    FMC_Write(FMC_CONFIG_BASE+4, u32Config[1]);
    FMC_DISABLE_CFG_UPDATE();
    return 0;
}


/**
  * @brief    Calculate and read the CRC32 checksum of a specified flash area. 
  * @param[in]    addr     Start address of the flash area to be executed CRC32 checksum calculation.
  * @param[in]    count    Number of bytes to be calculated.
  * @param[out]   chksum   If success, it will contain the result of CRC32 checksum calculation.
  * @retval   0   Success
  * @retval   -1  Invalid parameter.
  */
int32_t FMC_GetCRC32Sum(uint32_t addr, uint32_t count, uint32_t *chksum)
{
    FMC->ISPCMD = FMC_ISPCMD_CAL_CRC32;
    FMC->ISPADDR = addr;
    FMC->ISPDAT  = count;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;

    if (FMC->ISPCTL & FMC_ISPCTL_ISPFF_Msk)
    {
        FMC->ISPCTL |= FMC_ISPCTL_ISPFF_Msk;
        return -1;
    }

    FMC->ISPCMD = FMC_ISPCMD_READ_CRC32;
    FMC->ISPADDR = addr;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk; 
    
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;

    if (FMC->ISPCTL & FMC_ISPCTL_ISPFF_Msk)
    {
        FMC->ISPCTL |= FMC_ISPCTL_ISPFF_Msk;
        return -1;
    }
    
    *chksum = FMC->ISPDAT;
    
    return 0;
}


/*@}*/ /* end of group NM1240_FMC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NM1240_FMC_Driver */

/*@}*/ /* end of group NM1240_Device_Driver */



/*** (C) COPYRIGHT 2020 Nuvoton Technology Corp. ***/

/*-----------------------------------------------------------------------------------------------------------
 *  Nuvoton Technology Corporation Confidential
 *
 *  Copyright (c) 2018-2022 by Nuvoton Technology Corporation
 *  All rights reserved
 *
 *<<<----------------------------------------------------------------------------------------------------->>>
 * Filename: aprom_isp.h
 *      The keyboard matrix scan task handlers
 *
 * Project:
 *            Nuvoton Embedded Controller Firmware
 *---------------------------------------------------------------------------------------------------------*/

#ifndef __APROM_ISP_H__
#define __APROM_ISP_H__

#include <stdbool.h>

#define FMC_APROM_STATUS_NONE               0x00
#define FMC_APROM_STATUS_PASS               0x00
#define FMC_APROM_STATUS_OUT_OF_RANGE       0x01
#define FMC_APROM_STATUS_NOT_PAGE_ALIGN     0x02
#define FMC_APROM_STATUS_NOT_WORD_ALIGN     0x02
#define FMC_APROM_STATUS_ERASE_FAIL         0x04
#define FMC_APROM_STATUS_ERASE_CHECK_FAIL   0x03
#define FMC_APROM_STATUS_PROGRAM_CHECK_FAIL   0x03

void Enable_FMC_ISP_Function(void);
void Disable_FMC_ISP_Function(void);
void Enable_APROM_ISP_Function(void);
void Disable_APROM_ISP_Function(void);
int FMC_APROM_Erase_Check(uint32_t rom_addr, uint32_t rom_size);
int FMC_APROM_Erase(uint32_t rom_addr, uint32_t rom_size);
int FMC_APROM_Write(uint32_t rom_addr, uint32_t rom_size, uint32_t *rom_data);
bool FMC_ISP_Config_Vector_Base(uint32_t base_addr);

void PrintFlashData(uint32_t u32StartAddr, uint32_t u32EndAddr);
int32_t SetDataFlashBase(uint32_t u32DFBA);
int32_t FillDataPattern(uint32_t u32StartAddr, uint32_t u32EndAddr, uint32_t u32Pattern);
int32_t VerifyData(uint32_t u32StartAddr, uint32_t u32EndAddr, uint32_t u32Pattern);
uint32_t FlashTest(uint32_t u32StartAddr, uint32_t u32EndAddr, uint32_t u32Pattern);
uint32_t FMC_APROM_Flash(uint32_t ApStartAddr, uint32_t ApEndAddr,uint32_t DataEndAddr);

//typedef enum {
//
//    FLASH_ERASE_ERROR      ,
//    FLASH_VERIFY_FAIL      ,
//    //FLASH_WRITE_PAGE_FAIL  ,
//    FLASH_DATA_VERIFY_FAIL ,
//    FLASH_READ_FAIL        ,
//    FLASH_READ_VERIFY_FAIL ,
//    FLASH_WRITE_ERROR
//} FlashErrorCode;



#endif /* __APROM_ISP_H__ */

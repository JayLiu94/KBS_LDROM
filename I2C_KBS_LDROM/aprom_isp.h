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

#endif /* __APROM_ISP_H__ */

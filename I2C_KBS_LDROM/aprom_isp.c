/******************************************************************************
 * @file     aprom_isp.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 2020/08/07 14:36p $
 * @brief   NM1240 GDMA I2C SLAVE test
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "prj_config.h"

void Enable_FMC_ISP_Function(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Enable FMC ISP function */
    FMC_Open();
}

void Disable_FMC_ISP_Function(void)
{
    /* Disable FMC ISP function */
    FMC_Close();
    /* Lock protected registers */
    SYS_LockReg();
}

void Enable_APROM_ISP_Function(void)
{
     /* Unlock protected registers */
    SYS_UnlockReg();
    /* Enable FMC ISP function */
    FMC_Open();
    
    FMC_ENABLE_AP_UPDATE();
}

void Disable_APROM_ISP_Function(void)
{
    FMC_DISABLE_AP_UPDATE();

    /* Disable FMC ISP function */
    FMC_Close();
    /* Lock protected registers */
    SYS_LockReg();
}

int FMC_APROM_Erase_Check(uint32_t rom_addr, uint32_t rom_size)
{
    uint32_t    rom_data;
    
    while(rom_size)
    {
        rom_data = FMC_Read(rom_addr);
        if(rom_data != 0xFFFFFFFF)
        {
            uart_send_string(UUART2, "FMC data erase verify error at addr: ");
            uart_send_hex(UUART2, rom_addr, 4);
            uart_send_string(UUART2, " , read = ");
            uart_send_hex(UUART2, rom_data, 1);
            uart_send_char(UUART2, '\n');
            uart_wait_send_done(UUART2);

            return(FMC_APROM_STATUS_ERASE_CHECK_FAIL);
        }

        rom_addr += 4;
        rom_size -= 4;
    }

    return(FMC_APROM_STATUS_PASS);
}

int FMC_APROM_Erase(uint32_t rom_addr, uint32_t rom_size)
{
    int erase_sts;

    if((rom_addr >= FMC_APROM_END) || ((rom_addr + rom_size) >= FMC_APROM_END))
    {
        return(FMC_APROM_STATUS_OUT_OF_RANGE);
    }

    if((rom_addr % FMC_FLASH_PAGE_SIZE) || ((rom_addr + rom_size) % FMC_FLASH_PAGE_SIZE))
    {
        return(FMC_APROM_STATUS_NOT_PAGE_ALIGN);
    }

    Enable_APROM_ISP_Function();

    while(rom_size)
    {
        erase_sts = FMC_Erase(rom_addr);
        if(erase_sts != 0)
        {
            return(FMC_APROM_STATUS_ERASE_FAIL);
        }

        erase_sts = FMC_APROM_Erase_Check(rom_addr, FMC_FLASH_PAGE_SIZE);
        if(erase_sts != FMC_APROM_STATUS_PASS)
        {
            return(erase_sts);
        }

        rom_addr += FMC_FLASH_PAGE_SIZE;
        rom_size -= FMC_FLASH_PAGE_SIZE;
    }

    Disable_APROM_ISP_Function();

    return(FMC_APROM_STATUS_PASS);
}

int FMC_APROM_Write(uint32_t rom_addr, uint32_t rom_size, uint32_t *rom_data)
{
    uint32_t write_addr;
    uint32_t *data_ptr;
    uint32_t data;

    if((rom_addr >= FMC_APROM_END) || ((rom_addr + rom_size) >= FMC_APROM_END))
    {
        return(FMC_APROM_STATUS_OUT_OF_RANGE);
    }

    if((rom_addr % 4) || ((rom_addr + rom_size) % 4))
    {
        return(FMC_APROM_STATUS_NOT_WORD_ALIGN);
    }

    Enable_APROM_ISP_Function();

    data_ptr = rom_data;
    for(write_addr = rom_addr; write_addr < (rom_addr + rom_size); write_addr += 4)
    {
        FMC_Write(write_addr, *data_ptr);
        *data_ptr += 4;
    }

    data_ptr = rom_data;
    for(write_addr = rom_addr; write_addr < (rom_addr + rom_size); write_addr += 4)
    {
        data = FMC_Read(write_addr);
        if(data != *data_ptr)
        {
            uart_send_string(UUART2, "FMC data write verify error at addr: ");
            uart_send_hex(UUART2, write_addr, 4);
            uart_send_string(UUART2, " , read = ");
            uart_send_hex(UUART2, data, 1);
            uart_send_char(UUART2, '\n');
            uart_wait_send_done(UUART2);

            Disable_APROM_ISP_Function();

            return(FMC_APROM_STATUS_PROGRAM_CHECK_FAIL);
        }

        *data_ptr += 4;
    }

    Disable_APROM_ISP_Function();

    return(FMC_APROM_STATUS_PASS);
}

bool FMC_ISP_Config_Vector_Base(uint32_t base_addr)
{
	/* Mask all interrupt before changing VECMAP to avoid wrong interrupt handler fetched */
   	__set_PRIMASK(1);

    /* Disable all interrupts before change VECMAP */
    NVIC->ICER[0] = 0xFFFFFFFF;

    /* Set Main Stack Pointer register of new boot */
    __set_MSP(FMC_Read(base_addr));

    /* Set vector table of startup AP address */
    FMC_SetVectorPageAddr(base_addr);
    if(FMC_GetVectorPageAddr() != base_addr)
    {
        return(false);
    }

    return(true);
}


/*** (C) COPYRIGHT 2020 Nuvoton Technology Corp. ***/

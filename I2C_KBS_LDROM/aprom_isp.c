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


void PrintFlashData(uint32_t u32StartAddr, uint32_t u32EndAddr)
{
    uint32_t addr;

    uart_send_string(UUART2, "Print Flash Data from 0x");
    uart_send_hex(UUART2, u32StartAddr, 4);
    uart_send_string(UUART2, " to 0x");
    uart_send_hex(UUART2, u32EndAddr, 4);
    uart_send_char(UUART2, '\n');

    for (addr = u32StartAddr; addr < u32EndAddr; addr += 32)
    {
        uint32_t data = FMC_Read(addr);
        uart_send_string(UUART2, "Address: 0x");
        uart_send_hex(UUART2, addr, 4);
        uart_send_char(UUART2, '\n');
        uart_send_string(UUART2, "Data: 0x");
        uart_send_hex(UUART2, data, 8);
        uart_send_char(UUART2, '\n');
    }
}


int32_t FillDataPattern(uint32_t u32StartAddr, uint32_t u32EndAddr, uint32_t u32Pattern)
{
    uint32_t u32Addr;

    for(u32Addr = u32StartAddr; u32Addr < u32EndAddr; u32Addr += 4)
    {
        if (FMC_Write(u32Addr, u32Pattern) != 0)
        {
            uart_send_string(UUART2,"\rFMC_Write address failed!:0x\n");
            uart_send_hex(UUART2, u32Addr, 4);
            return -1;
        }
    }
    return 0;
}


int32_t  VerifyData(uint32_t u32StartAddr, uint32_t u32EndAddr, uint32_t u32Pattern)
{
    uint32_t    u32Addr;
    uint32_t    u32Data;


    for(u32Addr = u32StartAddr; u32Addr < u32EndAddr; u32Addr += 4)
    {
        u32Data = FMC_Read(u32Addr);

        if(u32Data != u32Pattern)
        {
            uart_send_string(UUART2,"FMC_Read data verify failed at address 0x");
            uart_send_hex(UUART2, u32Addr, 4);
            uart_send_char(UUART2, '\n');

            uart_send_string(UUART2,"read=0x");
            uart_send_hex(UUART2, u32Data, 4);
            uart_send_char(UUART2, '\n');

            uart_send_string(UUART2,"expect=0x");
            uart_send_hex(UUART2, u32Pattern, 4);
            uart_send_char(UUART2, '\n');
            return -1;
        }
    }
    return 0;
}


uint32_t FlashTest(uint32_t u32StartAddr, uint32_t u32EndAddr, uint32_t u32Pattern)
{
	uint32_t    u32Addr;

    uart_send_string(UUART2,"Flash test address: 0x");
    uart_send_hex(UUART2, u32StartAddr, 4);
    uart_send_char(UUART2, '\n');
    for(u32Addr = u32StartAddr; u32Addr < u32EndAddr; u32Addr += FMC_FLASH_PAGE_SIZE)
    {

        // Erase page
        if (FMC_Erase(u32Addr) != 0)
        {
            uart_send_string(UUART2,"FMC_Erase address failed : 0x");
            uart_send_hex(UUART2, u32Addr, 4);
            uart_send_char(UUART2, '\n');
            uart_wait_send_done(UUART2);
            return -1;
        }

        // Verify if page contents are all 0xFFFFFFFF
        if (VerifyData(u32Addr, u32Addr + FMC_FLASH_PAGE_SIZE, 0xFFFFFFFF) != 0)
        {
            uart_send_string(UUART2,"FMC_Verify address failed : 0x");
            uart_send_hex(UUART2, u32Addr, 4);
            uart_send_char(UUART2, '\n');
            uart_wait_send_done(UUART2);
            return -1;
        }

        // Write test pattern to fill the whole page
        if(FillDataPattern(u32Addr, u32Addr + FMC_FLASH_PAGE_SIZE, u32Pattern) != 0)
        {
            uart_send_string(UUART2,"FMC_DataPattern address failed : 0x");
            uart_send_hex(UUART2, u32Addr, 4);
            uart_send_char(UUART2, '\n');
            uart_wait_send_done(UUART2);
            return -1;
        }

        // Verify if page contents are all equal to test pattern
        if(VerifyData(u32Addr, u32Addr + FMC_FLASH_PAGE_SIZE, u32Pattern) != 0)
        {
            uart_send_string(UUART2,"\nData verify failed!\r\n ");
            uart_wait_send_done(UUART2);
            return -1;
        }

        
    }
    uart_send_string(UUART2, "Flash Test Passed.Finish addr: 0x");
    uart_send_hex(UUART2, u32Addr, 4);
    uart_send_char(UUART2, '\n');
    uart_wait_send_done(UUART2);

    PrintFlashData(u32StartAddr, u32EndAddr);

    return 0;
}

//ApStartAddr-->FMC_APROM_BASE(0x0000)
//ApEndAddr-->DataFlashBase
//DataEndAddr-->FMC_APROM_END_64K(0x10000)
uint32_t FMC_APROM_Flash(uint32_t ApStartAddr, uint32_t ApEndAddr,uint32_t DataEndAddr)
{
    uint32_t u32Addr;
    uint32_t u32Data;
    uint32_t u32PageAddr;
    uint32_t u32DataFlashAddr;
    if (ApStartAddr > ApEndAddr || ApEndAddr > DataEndAddr) {
        uart_send_string(UUART2, "Address range is invalid.\n");
        return -1;
    }

    //FMC_ENABLE_AP_UPDATE();  
    for (u32PageAddr = ApStartAddr; u32PageAddr < ApEndAddr; u32PageAddr += FMC_FLASH_PAGE_SIZE) 
    {
        if (FMC_Erase(u32PageAddr) != 0) 
        {
            uart_send_string(UUART2, "FMC_Erase failed at address: 0x");
            uart_send_hex(UUART2, u32PageAddr, 4);
            uart_send_char(UUART2, '\n');
            return -1;
        }

        for (uint32_t u32VerifyAddr = u32PageAddr; u32VerifyAddr < u32PageAddr + FMC_FLASH_PAGE_SIZE; u32VerifyAddr += 4) 
        {
            if (FMC_Read(u32VerifyAddr) != 0xFFFFFFFF) 
            {
                uart_send_string(UUART2, "Page verify failed at address: 0x");
                uart_send_hex(UUART2, u32VerifyAddr, 4);
                uart_send_char(UUART2, '\n');
                return -1;
            }
        }
    }


    for (u32Addr = ApStartAddr; u32Addr < ApEndAddr; u32Addr += 4) 
    {
        u32DataFlashAddr = ApEndAddr + (u32Addr - ApStartAddr);
        if (u32DataFlashAddr >= DataEndAddr) {
            uart_send_string(UUART2, "DataFlash address out of range.\n");
            return -1;
        }
        u32Data = FMC_Read(u32DataFlashAddr);

        if (FMC_Write(u32Addr, u32Data) != 0) {
            uart_send_string(UUART2, "FMC_Write failed at address: 0x");
            uart_send_hex(UUART2, u32Addr, 4);
            uart_send_char(UUART2, '\n');
            return -1;
        }


        uint32_t u32VerifyData = FMC_Read(u32Addr);
        if (u32VerifyData != u32Data) {
            uart_send_string(UUART2, "Verify failed at address: 0x");
            uart_send_hex(UUART2, u32Addr, 4);
            uart_send_char(UUART2, '\n');

            uart_send_string(UUART2, "Expected: 0x");
            uart_send_hex(UUART2, u32Data, 8);
            uart_send_string(UUART2, " Read: 0x");
            uart_send_hex(UUART2, u32VerifyData, 8);
            uart_send_char(UUART2, '\n');
            return -1;
        }
    }

    uart_send_string(UUART2, "APROM flashing completed successfully.\n");
    //FMC_DISABLE_AP_UPDATE();

    return 0;       
}
/*** (C) COPYRIGHT 2020 Nuvoton Technology Corp. ***/

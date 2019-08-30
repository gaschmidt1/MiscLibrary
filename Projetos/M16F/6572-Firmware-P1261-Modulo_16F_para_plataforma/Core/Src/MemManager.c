/*
 * MemManager.c
 *
 *  Created on: 13 de fev de 2019
 *      Author: giovani
 */

#include "Flash_F0.h"
#include "Flash.h"
#include "MemManager.h"

#define FIRST_VALUE (uint32_t)  0xA1FF14C2 //0xA1FF14C2

uint32_t FindSlot(uint32_t Address);

static void Clear_Bank(void);

uint32_t Active_Address = 0;

static int32_t Get_Remaining_Space(void);

uint8_t Mem_CheckMemory(void)
{
	uint8_t return_val = 1;
	uint32_t addr_value = Flash_Read_Uint32(FLASH_START_VALUE_ADDR);

	if(addr_value != FIRST_VALUE)
	{
		Flash_Erase(BANK1_WRITE_START_ADDR);
		Flash_Write_Uint32(FLASH_START_VALUE_ADDR,FIRST_VALUE);
		Flash_Write_Uint32(FLASH_START_DATA_ADDR,0x00000000);
		return_val = 0; // memory error,
	}
	Active_Address =  FindSlot(FLASH_START_VALUE_ADDR);
	return return_val;
}

void Mem_Reinit(void)
{
	Flash_Erase(BANK1_WRITE_START_ADDR);
	Flash_Write_Uint32(FLASH_START_VALUE_ADDR,FIRST_VALUE);
	Flash_Write_Uint32(FLASH_START_DATA_ADDR,0x00000000);
	Active_Address =  FindSlot(FLASH_START_VALUE_ADDR);
}

void Mem_GetData(Fake_EEPROM_Typedef *app_data, uint8_t size)
{
	uint32_t i;
	int8_t size_count = size - 1;
	for( i = (Active_Address - 4);size_count >= 0 ;i -= 4)
	{
		app_data->Data_Values[size_count] = Flash_Read_Uint32(i);
		size_count--;
	}
}


void Mem_WriteData(Fake_EEPROM_Typedef *app_data, uint8_t size)
{
	uint8_t size_count = 0;
	if(size > Get_Remaining_Space())
	{
		Clear_Bank();
	}
	for( ;size_count < size ; Active_Address += 4)
	{
		Flash_Write_Uint32(Active_Address,app_data->Data_Values[size_count]);
		size_count++;
	}
}

static void Clear_Bank(void)
{
	Flash_Erase(BANK1_WRITE_START_ADDR);
	Flash_Write_Uint32(FLASH_START_VALUE_ADDR,FIRST_VALUE);
	Active_Address = FindSlot(FLASH_START_VALUE_ADDR);
}

static int32_t Get_Remaining_Space(void)
{
	return (FLASH_END_ADDR - Active_Address );
}

uint32_t FindSlot(uint32_t Address)
{
	uint32_t i;
	uint32_t tmp;
	uint32_t free_slot = 0;
	for(i=(Address + PAGE_SIZE -4); i>=Address; i-=4)
	{
		tmp = Flash_Read_Uint32(i);
		if(tmp!=0xFFFFFFFF)
		{
			free_slot = i + 4;
			break;
		}
	}
	return free_slot;
}


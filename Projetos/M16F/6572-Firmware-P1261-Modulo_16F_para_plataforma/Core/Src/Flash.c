/*
 * Flash.c
 *
 *  Created on: 13 de fev de 2019
 *      Author: giovani
 */




#include "Flash.h"
#include "stm32_hal_legacy.h"


void Flash_WriteBlock(void)
{
	HAL_FLASH_Unlock();

	/* Clear All pending flags */
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_EOP); // | FLASH_FLAG_OPTVERR

	HAL_FLASH_Lock();
}

void Flash_Write_Uint32(uint32_t Address, uint32_t Data)
{
	__disable_irq();

	HAL_FLASH_Unlock();

	/* Clear All pending flags */
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_EOP); // | FLASH_FLAG_OPTVERR

	HAL_FLASH_Program(TYPEPROGRAM_WORD, Address, Data);

	HAL_FLASH_Lock();

	__enable_irq();
}

uint32_t Flash_Read_Uint32(uint32_t Address)
{
	HAL_FLASH_Unlock();

	uint32_t addr = (*(__IO uint32_t*) Address);

	HAL_FLASH_Lock();

	return addr;
}

void Flash_Read_Array(uint32_t Address, uint32_t *data, uint8_t size)
{
	uint8_t i;
	__IO uint32_t *ptr;

	HAL_FLASH_Unlock();

	ptr = (__IO uint32_t*)Address;

	for (i = 0; i < size; i++)
	{
		data[i] = *ptr;
		ptr++;
	}

	HAL_FLASH_Lock();
}


void Flash_Write_Array(uint32_t Address,uint32_t * Data, uint8_t size)
{
	uint8_t i;

	HAL_FLASH_Unlock();

	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_EOP); // | FLASH_FLAG_OPTVERR

	for(i = 0; i < size;i++)
	{
		HAL_FLASH_Program(TYPEPROGRAM_WORD, Address, Data[i]);
		Address += 4;
	}

	HAL_FLASH_Lock();
}


void Flash_Erase(uint32_t PageAddress)
{
	uint32_t PageError = 0;

	FLASH_EraseInitTypeDef EraseInitStruct;

	/* Fill EraseInit structure*/
	EraseInitStruct.TypeErase = TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = PageAddress;
	EraseInitStruct.NbPages = 1;

	HAL_FLASH_Unlock();

	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	HAL_FLASH_Lock();
}

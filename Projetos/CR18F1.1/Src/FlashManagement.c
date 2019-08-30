/*
 * FlashManagement.c
 *
 *  Created on: Aug 23, 2019
 *      Author: gerry
 */

#include "MyFlash.h"
#include "FlashManagement.h"

#define kCheckValue (uint32_t) 0xA1A1A1A1

uint32_t FindSlot(uint32_t Address);

//static void ClearBank(void);

uint32_t ActiveAddress = 0;

//static int32_t GetRemainingSpace(void);

uint8_t MemCheckMemory(void)
{
	uint8_t return_val = 1;
	uint32_t Check = FlashReadU32(kFlashPageCheckAddress);

	if (Check != kCheckValue)
	{
		FlashErase(kFlashPageInitAddress);
		FlashWriteU32(kFlashPageCheckAddress, kCheckValue);
		FlashWriteU32(kFlashStartDataAddress, 0x00000000);
		return_val = 0;
	}
	ActiveAddress = FindSlot(kFlashStartDataAddress);
	return (return_val);
}

void MemReinit(void)
{
	FlashErase(kFlashPageInitAddress);
	FlashWriteU32(kFlashPageCheckAddress, kCheckValue);
	FlashWriteU32(kFlashStartDataAddress, 0x00000000);
	ActiveAddress = FindSlot(kFlashStartDataAddress);
}

//void Mem_GetData(Fake_EEPROM_Typedef *app_data, uint8_t size)
//{
//	uint32_t i;
//	int8_t size_count = size - 1;
//	for( i = (Active_Address - 4);size_count >= 0 ;i -= 4)
//	{
//		app_data->Data_Values[size_count] = Flash_Read_Uint32(i);
//		size_count--;
//	}
//}

//void Mem_WriteData(Fake_EEPROM_Typedef *app_data, uint8_t size)
//{
//	uint8_t size_count = 0;
//	if(size > Get_Remaining_Space())
//	{
//		Clear_Bank();
//	}
//	for( ;size_count < size ; Active_Address += 4)
//	{
//		Flash_Write_Uint32(Active_Address,app_data->Data_Values[size_count]);
//		size_count++;
//	}
//}

//static void ClearBank(void)
//{
//	FlashErase(kFlashPageInitAddress);
//	FlashWriteU32(kFlashStartDataAddress, kCheckValue);
//	ActiveAddress = FindSlot(kFlashStartDataAddress);
//}
//
//static int32_t GetRemainingSpace(void)
//{
//	return (kFlashEndDataAddress - ActiveAddress );
//}

uint32_t FindSlot(uint32_t Address)
{
	uint32_t i;
	uint32_t tmp;
	uint32_t free_slot = 0;
	for (i = (Address + kPageSize - 4); i >= Address; i -= 4)
	{
		tmp = FlashReadU32(i);
		if (tmp != 0xFFFFFFFF)
		{
			free_slot = i + 4;
			break;
		}
	}
	return free_slot;
}

/*
 * MyFlash.h
 *
 *  Created on: 23/08/2019
 *      Author: gerry
 */

#ifndef INC_MyFlash_H_
#define INC_MyFlash_H_

#include "stm32f0xx_hal.h"
//#include "MyTypes.h"

//#define ADDR_FLASH_PAGE   ((uint32_t)0x0800F800)
#define kFlashPageInitAddress   ((uint32_t)0x0800F800)

//#define BANK1_WRITE_START_ADDR 	((uint32_t) ADDR_FLASH_PAGE)
#define kFlashPageEndAddress 	((uint32_t) (ADDR_FLASH_PAGE + 0x7FF))

#define kPageSize			((uint32_t) 0x800)  /* 2kb */

#define kBlockSize 			8

//#define FLASH_START_VALUE_ADDR   BANK1_WRITE_START_ADDR
//#define FLASH_START_DATA_ADDR	(BANK1_WRITE_START_ADDR + 4)

#define kCheckValue (uint32_t) 0xA1A1A1A1

#define kFlashPageCheckAddress	kFlashPageInitAddress
#define kFlashStartDataAddress		kFlashPageInitAddress + 4

#define kFlashEndDataAddress		0x0800FFFF

//void FlashWriteBlock(void);
void FlashWriteU32(uint32_t Address, uint32_t Data);
uint32_t FlashReadU32(uint32_t Address);
void FlashReadArray(uint32_t Address, uint32_t *data, uint8_t size);
void FlashWriteArray(uint32_t Address, uint32_t * Data, uint8_t size);
void FlashErase(uint32_t PageAddress);

#endif /*MyFlash*/


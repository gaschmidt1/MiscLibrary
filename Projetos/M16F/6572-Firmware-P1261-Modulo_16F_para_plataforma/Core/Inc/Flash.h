/*
 * Flash.h
 *
 *  Created on: 13 de fev de 2019
 *      Author: giovani
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "Application_x.h"
#include "main.h"

#define FLASH_START_VALUE_ADDR   BANK1_WRITE_START_ADDR
#define FLASH_START_DATA_ADDR	(BANK1_WRITE_START_ADDR + 4)
#define FLASH_END_ADDR			0x0801F7FF


void Flash_WriteBlock(void);
void Flash_Write_Uint32(uint32_t Address, uint32_t Data);
uint32_t Flash_Read_Uint32(uint32_t Address);
void Flash_Read_Array(uint32_t Address, uint32_t *data, uint8_t size);
void Flash_Write_Array(uint32_t Address, uint32_t * Data, uint8_t size);
void Flash_Erase(uint32_t PageAddress);


#endif /* INC_FLASH_H_ */

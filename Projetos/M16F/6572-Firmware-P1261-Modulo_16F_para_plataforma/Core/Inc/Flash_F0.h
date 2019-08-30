/*
 * Flash_F0.h
 *
 *  Created on: 13 de fev de 2019
 *      Author: giovani
 */

#ifndef INC_FLASH_F0_H_
#define INC_FLASH_F0_H_


#include "stm32f0xx_hal.h"



#define ADDR_FLASH_PAGE_62   ((uint32_t)0x0801F000) /* Base @ of Page 62, 2 Kbyte */

#define BANK1_WRITE_START_ADDR 	((uint32_t) ADDR_FLASH_PAGE_62)
#define BANK1_WRITE_END_ADDR 	((uint32_t) (ADDR_FLASH_PAGE_62 + 0x7FF))

#define PAGE_SIZE 				((uint32_t) 0x800)

#define BLOCK_SIZE 				8


#endif /* INC_FLASH_F0_H_ */

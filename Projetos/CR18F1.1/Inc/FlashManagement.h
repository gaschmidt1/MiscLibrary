
/*
 * FlashManager.h
 *
 *  Created on: 23/08/2019
 *      Author: gerry
 */

#ifndef INC_FlashManagement_H_
#define INC_FlashManagement_H_

#include "MyFlash.h"
#include "stm32f0xx_hal.h"
#include "stm32_hal_legacy.h"

uint8_t MemCheckMemory(void);
//void Mem_Restore(Fake_EEPROM_Typedef *app_data);
//void Mem_GetData(Fake_EEPROM_Typedef *app_data, uint8_t size);
//void Mem_WriteData(Fake_EEPROM_Typedef *app_data, uint8_t size);
void MemReinit(void);

#endif /*  */

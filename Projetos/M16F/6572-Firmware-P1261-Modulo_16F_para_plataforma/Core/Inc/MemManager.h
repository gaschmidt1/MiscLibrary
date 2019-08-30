/*
 * MemManager.h
 *
 *  Created on: 13 de fev de 2019
 *      Author: giovani
 */

#ifndef INC_MEMMANAGER_H_
#define INC_MEMMANAGER_H_
#include "Application_x.h"

uint8_t Mem_CheckMemory(void);
void Mem_Restore(Fake_EEPROM_Typedef *app_data);
void Mem_GetData(Fake_EEPROM_Typedef *app_data, uint8_t size);
void Mem_WriteData(Fake_EEPROM_Typedef *app_data, uint8_t size);
void Mem_Reinit(void);


#endif /* INC_MEMMANAGER_H_ */

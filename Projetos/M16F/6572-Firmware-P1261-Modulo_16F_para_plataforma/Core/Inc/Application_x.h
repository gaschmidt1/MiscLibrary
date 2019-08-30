/*
 * Application_x.h
 *
 *  Created on: 11 de jan de 2019
 *      Author: giovani
 */

#ifndef INC_APPLICATION_X_H_
#define INC_APPLICATION_X_H_


#include "cmsis_os.h"
#include "main.h"
#include "Process.h"


#define NRF905_Signal_Ready 0x01
#define APP_FLASH_VERIFY 0x02

osThreadId appThreadId;
osThreadId inputFilterThreadId;
osThreadId LedRunThreadId;

osPoolId  App_Cmd_DataPool_Id;

#define APP_DEFAULT_VALUES_LOCATION 0x0801EFD8 //E0
#define NRF905_ADDRESS_OFFSET 0

#define APP_BLOCK_SIZE 8

/*
 * #define APP_BLOCK_SIZE 4
 * typedef union
{
	uint32_t Data_Values[APP_BLOCK_SIZE];
	struct
	{
		uint32_t RoscaTuboDesligada:8;
		uint32_t RoscaTuboLigada:8;
		uint32_t RoscaTuboRampa:8;
		uint32_t RoscaElevacaoDesligada:8;

		uint32_t RoscaElevacaoLigada:8;
		uint32_t RoscaElevacaoRampa:8;
		uint32_t RoscaInferiorDesligada:8;
		uint32_t RoscaInferiorLigada:8;

		uint32_t RoscaInferiorRampa:8;
		uint32_t TuboHorario:8;
		uint32_t TuboAntiHorario:8;
		uint32_t TuboParado:8;

		uint32_t TuboRampa:8;
		uint32_t OutrosTempoIgnicao:8;
		uint32_t OutrosTempoMovimentoComportas:8;
		uint32_t OutrosTempoMovimentoUnused:8;
	}Variaveis;
}Fake_EEPROM_Typedef;
 *
 */

typedef union
{
  uint32_t Data_Values[APP_BLOCK_SIZE];
  struct
  {
    uint32_t RoscaTuboDesligada:16;
    uint32_t RoscaTuboLigada:16;
    uint32_t RoscaTuboRampa:16;
    uint32_t RoscaElevacaoDesligada:16;

    uint32_t RoscaElevacaoLigada:16;
    uint32_t RoscaElevacaoRampa:16;
    uint32_t RoscaInferiorDesligada:16;
    uint32_t RoscaInferiorLigada:16;

    uint32_t RoscaInferiorRampa:16;
    uint32_t TuboHorario:16;
    uint32_t TuboAntiHorario:16;
    uint32_t TuboParado:16;

    uint32_t TuboRampa:16;
    uint32_t OutrosTempoIgnicao:16;
    uint32_t OutrosTempoMovimentoComportas:16;
    uint32_t OutrosTempoMovimentoUnused:16;
  }Variaveis;
}Fake_EEPROM_Typedef;

Fake_EEPROM_Typedef *P1178_Variaveis;

osPoolId   AplicacaoDataPool_Id;



void Application_Init(void);

#endif /* INC_APPLICATION_X_H_ */

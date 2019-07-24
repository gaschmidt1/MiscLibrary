/**
 ******************************************************************************
 * File Name          : Inputs.h
 * Description        : This file provides code for the use
 *                      of the In instances.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Inputs_H
#define __Inputs_H



#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
//#include "cmsis_os.h"
#include "../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.h"

/* Defines -------------------------------------------------------------------*/
#define kInputCount 9U
#define kInHisteresis 20

/* Types ---------------------------------------------------------------------*/
typedef enum
{
	In01 = 0,
	In02 = 1,
	In03 = 2,
	In04 = 3,
	In05 = 4,
	In06 = 5,
	In07 = 6,
	In08 = 7,
	In09 = 8
}InputNameType;

typedef enum
{
	ANALOG = 0,
	DIGITAL = 1,
	UNUSEDIN = 3
}InputFunctionType;

typedef enum
{
	InOFF = 0,
	InON = 1
}InputStateType;

typedef struct
{
	uint16_t InAdcValue;
	uint16_t InThreshold;
	uint8_t InDebounceUp;
	uint8_t InDebounceDown;
	uint8_t InDebounceUpCounter;
	uint8_t InDebounceDownCounter;
	InputFunctionType InFunctionType;
	InputStateType InStateAtt;
	InputStateType InStateOld;
}InputStruct;

/* Variables -----------------------------------------------------------------*/
InputStruct InputConf[kInputCount];

uint32_t AdcDmaBuffer[kInputCount];
uint32_t AdcDmaAcc[kInputCount];
uint32_t AdcDmaAverageBuffer[kInputCount];

/* Prototypes ----------------------------------------------------------------*/

void InputsInit(void);
uint8_t InputsGetState(InputNameType InName);
uint16_t InputsGetValue(InputNameType InName);
void InputsPeriodic(void);
void InputsAdcPeriodic(void);


#ifdef __cplusplus
}
#endif
#endif /* __Inputs_H */

/**
 * @}
 */

/**
 * @}
 */

/*****************************END OF FILE****/


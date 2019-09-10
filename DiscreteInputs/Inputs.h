/*
 * Inputs.h
 *
 *  Created on: Aug 2, 2019
 *      Author: gerry
 */

#ifndef SRC_INPUTS_H_
#define SRC_INPUTS_H_

#include "stm32f0xx_hal.h"
#include "MyTypes.h"
#include "main.h"
#include "gpio.h"

/* Defines -------------------------------------------------------------------*/
#define kInputCount 18U
#define kInHisteresis 10

/* Types ---------------------------------------------------------------------*/
typedef enum
{
	In01, In02, In03, In04, In05, In06, In07, In08, In09, In10, In11, In12, In13, In14, In15, In16, In17, In18,
} InputNameType;

typedef struct
{
	GPIO_PinState InState;
	GPIO_TypeDef* GPIO;
	uint16_t GPIO_Pin;
	uint8_t InDebounceUp;
	uint8_t InDebounceDown;
	uint8_t InDebounceUpCounter;
	uint8_t InDebounceDownCounter;
	GPIO_PinState InStateAtt;
	GPIO_PinState InStateOld;
/*todo criar outra variável campo de bits para armazenar todas as teclas durante o periodic e tambem um hit*/
} InputStruct;

/* Variables -----------------------------------------------------------------*/
InputStruct InputConf[kInputCount];

u32t KeysBitField;

/* Prototypes --------------------------------------------------------------*/
void InputsInit(void);
uint8_t InputsGetState(InputNameType InName);
uint32_t KeysGetState(void);
void InputsPeriodic(void);

#endif /* SRC_INPUTS_H_ */

/*
 * Inputs.c
 *
 *  Created on: Aug 2, 2019
 *      Author: gerry
 */

/**
 ******************************************************************************
 * File Name          : Inputs.c
 * Description        : This file provides code for the use
 *                      of the inputs instances.
 *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "Inputs.h"
#include "main.h"

/******************************************************************************/
/**
 * @brief contigure a input struct param for one each
 *
 * @param  InName				A enum index in vector
 * @param  InDebounceDown		A time for Bounce out
 * @param  InDebounceUp			A time for bounce in
 * @param  GPIO_Pin				A number of a port pin
 * @param  GPIO_TypeDef*		A pointer to a structure off a port
 */
void InputsConfigure(InputNameType InName, uint8_t InDebounceDown, uint8_t InDebounceUp, uint16_t GPIO_Pin,
		GPIO_TypeDef* GPIO)
{
	/* Check the parameters */
	if (InName < kInputCount)
	{
		InputConf[InName].GPIO = GPIO;
		InputConf[InName].GPIO_Pin = GPIO_Pin;
		InputConf[InName].InDebounceDown = InDebounceDown;
		InputConf[InName].InDebounceUp = InDebounceUp;
		InputConf[InName].InDebounceDownCounter = 0x00;
		InputConf[InName].InDebounceUpCounter = 0x00;
		InputConf[InName].InStateAtt = GPIO_PIN_RESET;
		InputConf[InName].InStateOld = GPIO_PIN_RESET;
		KeysBitField.u32v = 0;
	}
}

/******************************************************************************/
/**
 * @brief Use a InputsConfigure for listing inputs avaliable
 * @param  None
 */
void InputsInit(void)
{
	InputsConfigure(In01, 10, 10, McuIn1_Pin, McuIn1_GPIO_Port);
	InputsConfigure(In02, 10, 10, McuIn2_Pin, McuIn2_GPIO_Port);
	InputsConfigure(In03, 10, 10, McuIn3_Pin, McuIn3_GPIO_Port);
	InputsConfigure(In04, 10, 10, McuIn4_Pin, McuIn4_GPIO_Port);
	InputsConfigure(In05, 10, 10, McuIn5_Pin, McuIn5_GPIO_Port);
	InputsConfigure(In06, 10, 10, McuIn6_Pin, McuIn6_GPIO_Port);
	InputsConfigure(In07, 10, 10, McuIn7_Pin, McuIn7_GPIO_Port);
	InputsConfigure(In08, 10, 10, McuIn8_Pin, McuIn8_GPIO_Port);
	InputsConfigure(In09, 10, 10, McuIn9_Pin, McuIn9_GPIO_Port);
	InputsConfigure(In10, 10, 10, McuIn10_Pin, McuIn10_GPIO_Port);
	InputsConfigure(In11, 10, 10, McuIn11_Pin, McuIn11_GPIO_Port);
	InputsConfigure(In12, 10, 10, McuIn12_Pin, McuIn12_GPIO_Port);
	InputsConfigure(In13, 10, 10, McuIn13_Pin, McuIn13_GPIO_Port);
	InputsConfigure(In14, 10, 10, McuIn14_Pin, McuIn14_GPIO_Port);
	InputsConfigure(In15, 10, 10, McuIn15_Pin, McuIn15_GPIO_Port);
	InputsConfigure(In16, 10, 10, McuIn16_Pin, McuIn16_GPIO_Port);
	InputsConfigure(In17, 10, 10, McuIn17_Pin, McuIn17_GPIO_Port);
	InputsConfigure(In18, 10, 10, McuIn18_Pin, McuIn18_GPIO_Port);
}

/******************************************************************************/
/**
 * @brief Get a state off a digital input
 * @param  InName				A enum index in vector
 */
uint8_t InputsGetState(InputNameType InName)
{
	uint8_t InStateRet = 0;

	if (InName < kInputCount)
	{
		InStateRet = InputConf[InName].InStateAtt;
	}
	return (InStateRet);
}

/******************************************************************************/
/**
 * @brief Get a state off all digital input
 * @param  void
 */
uint32_t KeysGetState(void)
{
	uint32_t InStateRet = 0;
	InStateRet = KeysBitField.u32v;
	return (InStateRet);
}

/******************************************************************************/
/**
 * @brief Execute a filter and bounce off all inputs
 * @param  None

 */
void InputsPeriodic(void)
{
	uint8_t i;

	for (i = 0; i < kInputCount; i++)
	{
		InputConf[i].InState = HAL_GPIO_ReadPin(InputConf[i].GPIO, InputConf[i].GPIO_Pin);

		if (InputConf[i].InState == GPIO_PIN_RESET)
		{
			if (InputConf[i].InDebounceUpCounter < InputConf[i].InDebounceUp)
			{
				InputConf[i].InDebounceUpCounter++;
			}
			else
			{
				InputConf[i].InStateAtt = GPIO_PIN_SET;
				InputConf[i].InDebounceDownCounter = 0;
				InputConf[i].InStateOld = InputConf[i].InState;
				KeysBitField.u32v |= (1 << i);
				KeysBitField.u32v &= 0x0003FFFF;
			}
		}

		if (InputConf[i].InState == GPIO_PIN_SET)
		{
			if (InputConf[i].InDebounceDownCounter < InputConf[i].InDebounceDown)
			{
				InputConf[i].InDebounceDownCounter++;
			}
			else
			{
				InputConf[i].InStateAtt = GPIO_PIN_RESET;
				InputConf[i].InDebounceUpCounter = 0;
				InputConf[i].InStateOld = InputConf[i].InState;
				KeysBitField.u32v &=~ (1 << i);
				KeysBitField.u32v &= 0x0003FFFF;
			}
		}
	}
}


/**
 ******************************************************************************
 * File Name          : Inputs.c
 * Description        : This file provides code for the use
 *                      of the inputs instances.
 *****************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Inputs.h"
#include "cmsis_os.h"
#include "main.h"

//static uint8_t AdcCount = 0;
extern ADC_HandleTypeDef hadc;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

void InputsConfigure(InputNameType InName, uint8_t InDebounceDown, uint8_t InDebounceUp, uint16_t InThreshold, InputFunctionType InFunction);

/******************************************************************************/
/**
 * @brief contigure a input struct param for one each
 *
 * @param  InName				A enum index in vector
 * @param  InDebounceDown		A time for Bounce out
 * @param  InDebounceUp			A time for bounce in
 * @param  InThreshold			A Level off difference on off
 * @param  InputFunctionType	Is digital or analog
 */
void InputsConfigure(InputNameType InName, uint8_t InDebounceDown, uint8_t InDebounceUp, uint16_t InThreshold, InputFunctionType InFunction)
{
	if(InName < kInputCount)
	{
		InputConf[InName].InDebounceDown = InDebounceDown;
		InputConf[InName].InDebounceUp = InDebounceUp;
		InputConf[InName].InDebounceDownCounter = 0x00;
		InputConf[InName].InDebounceUpCounter = 0x00;
		InputConf[InName].InFunctionType = InFunction;
		InputConf[InName].InThreshold = InThreshold;
		InputConf[InName].InAdcValue = 0x0000;
		InputConf[InName].InStateAtt = InOFF;
		InputConf[InName].InStateOld = InOFF;
	}
}

/******************************************************************************/
/**
 * @brief Use a InputsConfigure for listing inputs avaliable
 *
 * @param  None
 */
void InputsInit(void)
{
	InputsConfigure(In01, 20, 20, 2000, ANALOG);
	InputsConfigure(In02, 20, 20, 2000, ANALOG);
	InputsConfigure(In03, 20, 20, 2000, ANALOG);
	InputsConfigure(In04, 20, 20, 2000, ANALOG);
	InputsConfigure(In05, 20, 20, 2000, ANALOG);
	InputsConfigure(In06, 20, 20, 2000, ANALOG);
	InputsConfigure(In07, 20, 20, 2000, ANALOG);
	InputsConfigure(In08, 20, 20, 2000, ANALOG);
	InputsConfigure(In09, 20, 20, 2000, ANALOG);
}

/******************************************************************************/
/**
 * @brief Get a state off a digital input
 *
 * @param  InName				A enum index in vector
 */
uint8_t InputsGetState(InputNameType InName)
{
	uint8_t InStateRet = 0;

	if((InName < kInputCount) && (InputConf[InName].InFunctionType == DIGITAL))
	{
		InStateRet = InputConf[InName].InStateAtt;
	}
	return(InStateRet);
}

/******************************************************************************/
/**
 * @brief Get a value off a analog in
 *
 * @param  InName				A enum index in vector
 */
uint16_t InputsGetValue(InputNameType InName)
{
	uint16_t InStateRet = 0;

	if((InName < kInputCount) && (InputConf[InName].InFunctionType == ANALOG))
	{
		InStateRet = InputConf[InName].InAdcValue;
	}
	return(InStateRet);
}

/******************************************************************************/
/**
 * @brief Execute a filter and bounce off all inputs
 *
 * @param  None

 */
void InputsPeriodic(void)
{
	uint8_t i;
	// use semaphore ???
	for(i = 0; i < kInputCount; i++)
	{
		if(InputConf[i].InFunctionType == DIGITAL)
		{
			if((AdcDmaAverageBuffer[i] + kInHisteresis) > InputConf[i].InThreshold)
			{
				if((InputConf[i].InStateAtt == InOFF) && (InputConf[i].InStateOld == InON))
				{
					if(InputConf[i].InDebounceUpCounter < InputConf[i].InDebounceUp)
					{
						InputConf[i].InDebounceUpCounter++;
					}
					else
					{
						InputConf[i].InStateAtt = InON;
						InputConf[i].InDebounceDownCounter = 0;
					}
				}
			}
			else if((AdcDmaAverageBuffer[i] - kInHisteresis) < InputConf[i].InThreshold)
			{
				if((InputConf[i].InStateAtt == InON) && (InputConf[i].InStateOld == InOFF))
				{
					if(InputConf[i].InDebounceDownCounter < InputConf[i].InDebounceDown)
					{
						InputConf[i].InDebounceDownCounter++;
					}
					else
					{
						InputConf[i].InStateAtt = InOFF;
						InputConf[i].InDebounceUpCounter = 0;
					}
				}
			}
			else
			{

			}
		}
		else // ANALOG
		{
			InputConf[i].InAdcValue = AdcDmaAverageBuffer[i];
		}
	}
}

/******************************************************************************/
/**
 * @brief Start a ADC conversion in DMA mode
 *
 * @param  none
 */
void InputsAdcPeriodic(void)
{
	HAL_ADC_Start_DMA(&hadc, AdcDmaBuffer, kInputCount);
}

/******************************************************************************/
/**
 * @brief Use a calbak function off ADC for calculate a average value
 *
 * @param  InName				A enum index in vector
 * @param  InDebounceDown		A time for Bounce out
 * @param  InDebounceUp			A time for bounce in
 * @param  InThreshold			A Level off difference on off
 * @param  InputFunctionType	Is digital or analog
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	static uint8_t AdcCount;
	uint8_t i;
	//HAL_GPIO_TogglePin(PinMcuLedVd_GPIO_Port, PinMcuLedVd_Pin);

	if(AdcCount < 10)
	{
		AdcCount++;

		for(i = 0; i < kInputCount; i++)
		{
			AdcDmaAcc[i] += AdcDmaBuffer[i];
		}
	}
	else
	{

		for(i = 0; i < kInputCount; i++)
		{
			AdcDmaAverageBuffer[i] = (uint32_t)(AdcDmaAcc[i] / AdcCount);
			AdcDmaAcc[i] = 0;
		}
		AdcCount = 0;
		InputsPeriodic();
	}
}



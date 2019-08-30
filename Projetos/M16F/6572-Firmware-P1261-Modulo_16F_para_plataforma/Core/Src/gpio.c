/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */
#include "Outputs.h"
#include "NRF905.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
GPIO_TypeDef *GPIO_Get_Port(uint32_t out_pin);


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == NORDIC_DR_Pin)
	{
		osSignalSet(NRF905ThreadId,NORDIC_DR_SIGNAL);
	}
}

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_VD_Pin|MCU_OUT_08_Pin|MCU_OUT_09_Pin|MCU_OUT_10_Pin 
                          |MCU_OUT_11_Pin|MCU_OUT_06_Pin|MCU_OUT_07_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED_VM_Pin|MCU_OUT_12_Pin|MCU_OUT_13_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, NORDIC_TX_EN_Pin|NORDIC_PWR_UP_Pin|NORDIC_CS_Pin|NORDIC_TRX_CE_Pin|TXEN_485_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MCU_OUT_14_Pin|MCU_OUT_15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MCU_OUT_01_Pin|MCU_OUT_02_Pin|MCU_OUT_03_Pin|MCU_OUT_04_Pin 
                          |MCU_OUT_05_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = LED_VD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = TXEN_485_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LED_VM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

void GPIO_Change_Pin_State(GPIO_TypeDef  *GPIOx,uint32_t GPIO_Pin, GPIO_PinState PinState)
{
	  /* Check the parameters */
	  assert_param(IS_GPIO_PIN(GPIO_Pin));
	  assert_param(IS_GPIO_PIN_ACTION(PinState));

	  if (PinState != GPIO_PIN_RESET)
	  {
		  GPIOx->BSRR = (uint32_t)GPIO_Pin;
	  }
	  else
	  {
		  GPIOx->BRR = (uint32_t)GPIO_Pin;
	  }
}

GPIO_PinState GPIO_Get_Pin_State(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
	GPIO_PinState bitstatus;

	/* Check the parameters */
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;

}

void GPIO_Toggle_Pin(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
	  /* Check the parameters */
	  assert_param(IS_GPIO_PIN(GPIO_Pin));

	  GPIOx->ODR ^= GPIO_Pin;
}

void GPIO_Configure_as_Output(GPIO_TypeDef  *GPIOx,uint32_t pin)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};


	  GPIO_InitStruct.Pin = pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void GPIO_Configure_as_Input(GPIO_TypeDef  *GPIOx,uint32_t pin)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void GPIO_DisableIRQ(uint32_t gpio_pin)
{
	if(gpio_pin == NORDIC_DR_Pin)
	{
		 HAL_NVIC_DisableIRQ(EXTI4_15_IRQn);
	}
}

void GPIO_EnableIRQ(uint32_t gpio_pin)
{
	if(gpio_pin == NORDIC_DR_Pin)
	{
		HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
	}
}

void GPIO_Configure_as_Analog(GPIO_TypeDef  *GPIOx,uint32_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void GPIO_Configure_NRF905_IO(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  GPIO_InitStruct.Pin = NORDIC_AM_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(NORDIC_AM_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = NORDIC_UPCLK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(NORDIC_UPCLK_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = NORDIC_DR_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(NORDIC_DR_GPIO_Port, &GPIO_InitStruct);

	  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

	  GPIO_InitStruct.Pin = NORDIC_CD_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(NORDIC_CD_GPIO_Port, &GPIO_InitStruct);


	  GPIO_InitStruct.Pin = NORDIC_TRX_CE_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(NORDIC_TRX_CE_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = NORDIC_TX_EN_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(NORDIC_TX_EN_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = NORDIC_PWR_UP_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(NORDIC_PWR_UP_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = NORDIC_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	  HAL_GPIO_Init(NORDIC_CS_GPIO_Port, &GPIO_InitStruct);
}


PCB_Outputs_TypeDefs GPIO_Return_PCB_Out(GPIO_TypeDef  *GPIOx,uint32_t pin)
{
	if(GPIOx == GPIOA)
	{
		if(pin == GPIO_PIN_8)
		{
			return OUT_1;
		}
		else if(pin == GPIO_PIN_9)
		{
			return OUT_2;
		}
		else if(pin == GPIO_PIN_10)
		{
			return OUT_3;
		}
		else if(pin == GPIO_PIN_11)
		{
			return OUT_4;
		}
		else if(pin == GPIO_PIN_15)
		{
			return OUT_5;
		}
	}
	else if(GPIOx == GPIOB)
	{
		if(pin == GPIO_PIN_3)
		{
			return OUT_6;
		}
		else if(pin == GPIO_PIN_4)
		{
			return OUT_7;
		}
		else if(pin == GPIO_PIN_10)
		{
			return OUT_8;
		}
		else if(pin == GPIO_PIN_11)
		{
			return OUT_9;
		}
		else if(pin == GPIO_PIN_14)
		{
			return OUT_10;
		}
		else if(pin == GPIO_PIN_15)
		{
			return OUT_11;
		}
	}
	else if(GPIOx == GPIOE)
	{
		if(pin == GPIO_PIN_0)
		{
			return OUT_12;
		}
		else if(pin == GPIO_PIN_1)
		{
			return OUT_13;
		}
	}
	else if(GPIOx == GPIOC)
	{
		if(pin == GPIO_PIN_7)
		{
			return OUT_14;
		}
		else if(pin == GPIO_PIN_8)
		{
			return OUT_15;
		}
		else if(pin == GPIO_PIN_9)
		{
			return OUT_16;
		}
	}
	return 0;
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
 ******************************************************************************
 * File Name          : ADC.c
 * Description        : This file provides code for the configuration
 *                      of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */
#include "VN5025.h"
uint32_t dma_buffer [16] = {0};
uint32_t debug_cnt = 0 ;
uint16_t length_of_convertion = 0;
uint8_t adc_completed = 0;
uint16_t InputRawAdc[16];

uint16_t GetRawAdcValue(int8_t Input)
{
  if(Input < 16)
    {
      return(InputRawAdc[Input]);
    }
  return(0xFFFF);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  uint8_t i;
  for(i = 0 ; i < length_of_convertion; i++)
    {

      adc_completed = 1;
      InputRawAdc[i] = (uint16_t)dma_buffer[i];
      InputRawAdc[i] = InputRawAdc[i];
    }

#if VN5025_PROTECTION_ACTIVE
  VN5025_Adc->VN_CSD1_SUM_VAL += dma_buffer[14];
  VN5025_Adc->VN_CSD2_SUM_VAL += dma_buffer[15];
  VN5025_Adc->VN_CSD1_SAMPLES_COUNT++;
  VN5025_Adc->VN_CSD2_SAMPLES_COUNT++;
#endif
}

uint8_t ADC_is_Convertion_Completed (void)
{
  uint8_t state = adc_completed;
  adc_completed = 0;
  return(state);
}
/* USER CODE END 0 */

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;
/* ADC init function */

void MX_ADC_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  /*
  ** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;

  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_2;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_3;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_4;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_6;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_7;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_8;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_9;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_10;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_11;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_12;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_13;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_14;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
  sConfig.Channel = ADC_CHANNEL_15;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure for the selected ADC regular channel to be converted. 
  */
//  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
//  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /**Configure for the selected ADC regular channel to be converted.
//  */
//  sConfig.Channel = ADC_CHANNEL_VREFINT;
//  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /**Configure for the selected ADC regular channel to be converted.
//  */
//  sConfig.Channel = ADC_CHANNEL_VBAT;
//  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC GPIO Configuration    
    PC0     ------> ADC_IN10
    PC1     ------> ADC_IN11
    PC2     ------> ADC_IN12
    PC3     ------> ADC_IN13
    PA0     ------> ADC_IN0
    PA1     ------> ADC_IN1
    PA2     ------> ADC_IN2
    PA3     ------> ADC_IN3
    PA4     ------> ADC_IN4
    PA5     ------> ADC_IN5
    PA6     ------> ADC_IN6
    PA7     ------> ADC_IN7
    PC4     ------> ADC_IN14
    PC5     ------> ADC_IN15
    PB0     ------> ADC_IN8
    PB1     ------> ADC_IN9 
    */
    GPIO_InitStruct.Pin = MCU_ADC_AN_11_Pin|MCU_ADC_AN_12_Pin|MCU_ADC_AN_13_Pin|MCU_ADC_AN_14_Pin 
                          |MCU_ADC_15_VN_Pin|MCU_ADC_16_VN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = MCU_ADC_AN_01_Pin|MCU_ADC_AN_02_Pin|MCU_ADC_AN_03_Pin|MCU_ADC_AN_04_Pin 
                          |MCU_ADC_AN_05_Pin|MCU_ADC_AN_06_Pin|MCU_ADC_AN_07_Pin|MCU_ADC_AN_08_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = MCU_ADC_AN_09_Pin|MCU_ADC_AN_10_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC Init */
    hdma_adc.Instance = DMA1_Channel1;
    hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc.Init.Mode = DMA_CIRCULAR;
    hdma_adc.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hdma_adc) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_DMA1_REMAP(HAL_DMA1_CH1_ADC);

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /**ADC GPIO Configuration    
    PC0     ------> ADC_IN10
    PC1     ------> ADC_IN11
    PC2     ------> ADC_IN12
    PC3     ------> ADC_IN13
    PA0     ------> ADC_IN0
    PA1     ------> ADC_IN1
    PA2     ------> ADC_IN2
    PA3     ------> ADC_IN3
    PA4     ------> ADC_IN4
    PA5     ------> ADC_IN5
    PA6     ------> ADC_IN6
    PA7     ------> ADC_IN7
    PC4     ------> ADC_IN14
    PC5     ------> ADC_IN15
    PB0     ------> ADC_IN8
    PB1     ------> ADC_IN9 
    */
    HAL_GPIO_DeInit(GPIOC, MCU_ADC_AN_11_Pin|MCU_ADC_AN_12_Pin|MCU_ADC_AN_13_Pin|MCU_ADC_AN_14_Pin 
                          |MCU_ADC_15_VN_Pin|MCU_ADC_16_VN_Pin);

    HAL_GPIO_DeInit(GPIOA, MCU_ADC_AN_01_Pin|MCU_ADC_AN_02_Pin|MCU_ADC_AN_03_Pin|MCU_ADC_AN_04_Pin 
                          |MCU_ADC_AN_05_Pin|MCU_ADC_AN_06_Pin|MCU_ADC_AN_07_Pin|MCU_ADC_AN_08_Pin);

    HAL_GPIO_DeInit(GPIOB, MCU_ADC_AN_09_Pin|MCU_ADC_AN_10_Pin);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void ADC_Configure_Channel(uint32_t channel , uint8_t rank)
{
  ADC_ChannelConfTypeDef sConfig = { 0 };
  sConfig.Channel = channel;
  sConfig.Rank = rank;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
}

uint32_t ADC_Get_Channel (GPIO_TypeDef  *GPIOx, uint32_t adc_pin)
{

  if(GPIOx ==  GPIOC)
    {
      if(adc_pin == GPIO_PIN_0 )
	{
	  return ADC_CHANNEL_10;
	}
      else if(adc_pin == GPIO_PIN_1)
	{
	  return ADC_CHANNEL_11;
	}
      else if(adc_pin == GPIO_PIN_2)
	{
	  return ADC_CHANNEL_12;
	}
      else if(adc_pin == GPIO_PIN_3)
	{
	  return ADC_CHANNEL_13;
	}
      else if(adc_pin == GPIO_PIN_4)
	{
	  return ADC_CHANNEL_14;
	}
      else if(adc_pin == GPIO_PIN_5)
	{
	  return ADC_CHANNEL_15;
	}
    }
  else if(GPIOx == GPIOA)
    {
      if(adc_pin == GPIO_PIN_0 )
	{
	  return ADC_CHANNEL_0;
	}
      else if(adc_pin == GPIO_PIN_1)
	{
	  return ADC_CHANNEL_1;
	}
      else if(adc_pin == GPIO_PIN_2)
	{
	  return ADC_CHANNEL_2;
	}
      else if(adc_pin == GPIO_PIN_3)
	{
	  return ADC_CHANNEL_3;
	}
      else if(adc_pin == GPIO_PIN_4)
	{
	  return ADC_CHANNEL_4;
	}
      else if(adc_pin == GPIO_PIN_5)
	{
	  return ADC_CHANNEL_5;
	}
      else if(adc_pin == GPIO_PIN_6)
	{
	  return ADC_CHANNEL_6;
	}
      else if(adc_pin == GPIO_PIN_7)
	{
	  return ADC_CHANNEL_7;
	}
    }
  else if(GPIOx == GPIOB)
    {
      if(adc_pin == GPIO_PIN_0 )
	{
	  return ADC_CHANNEL_8;
	}
      else if(adc_pin == GPIO_PIN_1)
	{
	  return ADC_CHANNEL_9;
	}

    }
  return 0xFFFF; // error condition
}

void ADC_Start_Convertion(uint16_t inputs_lenght)
{
  length_of_convertion = inputs_lenght;
  HAL_ADC_Start_DMA(&hadc, dma_buffer, inputs_lenght);
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "usart.h"
#include "string.h"
#include <main.h>
#include <gpio.h>


/* USER CODE BEGIN 0 */



#define SIZE_OF_RECEPTION 1
static uint8_t usart8_rx_buffer[SIZE_OF_RECEPTION] = {0};

USART_RX_Callback (*Usart8_Callback_Rx);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &CYBLE_USART)
	{
		Usart8_Callback_Rx(usart8_rx_buffer[0]);
		USART8_Start_Reception();
	}

}
/* USER CODE END 0 */

UART_HandleTypeDef huart8;

/* USART8 init function */

void MX_USART8_UART_Init(void)
{

  huart8.Instance = USART8;
  huart8.Init.BaudRate = 57600;
  huart8.Init.WordLength = UART_WORDLENGTH_8B;
  huart8.Init.StopBits = UART_STOPBITS_1;
  huart8.Init.Parity = UART_PARITY_NONE;
  huart8.Init.Mode = UART_MODE_TX_RX;
  huart8.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart8.Init.OverSampling = UART_OVERSAMPLING_16;
  huart8.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart8.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart8) != HAL_OK)
  {
    Error_Handler();
  }

}

UART_HandleTypeDef huart5;

/* USART5 init function */

void MX_USART5_UART_Init(void)
{

  huart5.Instance = USART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART5)
  {
    /* USER CODE BEGIN USART5_MspInit 0 */

    /* USER CODE END USART5_MspInit 0 */
      /* USART5 clock enable */
      __HAL_RCC_USART5_CLK_ENABLE();

      __HAL_RCC_GPIOE_CLK_ENABLE();
      /**USART5 GPIO Configuration
      PE10     ------> USART5_TX
      PE11     ------> USART5_RX
      */
      GPIO_InitStruct.Pin = BOOT_TX_Pin|BOOT_RX_Pin;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF1_USART5;
      HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

      /* USART5 interrupt Init */
      HAL_NVIC_SetPriority(USART3_8_IRQn, 3, 0);
      HAL_NVIC_EnableIRQ(USART3_8_IRQn);
    /* USER CODE BEGIN USART5_MspInit 1 */

    /* USER CODE END USART5_MspInit 1 */
  }
  else if(uartHandle->Instance==USART8)
  {
  /* USER CODE BEGIN USART8_MspInit 0 */

  /* USER CODE END USART8_MspInit 0 */
    /* USART8 clock enable */
    __HAL_RCC_USART8_CLK_ENABLE();
  
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART8 GPIO Configuration    
    PD13     ------> USART8_TX
    PD14     ------> USART8_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_USART8;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART8 interrupt Init */
    HAL_NVIC_SetPriority(USART3_8_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_8_IRQn);
  /* USER CODE BEGIN USART8_MspInit 1 */

  /* USER CODE END USART8_MspInit 1 */
  }

}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
if(uartHandle->Instance==USART5)
  {
  /* USER CODE BEGIN USART5_MspDeInit 0 */

  /* USER CODE END USART5_MspDeInit 0 */
	/* Peripheral clock disable */
	__HAL_RCC_USART5_CLK_DISABLE();

	/**USART5 GPIO Configuration
	PE10     ------> USART5_TX
	PE11     ------> USART5_RX
	*/
	HAL_GPIO_DeInit(GPIOE, BOOT_TX_Pin|BOOT_RX_Pin);

	/* USART5 interrupt Deinit */
  /* USER CODE BEGIN USART5:USART3_8_IRQn disable */
	/**
	* Uncomment the line below to disable the "USART3_8_IRQn" interrupt
	* Be aware, disabling shared interrupt may affect other IPs
	*/
	/* HAL_NVIC_DisableIRQ(USART3_8_IRQn); */
  /* USER CODE END USART5:USART3_8_IRQn disable */

  /* USER CODE BEGIN USART5_MspDeInit 1 */

  /* USER CODE END USART5_MspDeInit 1 */
  }
else if(uartHandle->Instance==USART8)
  {
  /* USER CODE BEGIN USART8_MspDeInit 0 */

  /* USER CODE END USART8_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART8_CLK_DISABLE();
  
    /**USART8 GPIO Configuration    
    PD13     ------> USART8_TX
    PD14     ------> USART8_RX 
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_13|GPIO_PIN_14);

    /* USART8 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_8_IRQn);
  /* USER CODE BEGIN USART8_MspDeInit 1 */

  /* USER CODE END USART8_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void USART8_Start_Reception(void)
{
	HAL_UART_Receive_IT(&huart8,usart8_rx_buffer,SIZE_OF_RECEPTION);
}

void USART8_Send_Packet(uint8_t *packet,uint16_t size)
{
	HAL_UART_Transmit_IT(&huart8,packet,size);
}

void USART8_Register_RX_Callback(USART_RX_Callback callback_function)
{
	Usart8_Callback_Rx = callback_function;
}
//HAL_UART_Transmit_IT(&huart1, (uint8_t *)aTxStartMessage, sizeof(aTxStartMessage));
//HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)

// DiagnosticTroubleCodes
void PrintDTC(char aTxStartMessage[])
{
	//HAL_UART_Transmit(&huart5, (uint8_t *)aTxStartMessage, sizeof(aTxStartMessage), 10);
	HAL_UART_Transmit(&huart5, (uint8_t *)aTxStartMessage, strlen(aTxStartMessage), 10);
	//HAL_UART_Transmit_IT(&huart5, (uint8_t *)aTxStartMessage, strlen(aTxStartMessage));
	//if(HAL_UART_Transmit_IT(&huart5, (uint8_t *)aTxStartMessage, strlen(aTxStartMessage))!= HAL_OK)
	//{

	//}
}

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

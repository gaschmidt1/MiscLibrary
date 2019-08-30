/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
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
#include "spi.h"
#include "NRF905.h"

osMutexDef (SPI1_Mutex);
osMutexId spi1_mutex_id;
/* USER CODE BEGIN 0 */
SPI_Communication_Typedef * SPI1_Active_Peripheral;
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(SPI1_Active_Peripheral !=0)
	{
		if(SPI1_Active_Peripheral->peripheral_name == NRF905)
		{
			SPI1_Active_Peripheral->chip_deselect_func();
			osSignalSet(NRF905ThreadId,SPI_TX_COMPLETED);
		}
	}

}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(SPI1_Active_Peripheral !=0)
	{
		if(SPI1_Active_Peripheral->peripheral_name == NRF905)
		{
			SPI1_Active_Peripheral->chip_deselect_func();
			osSignalSet(NRF905ThreadId,SPI_RX_COMPLETED);
		}
	}

}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(SPI1_Active_Peripheral !=0)
	{
		if(SPI1_Active_Peripheral->peripheral_name == NRF905)
		{
			SPI1_Active_Peripheral->chip_deselect_func();
			osSignalSet(NRF905ThreadId,SPI_RX_COMPLETED);
		}
	}
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	if(SPI1_Active_Peripheral !=0)
	{
		if(SPI1_Active_Peripheral->peripheral_name == NRF905)
		{
			SPI1_Active_Peripheral->chip_deselect_func();
			osSignalSet(NRF905ThreadId,SPI_ERROR);
		}
	}
}
/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  SPI1_Active_Peripheral = 0;
  spi1_mutex_id = osMutexCreate  (osMutex (SPI1_Mutex));
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
  
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PE13     ------> SPI1_SCK
    PE14     ------> SPI1_MISO
    PE15     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_SPI1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* SPI1 DMA Init */
    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA1_Channel3;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_DMA1_REMAP(HAL_DMA1_CH3_SPI1_TX);

    __HAL_LINKDMA(spiHandle,hdmatx,hdma_spi1_tx);


    /* SPI1_RX Init */
    hdma_spi1_rx.Instance = DMA1_Channel2;
    hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_rx.Init.Mode = DMA_NORMAL;
    hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_DMA1_REMAP(HAL_DMA1_CH2_SPI1_RX);

    __HAL_LINKDMA(spiHandle,hdmarx,hdma_spi1_rx);

    /* SPI1 interrupt Init */
    HAL_NVIC_SetPriority(SPI1_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();
  
    /**SPI1 GPIO Configuration    
    PE13     ------> SPI1_SCK
    PE14     ------> SPI1_MISO
    PE15     ------> SPI1_MOSI 
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    /* SPI1 DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmatx);

    /* SPI1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SPI1_IRQn);
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */



void SPI_Get_Bus(SPI_Communication_Typedef *spi_communication_properties)
{
	if(spi_communication_properties != SPI1_Active_Peripheral)
	{
		if(spi_communication_properties->SPI_Handler == &hspi1)
		{
			osMutexWait(spi1_mutex_id, osWaitForever);
			SPI1_Active_Peripheral = spi_communication_properties;
		}
	}
}

void SPI_Release_Bus(SPI_Communication_Typedef *spi_communication_properties)
{
	if(spi_communication_properties == SPI1_Active_Peripheral)
	{
		if(spi_communication_properties->SPI_Handler == &hspi1)
		{
			osMutexRelease(spi1_mutex_id);
			SPI1_Active_Peripheral = 0;
		}
	}

}


void SPI_Write_Data(SPI_Communication_Typedef *spi_communication_properties)
{
	if(spi_communication_properties == SPI1_Active_Peripheral)
	{
		if(spi_communication_properties->SPI_Handler == &hspi1)
		{
			spi_communication_properties->chip_select_func();
			HAL_SPI_Transmit_DMA(spi_communication_properties->SPI_Handler,spi_communication_properties->ptr_transmit_buffer,spi_communication_properties->size_of_transmission);
		}
	}
}


void SPI_Read_Data(SPI_Communication_Typedef *spi_communication_properties)
{
	if(spi_communication_properties == SPI1_Active_Peripheral)
	{
		if(spi_communication_properties->SPI_Handler == &hspi1)
		{
			spi_communication_properties->chip_select_func();
			HAL_SPI_Receive_IT(spi_communication_properties->SPI_Handler,spi_communication_properties->ptr_receive_buffer,spi_communication_properties->size_of_receive);
		}
	}

}

void SPI_Transmit_Receive_Data(SPI_Communication_Typedef *spi_communication_properties)
{
	if(spi_communication_properties == SPI1_Active_Peripheral)
	{
		if(spi_communication_properties->SPI_Handler == &hspi1)
		{
			spi_communication_properties->chip_select_func();
			HAL_SPI_TransmitReceive_DMA(spi_communication_properties->SPI_Handler,spi_communication_properties->ptr_transmit_buffer,spi_communication_properties->ptr_receive_buffer,spi_communication_properties->size_of_receive);
		}
	}
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

  /* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

  /* Private includes ----------------------------------------------------------*/
  /* USER CODE BEGIN Includes */

  /* USER CODE END Includes */

  /* Exported types ------------------------------------------------------------*/
  /* USER CODE BEGIN ET */

  /* USER CODE END ET */

  /* Exported constants --------------------------------------------------------*/
  /* USER CODE BEGIN EC */

  /* USER CODE END EC */

  /* Exported macro ------------------------------------------------------------*/
  /* USER CODE BEGIN EM */

  /* USER CODE END EM */

  /* Exported functions prototypes ---------------------------------------------*/
  void Error_Handler(void);

  /* USER CODE BEGIN EFP */

  /* USER CODE END EFP */

  /* Private defines -----------------------------------------------------------*/
#define MCU_ADC_AN_11_Pin GPIO_PIN_0
#define MCU_ADC_AN_11_GPIO_Port GPIOC
#define MCU_ADC_AN_12_Pin GPIO_PIN_1
#define MCU_ADC_AN_12_GPIO_Port GPIOC
#define MCU_ADC_AN_13_Pin GPIO_PIN_2
#define MCU_ADC_AN_13_GPIO_Port GPIOC
#define MCU_ADC_AN_14_Pin GPIO_PIN_3
#define MCU_ADC_AN_14_GPIO_Port GPIOC
#define MCU_ADC_AN_01_Pin GPIO_PIN_0
#define MCU_ADC_AN_01_GPIO_Port GPIOA
#define MCU_ADC_AN_02_Pin GPIO_PIN_1
#define MCU_ADC_AN_02_GPIO_Port GPIOA
#define MCU_ADC_AN_03_Pin GPIO_PIN_2
#define MCU_ADC_AN_03_GPIO_Port GPIOA
#define MCU_ADC_AN_04_Pin GPIO_PIN_3
#define MCU_ADC_AN_04_GPIO_Port GPIOA
#define MCU_ADC_AN_05_Pin GPIO_PIN_4
#define MCU_ADC_AN_05_GPIO_Port GPIOA
#define MCU_ADC_AN_06_Pin GPIO_PIN_5
#define MCU_ADC_AN_06_GPIO_Port GPIOA
#define MCU_ADC_AN_07_Pin GPIO_PIN_6
#define MCU_ADC_AN_07_GPIO_Port GPIOA
#define MCU_ADC_AN_08_Pin GPIO_PIN_7
#define MCU_ADC_AN_08_GPIO_Port GPIOA
#define MCU_ADC_AN_09_Pin GPIO_PIN_0
#define MCU_ADC_AN_09_GPIO_Port GPIOB
#define MCU_ADC_AN_10_Pin GPIO_PIN_1
#define MCU_ADC_AN_10_GPIO_Port GPIOB

#define MCU_IN_01_Pin MCU_ADC_AN_01_Pin
#define MCU_IN_02_Pin MCU_ADC_AN_02_Pin
#define MCU_IN_03_Pin MCU_ADC_AN_03_Pin
#define MCU_IN_04_Pin MCU_ADC_AN_04_Pin
#define MCU_IN_05_Pin MCU_ADC_AN_05_Pin
#define MCU_IN_06_Pin MCU_ADC_AN_06_Pin
#define MCU_IN_07_Pin MCU_ADC_AN_07_Pin
#define MCU_IN_08_Pin MCU_ADC_AN_08_Pin
#define MCU_IN_09_Pin MCU_ADC_AN_09_Pin
#define MCU_IN_10_Pin MCU_ADC_AN_10_Pin
#define MCU_IN_11_Pin MCU_ADC_AN_11_Pin
#define MCU_IN_12_Pin MCU_ADC_AN_12_Pin
#define MCU_IN_13_Pin MCU_ADC_AN_13_Pin
#define MCU_IN_14_Pin MCU_ADC_AN_14_Pin
//#define MCU_IN_15_Pin GPIO_PIN_4
//#define MCU_IN_16_Pin GPIO_PIN_5

#define MCU_ADC_15_VN_Pin GPIO_PIN_4
#define MCU_ADC_16_VN_Pin GPIO_PIN_5


#define MCU_IN_01_Port MCU_ADC_AN_01_GPIO_Port
#define MCU_IN_02_Port MCU_ADC_AN_02_GPIO_Port
#define MCU_IN_03_Port MCU_ADC_AN_03_GPIO_Port
#define MCU_IN_04_Port MCU_ADC_AN_04_GPIO_Port
#define MCU_IN_05_Port MCU_ADC_AN_05_GPIO_Port
#define MCU_IN_06_Port MCU_ADC_AN_06_GPIO_Port
#define MCU_IN_07_Port MCU_ADC_AN_07_GPIO_Port
#define MCU_IN_08_Port MCU_ADC_AN_08_GPIO_Port
#define MCU_IN_09_Port MCU_ADC_AN_09_GPIO_Port
#define MCU_IN_10_Port MCU_ADC_AN_10_GPIO_Port
#define MCU_IN_11_Port MCU_ADC_AN_11_GPIO_Port
#define MCU_IN_12_Port MCU_ADC_AN_12_GPIO_Port
#define MCU_IN_13_Port MCU_ADC_AN_13_GPIO_Port
#define MCU_IN_14_Port MCU_ADC_AN_14_GPIO_Port
//#define MCU_IN_15_Port GPIOC
//#define MCU_IN_16_Port GPIOC

#define MCU_ADC_15_VN_GPIO_Port GPIOC
#define MCU_ADC_16_VN_GPIO_Port GPIOC


#define LED_VD_Pin GPIO_PIN_2
#define LED_VD_GPIO_Port GPIOB
#define LED_VM_Pin GPIO_PIN_12
#define LED_VM_GPIO_Port GPIOE

#define MCU_OUT_08_Pin GPIO_PIN_10
#define MCU_OUT_08_GPIO_Port GPIOB
#define MCU_OUT_09_Pin GPIO_PIN_11
#define MCU_OUT_09_GPIO_Port GPIOB
#define MCU_OUT_10_Pin GPIO_PIN_14
#define MCU_OUT_10_GPIO_Port GPIOB
#define MCU_OUT_11_Pin GPIO_PIN_15
#define MCU_OUT_11_GPIO_Port GPIOB

#define NORDIC_TX_EN_Pin GPIO_PIN_8
#define NORDIC_TX_EN_GPIO_Port GPIOD
#define NORDIC_PWR_UP_Pin GPIO_PIN_9
#define NORDIC_PWR_UP_GPIO_Port GPIOD
#define NORDIC_CS_Pin GPIO_PIN_10
#define NORDIC_CS_GPIO_Port GPIOD

#define MCU_OUT_14_Pin GPIO_PIN_7
#define MCU_OUT_14_GPIO_Port GPIOC
#define MCU_OUT_15_Pin GPIO_PIN_8
#define MCU_OUT_15_GPIO_Port GPIOC
#define MCU_OUT_16_Pin GPIO_PIN_9
#define MCU_OUT_16_GPIO_Port GPIOC
#define MCU_OUT_01_Pin GPIO_PIN_8
#define MCU_OUT_01_GPIO_Port GPIOA
#define MCU_OUT_02_Pin GPIO_PIN_9
#define MCU_OUT_02_GPIO_Port GPIOA
#define MCU_OUT_03_Pin GPIO_PIN_10
#define MCU_OUT_03_GPIO_Port GPIOA
#define MCU_OUT_04_Pin GPIO_PIN_11
#define MCU_OUT_04_GPIO_Port GPIOA
#define MCU_OUT_05_Pin GPIO_PIN_15
#define MCU_OUT_05_GPIO_Port GPIOA

#define NORDIC_AM_Pin GPIO_PIN_2
#define NORDIC_AM_GPIO_Port GPIOD
#define NORDIC_TRX_CE_Pin GPIO_PIN_5
#define NORDIC_TRX_CE_GPIO_Port GPIOD
#define NORDIC_CD_Pin GPIO_PIN_6
#define NORDIC_CD_GPIO_Port GPIOD
#define NORDIC_DR_Pin GPIO_PIN_7
#define NORDIC_DR_GPIO_Port GPIOD

#define MCU_OUT_06_Pin GPIO_PIN_3
#define MCU_OUT_06_GPIO_Port GPIOB
#define MCU_OUT_07_Pin GPIO_PIN_4
#define MCU_OUT_07_GPIO_Port GPIOB

#define NORDIC_UPCLK_Pin GPIO_PIN_7
#define NORDIC_UPCLK_GPIO_Port GPIOB

#define MCU_OUT_12_Pin GPIO_PIN_0
#define MCU_OUT_12_GPIO_Port GPIOE
#define MCU_OUT_13_Pin GPIO_PIN_1
#define MCU_OUT_13_GPIO_Port GPIOE


#define MCU_CSD1_01_Pin GPIO_PIN_2
#define MCU_CSD1_02_Pin GPIO_PIN_3
#define MCU_CSD1_03_Pin GPIO_PIN_4
#define MCU_CSD1_04_Pin GPIO_PIN_5
#define MCU_CSD1_05_Pin GPIO_PIN_6
#define MCU_CSD1_06_Pin GPIO_PIN_7
#define MCU_CSD1_07_Pin GPIO_PIN_8
#define MCU_CSD1_08_Pin GPIO_PIN_9

#define MCU_CSD1_01_Port GPIOE
#define MCU_CSD1_02_Port GPIOE
#define MCU_CSD1_03_Port GPIOE
#define MCU_CSD1_04_Port GPIOE
#define MCU_CSD1_05_Port GPIOE
#define MCU_CSD1_06_Port GPIOE
#define MCU_CSD1_07_Port GPIOE
#define MCU_CSD1_08_Port GPIOE

#define MCU_CSD2_01_Pin MCU_CSD1_01_Pin
#define MCU_CSD2_02_Pin MCU_CSD1_02_Pin
#define MCU_CSD2_03_Pin MCU_CSD1_03_Pin
#define MCU_CSD2_04_Pin MCU_CSD1_04_Pin
#define MCU_CSD2_05_Pin MCU_CSD1_05_Pin
#define MCU_CSD2_06_Pin MCU_CSD1_06_Pin
#define MCU_CSD2_07_Pin MCU_CSD1_07_Pin
#define MCU_CSD2_08_Pin MCU_CSD1_08_Pin

#define MCU_CSD2_01_Port GPIOE
#define MCU_CSD2_02_Port GPIOE
#define MCU_CSD2_03_Port GPIOE
#define MCU_CSD2_04_Port GPIOE
#define MCU_CSD2_05_Port GPIOE
#define MCU_CSD2_06_Port GPIOE
#define MCU_CSD2_07_Port GPIOE
#define MCU_CSD2_08_Port GPIOE

#define BOOT_TX_Pin GPIO_PIN_10
#define BOOT_TX_GPIO_Port GPIOE
#define BOOT_RX_Pin GPIO_PIN_11
#define BOOT_RX_GPIO_Port GPIOE

#define TXEN_485_Pin GPIO_PIN_12
#define TXEN_485_GPIO_Port GPIOD

#define TX_485_Pin GPIO_PIN_10
#define TX_485_GPIO_Port GPIOC

#define RX_485_Pin GPIO_PIN_11
#define RX_485_GPIO_Port GPIOC

  /* USER CODE BEGIN Private defines */
  typedef enum
  {
    OUT_1 = 0x00,
    OUT_2 = 0x01,
    OUT_3 = 0x02,
    OUT_4 = 0x03,
    OUT_5 = 0x04,
    OUT_6 = 0x05,
    OUT_7 = 0x06,
    OUT_8 = 0x07,
    OUT_9 = 0x08,
    OUT_10 = 0x09,
    OUT_11 = 0x0A,
    OUT_12 = 0x0B,
    OUT_13 = 0x0C,
    OUT_14 = 0x0D,
    OUT_15 = 0x0E,
    OUT_16 = 0x0F,
  }PCB_Outputs_TypeDefs;



  /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

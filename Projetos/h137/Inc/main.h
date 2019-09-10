/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define McuCsVn01_Pin GPIO_PIN_2
#define McuCsVn01_GPIO_Port GPIOE
#define McuCsVn02_Pin GPIO_PIN_3
#define McuCsVn02_GPIO_Port GPIOE
#define McuCsVn03_Pin GPIO_PIN_4
#define McuCsVn03_GPIO_Port GPIOE
#define McuCsVn04_Pin GPIO_PIN_5
#define McuCsVn04_GPIO_Port GPIOE
#define McuCsVn05_Pin GPIO_PIN_6
#define McuCsVn05_GPIO_Port GPIOE
#define McpLedKeys02_Pin GPIO_PIN_13
#define McpLedKeys02_GPIO_Port GPIOC
#define McuBtInt_Pin GPIO_PIN_2
#define McuBtInt_GPIO_Port GPIOF
#define McuCol03_Pin GPIO_PIN_3
#define McuCol03_GPIO_Port GPIOF
#define McuIn01_Pin GPIO_PIN_0
#define McuIn01_GPIO_Port GPIOA
#define McuIn02_Pin GPIO_PIN_1
#define McuIn02_GPIO_Port GPIOA
#define McuIn03_Pin GPIO_PIN_2
#define McuIn03_GPIO_Port GPIOA
#define McuIn04_Pin GPIO_PIN_3
#define McuIn04_GPIO_Port GPIOA
#define McuIn05_Pin GPIO_PIN_4
#define McuIn05_GPIO_Port GPIOA
#define McuIn06_Pin GPIO_PIN_5
#define McuIn06_GPIO_Port GPIOA
#define McuIn07_Pin GPIO_PIN_6
#define McuIn07_GPIO_Port GPIOA
#define McuIn08_Pin GPIO_PIN_7
#define McuIn08_GPIO_Port GPIOA
#define McuInVn_Pin GPIO_PIN_0
#define McuInVn_GPIO_Port GPIOB
#define McuLedVd_Pin GPIO_PIN_2
#define McuLedVd_GPIO_Port GPIOB
#define McuCsVn06_Pin GPIO_PIN_7
#define McuCsVn06_GPIO_Port GPIOE
#define McuCsVn08_Pin GPIO_PIN_8
#define McuCsVn08_GPIO_Port GPIOE
#define McuCsVn09_Pin GPIO_PIN_9
#define McuCsVn09_GPIO_Port GPIOE
#define Mcu485RxEn_Pin GPIO_PIN_10
#define Mcu485RxEn_GPIO_Port GPIOE
#define McuNordicSck_Pin GPIO_PIN_13
#define McuNordicSck_GPIO_Port GPIOE
#define McuNordicMiso_Pin GPIO_PIN_14
#define McuNordicMiso_GPIO_Port GPIOE
#define McuNordicMosi_Pin GPIO_PIN_15
#define McuNordicMosi_GPIO_Port GPIOE
#define McuIn07B10_Pin GPIO_PIN_10
#define McuIn07B10_GPIO_Port GPIOB
#define McuOut09_Pin GPIO_PIN_11
#define McuOut09_GPIO_Port GPIOB
#define McuLin03_Pin GPIO_PIN_12
#define McuLin03_GPIO_Port GPIOB
#define McuLin04_Pin GPIO_PIN_15
#define McuLin04_GPIO_Port GPIOB
#define McuNordicTxEn_Pin GPIO_PIN_8
#define McuNordicTxEn_GPIO_Port GPIOD
#define McuNordicPwrUp_Pin GPIO_PIN_9
#define McuNordicPwrUp_GPIO_Port GPIOD
#define McuNordicCs_Pin GPIO_PIN_10
#define McuNordicCs_GPIO_Port GPIOD
#define Mcu485TxEn_Pin GPIO_PIN_12
#define Mcu485TxEn_GPIO_Port GPIOD
#define McuBtTx_Pin GPIO_PIN_13
#define McuBtTx_GPIO_Port GPIOD
#define McuBtRx_Pin GPIO_PIN_14
#define McuBtRx_GPIO_Port GPIOD
#define McuFlashReset_Pin GPIO_PIN_15
#define McuFlashReset_GPIO_Port GPIOD
#define McuLedkeys01_Pin GPIO_PIN_6
#define McuLedkeys01_GPIO_Port GPIOC
#define McuOut01_Pin GPIO_PIN_8
#define McuOut01_GPIO_Port GPIOA
#define McuOut02_Pin GPIO_PIN_9
#define McuOut02_GPIO_Port GPIOA
#define McuOut03_Pin GPIO_PIN_10
#define McuOut03_GPIO_Port GPIOA
#define McuOut04_Pin GPIO_PIN_11
#define McuOut04_GPIO_Port GPIOA
#define McuCol02_Pin GPIO_PIN_12
#define McuCol02_GPIO_Port GPIOA
#define McuCol04_Pin GPIO_PIN_6
#define McuCol04_GPIO_Port GPIOF
#define McuPwm05_Pin GPIO_PIN_15
#define McuPwm05_GPIO_Port GPIOA
#define McuFlashCs_Pin GPIO_PIN_12
#define McuFlashCs_GPIO_Port GPIOC
#define McuCol01_Pin GPIO_PIN_0
#define McuCol01_GPIO_Port GPIOD
#define McuFlashSck_Pin GPIO_PIN_1
#define McuFlashSck_GPIO_Port GPIOD
#define McuNordicAm_Pin GPIO_PIN_2
#define McuNordicAm_GPIO_Port GPIOD
#define McuFlashMiso_Pin GPIO_PIN_3
#define McuFlashMiso_GPIO_Port GPIOD
#define McuFlashMosi_Pin GPIO_PIN_4
#define McuFlashMosi_GPIO_Port GPIOD
#define McuNordicTrxCe_Pin GPIO_PIN_5
#define McuNordicTrxCe_GPIO_Port GPIOD
#define McuNordicCd_Pin GPIO_PIN_6
#define McuNordicCd_GPIO_Port GPIOD
#define McuNordicDr_Pin GPIO_PIN_7
#define McuNordicDr_GPIO_Port GPIOD
#define McuIn05B3_Pin GPIO_PIN_3
#define McuIn05B3_GPIO_Port GPIOB
#define McuIn08B4_Pin GPIO_PIN_4
#define McuIn08B4_GPIO_Port GPIOB
#define McuLin01_Pin GPIO_PIN_5
#define McuLin01_GPIO_Port GPIOB
#define McuLin02_Pin GPIO_PIN_6
#define McuLin02_GPIO_Port GPIOB
#define McuNordicuCClk_Pin GPIO_PIN_7
#define McuNordicuCClk_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

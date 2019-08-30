/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Inputs.h"
#include "MyTypes.h"
#include "Nrf905.h"
#include "stm32f0xx_hal.h"
#include "MyFlash.h"
#include "RemoteControl.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
__attribute__((__section__(".user_data")))  uint8_t userConfig[64] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00 };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */
	u32t ToSend;
	uint8_t i;
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_TIM6_Init();
	/* USER CODE BEGIN 2 */

	//uint32_t aux = 0;//, Check = 0;
	//uint8_t aux8 = 0xFF;
	//aux = 123456;

//	uint8_t TxBuffer[32] =
//	                { 0x00, 0x01, 0x02, 0x03 };

//	testar se está gravado caso contrario gravar dados seguros;
//	FlashWriteU32(kFlashPageCheckAddress, kCheckValue);
//	Check = FlashReadU32(kFlashPageCheckAddress);
//
//	if (Check > 0)
//	{
//		HAL_Delay(1);
//	}

	nRf905SetConfig();

	nRf905SetTxAddr(0xFFFFFFFF);
	nRf905SetRxAddr(0xFFFFFFFF);

	ToSend.u32v = 0x12345678;
		nRf905SendPacket(ToSend.u8v, 4);
		for(i = 0; i < 50; i++)
		{
			Nrf905SetMode(eTrasmitShockBurstMode);
			HAL_Delay(50);

			Nrf905SetMode(eReceiveShockBurstMode);
			HAL_Delay(50);
			HAL_GPIO_TogglePin(McuLed4_GPIO_Port, McuLed4_Pin);
		}

	if (HAL_TIM_Base_Start_IT(&htim6) != HAL_OK)
	{
		while (1);
	}

	InputsInit();

	Nrf905SetMode(eReceiveShockBurstMode);
	HAL_Delay(50);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		if (Nrf905GetDr() == 1)
		{
			HAL_GPIO_TogglePin(McuLed1_GPIO_Port, McuLed1_Pin);
		}

		if (Nrf905GetCd() == 1)
		{
			HAL_GPIO_TogglePin(McuLed2_GPIO_Port, McuLed2_Pin);
		}

		//RemoteControlInit();

		//if (InputsGetState(In01))
		if(KeysGetState() ==  kSwProg)
		{
			//HAL_GPIO_WritePin(McuLed1_GPIO_Port, McuLed1_Pin, GPIO_PIN_SET);
		}
		else
		{
			//HAL_GPIO_WritePin(McuLed1_GPIO_Port, McuLed1_Pin, GPIO_PIN_RESET);
		}

		//HAL_GPIO_TogglePin(McuLed3_GPIO_Port, McuLed3_Pin);

		//HAL_Delay(1);
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */
/*
 * This interrupt run at 100Hz
 * Inputs capture
 * Power and sleep control
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	uint8_t cnt;
	static int16_t McuPwrCnt;
	if (htim->Instance == TIM6)
	{

		InputsPeriodic();

		for (cnt = 0; cnt <= 10; cnt++)
		{
			if (InputsGetState(cnt))
			{
				McuPwrCnt = 250;
			}
		}

		if (McuPwrCnt > 0)
		{
			McuPwrCnt--;
			HAL_GPIO_WritePin(McuPwr_GPIO_Port, McuPwr_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(McuLed4_GPIO_Port, McuLed4_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(McuPwr_GPIO_Port, McuPwr_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(McuLed4_GPIO_Port, McuLed4_Pin, GPIO_PIN_RESET);
		}
	}
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(char *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

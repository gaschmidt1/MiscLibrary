/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

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
/* USER CODE BEGIN Variables */
uint16_t counter_1000 = 0;
uint8_t counter_250 = 0;
uint8_t toggle_ctrl = 0;
uint8_t toggle_led = 0;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* definition and creation of defaultTask */
	 osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	 defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	  counter_250++;
	  counter_1000++;
	  if(counter_250 >= 250)
	  {
		  counter_250 = 0;
		  switch(toggle_ctrl)
		  {
		  case 0:
			  HAL_GPIO_TogglePin(MCU_OUT_01_GPIO_Port,MCU_OUT_01_Pin);
			  toggle_ctrl++;
			  break;

		  case 1:
			  HAL_GPIO_TogglePin(MCU_OUT_02_GPIO_Port,MCU_OUT_02_Pin);
			  toggle_ctrl++;
	  	  	  break;

		  case 2:
			  HAL_GPIO_TogglePin(MCU_OUT_03_GPIO_Port,MCU_OUT_03_Pin);
			  toggle_ctrl++;
			  break;

		  case 3:
			  HAL_GPIO_TogglePin(MCU_OUT_04_GPIO_Port,MCU_OUT_04_Pin);
			  toggle_ctrl++;
			  break;

		  case 4:
			  HAL_GPIO_TogglePin(MCU_OUT_05_GPIO_Port,MCU_OUT_05_Pin);
			  toggle_ctrl++;
			  break;

		  case 5:
			  HAL_GPIO_TogglePin(MCU_OUT_06_GPIO_Port,MCU_OUT_06_Pin);
			  toggle_ctrl++;
			  break;

		  case 6:
			  HAL_GPIO_TogglePin(MCU_OUT_07_GPIO_Port,MCU_OUT_07_Pin);
			  toggle_ctrl++;
			  break;

		  case 7:
			  HAL_GPIO_TogglePin(MCU_OUT_08_GPIO_Port,MCU_OUT_08_Pin);
			  toggle_ctrl++;
			  break;

		  case 8:
			  HAL_GPIO_TogglePin(MCU_OUT_09_GPIO_Port,MCU_OUT_09_Pin);
			  toggle_ctrl++;
			  break;

		  case 9:
			  HAL_GPIO_TogglePin(MCU_OUT_10_GPIO_Port,MCU_OUT_10_Pin);
			  toggle_ctrl++;
			  break;

		  case 10:
			  HAL_GPIO_TogglePin(MCU_OUT_11_GPIO_Port,MCU_OUT_11_Pin);
			  toggle_ctrl++;
			  break;

		  case 11:
			  HAL_GPIO_TogglePin(MCU_OUT_12_GPIO_Port,MCU_OUT_12_Pin);
			  toggle_ctrl++;
			  break;

		  case 12:
			  HAL_GPIO_TogglePin(MCU_OUT_13_GPIO_Port,MCU_OUT_13_Pin);
			  toggle_ctrl++;
			  break;

		  case 13:
			  HAL_GPIO_TogglePin(MCU_OUT_14_GPIO_Port,MCU_OUT_14_Pin);
			  toggle_ctrl++;
			  break;

		  case 14:
			  HAL_GPIO_TogglePin(MCU_OUT_15_GPIO_Port,MCU_OUT_15_Pin);
			  toggle_ctrl++;
			  break;

		  case 15:
			  HAL_GPIO_TogglePin(MCU_OUT_16_GPIO_Port,MCU_OUT_16_Pin);
			  toggle_ctrl = 0;
			  break;
		  }
	  }
	  if(counter_1000>=1000)
	  {
		  counter_1000 = 0;
		  HAL_GPIO_WritePin(LED_VD_GPIO_Port,LED_VD_Pin,toggle_led);
		  HAL_GPIO_WritePin(LED_VM_GPIO_Port,LED_VM_Pin,!toggle_led);
		  toggle_led = !toggle_led;
	  }

    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/*
 * Application_x.c
 *
 *  Created on: 11 de jan de 2019
 *      Author: giovani
 */


#include <Application_x.h>
#include <CyBLE.h>
#include <Inputs.h>
#include <MemManager.h>
#include <NetCommands.h>
#include <NRF905.h>
#include <Outputs.h>
#include <stddef.h>
#include <sys/_stdint.h>
#include <usart.h>
#include <VN5025.h>
#include "string.h"
#include "main.h"


uint8_t __attribute__((section (".myBufSection"))) eedata_values[19] =
    {

	0x01, //Serial number
	0x0D, //Serial number
	0x00, //Serial number
	0x05, //Serial number

	0x00

    };


osPoolDef (AplicacaoDataPool, 1, Fake_EEPROM_Typedef);

void ApplicationTask(void const * argument);
void InputFilterTask(void const * argument);
void LedRunTask(void const * argument);

void App_Outputs_Init(void);
void App_Inputs_Init(void);

static void Verify_App_Flash(void);
static void Copy_App_Vars(void);
static Fake_EEPROM_Typedef Copia_P1178_Variaveis;

static uint16_t received_key = 0;

static void Load_Default_Values(void);

void Application_Init(void)
{
  // esta thread roda a aplicação
  osThreadDef(AppTask, ApplicationTask, osPriorityNormal, 0, 256);
  appThreadId = osThreadCreate(osThread(AppTask), NULL);

  // esta thread faz o bonce das entradas
  osThreadDef(FilterTask, InputFilterTask, osPriorityNormal, 0, 256);
  inputFilterThreadId = osThreadCreate(osThread(FilterTask), NULL);

  // thread pisca led run
  osThreadDef(LedTask, LedRunTask, osPriorityNormal, 0, 128);
  LedRunThreadId = osThreadCreate(osThread(LedTask), NULL);

  // este pool troca dados da flash e variaveis de controle
  AplicacaoDataPool_Id = osPoolCreate (osPool(AplicacaoDataPool));
  P1178_Variaveis = (Fake_EEPROM_Typedef *)osPoolCAlloc (AplicacaoDataPool_Id);



  NetCommands_Init();
  App_Outputs_Init();
  App_Inputs_Init();
  CyBLE_Init();

  ProcessInit();

#if USE_NRF905
  NRF905_Init();
#endif

#if VN5025_PROTECTION_ACTIVE
  VN5025_Init_Protection_Task();
#endif

}

/*
 *
 *
 */
void LedRunTask(void const * argument)
{
  for(;;)
    {
	  static uint8_t cnt;
	  if(cnt > 0)
	  {
		  cnt--;
	  }
	  else
	  {
		  cnt = 10;
	  }

	  if(cnt > 9)
	  {
		  GPIO_Change_Pin_State(LED_VM_GPIO_Port, LED_VM_Pin, GPIO_PIN_SET);
	  }
	  else
	  {
	  GPIO_Change_Pin_State(LED_VM_GPIO_Port, LED_VM_Pin, GPIO_PIN_RESET);
	  }
      osDelay(100);
    }
}

/*
 *
 *
 */
void InputFilterTask(void const * argument)
{
  uint32_t wakeuptime;
  for(;;)
    {
      wakeuptime = osKernelSysTick();
      Inputs_Analog_Filter();
      osDelayUntil(&wakeuptime, 1);
    }
}

/*
 *
 *
 */
void ApplicationTask(void const * argument)
{
  uint32_t wakeuptime;
  osEvent evt;

#if USE_NRF905
  evt = osSignalWait(NRF905_Signal_Ready, 3000); // wait for the NRF905 configuration

  PrintDTC("Received from rRF...\n\r");

  if(evt.status == osEventTimeout)
    {
      Error_Handler();
    }
#endif

  if(!Mem_CheckMemory())
    {
      PrintDTC("Loading default values from EEP...\n\r");
      Load_Default_Values();
    }
  else
    {
      PrintDTC("Recovering default values from EEP...\n\r");

      Mem_GetData(P1178_Variaveis, APP_BLOCK_SIZE);
    }

  PrintDTC("Copy default values to RAM...\n\r");
  Copy_App_Vars();
  PrintDTC("running...\n\r");
  PrintDTC("Engine off...\n\r");

  for(;;)
    {
      wakeuptime = osKernelSysTick();

      evt = osSignalWait(APP_FLASH_VERIFY, 0);

      if(evt.status== osEventSignal)
	{
	  PrintDTC("Verify flash...\n\r");
	  Verify_App_Flash();
	}

      received_key = 0;

      if(NRF905_Control->new_payload == 1)
	{
	  NRF905_Control->new_payload = 0;
	  PrintDTC("New key from nRF...\n\r");
	  received_key = ((NRF905_Control->received_rx_payload[1]<<8)|NRF905_Control->received_rx_payload[2]);

	}

      Processo(received_key);

      osDelayUntil(&wakeuptime, kProcessInterval);
    }
}

// todo organizar a ordem das saidas (ordenar por grupos)
void App_Outputs_Init(void)
{
  Outputs_Configure(MCU_OUT_01_GPIO_Port, MCU_OUT_01_Pin, eF01, RELAY);
  Outputs_Configure(MCU_OUT_02_GPIO_Port, MCU_OUT_02_Pin, eF02, RELAY);
  Outputs_Configure(MCU_OUT_03_GPIO_Port, MCU_OUT_03_Pin, eF03, RELAY);
  Outputs_Configure(MCU_OUT_04_GPIO_Port, MCU_OUT_04_Pin, eF04, RELAY);

  Outputs_Configure(MCU_OUT_05_GPIO_Port, MCU_OUT_05_Pin, eF05, RELAY);
  Outputs_Configure(MCU_OUT_06_GPIO_Port, MCU_OUT_06_Pin, eF06, RELAY);
  Outputs_Configure(MCU_OUT_07_GPIO_Port, MCU_OUT_07_Pin, eF07, RELAY);
  Outputs_Configure(MCU_OUT_08_GPIO_Port, MCU_OUT_08_Pin, eF08, RELAY);

  Outputs_Configure(MCU_OUT_09_GPIO_Port, MCU_OUT_09_Pin, eF09, RELAY);
  Outputs_Configure(MCU_OUT_10_GPIO_Port, MCU_OUT_10_Pin, eF10, RELAY);
  Outputs_Configure(MCU_OUT_11_GPIO_Port, MCU_OUT_11_Pin, eF11, RELAY);
  Outputs_Configure(MCU_OUT_12_GPIO_Port, MCU_OUT_12_Pin, eF12, RELAY);

  Outputs_Configure(MCU_OUT_13_GPIO_Port, MCU_OUT_13_Pin, eF13, RELAY);
  Outputs_Configure(MCU_OUT_14_GPIO_Port, MCU_OUT_14_Pin, eF14, RELAY);
  Outputs_Configure(MCU_OUT_15_GPIO_Port, MCU_OUT_15_Pin, eF15, RELAY);
  Outputs_Configure(MCU_OUT_16_GPIO_Port, MCU_OUT_16_Pin, eF16, RELAY);

  Outputs_Start_PWM();
}


void App_Inputs_Init(void)
{
  Inputs_Configure(MCU_IN_01_Port, 		MCU_IN_01_Pin, 		eEntradaF1, 	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_02_Port, 		MCU_IN_02_Pin, 		eEntradaF2, 	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_03_Port, 		MCU_IN_03_Pin, 		eEntradaF3,  	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_04_Port, 		MCU_IN_04_Pin, 		eEntradaF4, 	ANALOG, 10, 10, 500);

  Inputs_Configure(MCU_IN_05_Port, 		MCU_IN_05_Pin, 		eEntradaF5,  	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_06_Port, 		MCU_IN_06_Pin, 		eEntradaF6,  	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_07_Port, 		MCU_IN_07_Pin, 		eEntradaF7,  	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_08_Port, 		MCU_IN_08_Pin, 		eEntradaF8,  	ANALOG, 10, 10, 500);

  Inputs_Configure(MCU_IN_09_Port, 		MCU_IN_09_Pin, 		eEntradaF9,  	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_10_Port, 		MCU_IN_10_Pin, 		eEntradaF10, 	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_11_Port, 		MCU_IN_11_Pin, 		eEntradaF11, 	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_12_Port, 		MCU_IN_12_Pin, 		eEntradaF12, 	ANALOG, 10, 10, 500);

  Inputs_Configure(MCU_IN_13_Port, 		MCU_IN_13_Pin, 		eEntradaF13, 	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_IN_14_Port, 		MCU_IN_14_Pin, 		eEntradaF14, 	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_ADC_15_VN_GPIO_Port, 	MCU_ADC_15_VN_Pin, 	eEntradaF15, 	ANALOG, 10, 10, 500);
  Inputs_Configure(MCU_ADC_16_VN_GPIO_Port,	MCU_ADC_16_VN_Pin, 	eEntradaF16, 	ANALOG, 10, 10, 500);

  Inputs_Start_Analog();
}


static void Load_Default_Values(void)
{
  //braço
  P1178_Variaveis->Variaveis.RoscaTuboDesligada = eedata_values[4];
  P1178_Variaveis->Variaveis.RoscaTuboLigada = eedata_values[5];
  P1178_Variaveis->Variaveis.RoscaTuboRampa = eedata_values[6];
  //lateral
  P1178_Variaveis->Variaveis.RoscaElevacaoDesligada = eedata_values[7];
  P1178_Variaveis->Variaveis.RoscaElevacaoLigada = eedata_values[8];
  P1178_Variaveis->Variaveis.RoscaElevacaoRampa = eedata_values[9];
  //inferior
  P1178_Variaveis->Variaveis.RoscaInferiorDesligada = eedata_values[10];
  P1178_Variaveis->Variaveis.RoscaInferiorLigada = eedata_values[11];
  P1178_Variaveis->Variaveis.RoscaInferiorRampa = eedata_values[12];
  //cotovelo
  P1178_Variaveis->Variaveis.TuboHorario = eedata_values[13];
  P1178_Variaveis->Variaveis.TuboAntiHorario = eedata_values[14];
  P1178_Variaveis->Variaveis.TuboParado = eedata_values[15];
  P1178_Variaveis->Variaveis.TuboRampa = eedata_values[16];
  //tempos
  P1178_Variaveis->Variaveis.OutrosTempoIgnicao = eedata_values[17];
  P1178_Variaveis->Variaveis.OutrosTempoMovimentoComportas = eedata_values[18];
  Mem_WriteData(P1178_Variaveis,APP_BLOCK_SIZE);
}


static void Copy_App_Vars(void)
{
  uint8_t i;
  for (i = 0 ; i < APP_BLOCK_SIZE; i++)
    {
      Copia_P1178_Variaveis.Data_Values[i] = P1178_Variaveis->Data_Values[i];
    }
}


static void Verify_App_Flash(void)
{
  uint8_t i;
  uint8_t not_Equal = 0;

  for(i = 0 ; i < APP_BLOCK_SIZE; i++)
    {
      if(Copia_P1178_Variaveis.Data_Values[i] != P1178_Variaveis->Data_Values[i])
	{
	  not_Equal = 1;
	  break;
	}
    }

  if(not_Equal)
    {
      Mem_WriteData(P1178_Variaveis,APP_BLOCK_SIZE);
      Copy_App_Vars();
    }
}

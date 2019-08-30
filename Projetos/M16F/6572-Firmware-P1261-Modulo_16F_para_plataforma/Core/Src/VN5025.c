/*
 * VN5025.c
 *
 *  Created on: 18 de jan de 2019
 *      Author: giovani
 */
#include "adc.h"
#include "tim.h"
#include "Outputs.h"
#include "VN5025.h"

void Vn5025Task(void const * argument);

osPoolDef (VN5025Pool, 1, VN50250_ADC_Values_Typedef);
osPoolDef (VN5025FlagsPool, 1, Outputs_State_Typedef);

uint8_t activated_vn = 0;
uint8_t vn_indexer_count = 0;
uint8_t firts_output_index = 0;
uint8_t first_time_index = 0;
uint8_t last_output_index = 0;

void VN5025_Init(PCB_Outputs_TypeDefs pcb_output)
{
  activated_vn++;
  last_output_index = pcb_output;
  if(!first_time_index)
    {
      first_time_index = 1;
      firts_output_index = pcb_output;
      vn_indexer_count = pcb_output;
    }
  switch(pcb_output)
  {
    case OUT_1 :
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD1_01_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD1_01_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_15;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_2:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD1_02_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD1_02_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_15;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_3:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD1_03_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD1_03_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_15;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_4:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD1_04_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD1_04_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_15;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_5:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD1_05_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD1_05_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_15;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_6:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD1_06_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD1_06_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_15;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_7:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD1_07_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD1_07_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_15;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_8:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD1_08_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD1_08_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_15;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_9:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD2_01_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD2_01_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_16;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_10:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD2_02_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD2_02_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_16;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_11:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD2_03_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD2_03_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_16;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_12:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD2_04_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD2_04_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_16;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_13:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD2_05_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD2_05_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_16;
      VN5025_Interface[vn_indexer_count].max_adc_value =5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_14:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD2_06_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD2_06_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_16;
      VN5025_Interface[vn_indexer_count].max_adc_value =5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_15:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD2_07_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD2_07_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_16;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    case OUT_16:
      VN5025_Interface[vn_indexer_count].mcu_enable_pin = MCU_CSD2_08_Pin;
      VN5025_Interface[vn_indexer_count].mcu_enable_port = MCU_CSD2_08_Port;
      VN5025_Interface[vn_indexer_count].adc_channel = ADC_16;
      VN5025_Interface[vn_indexer_count].max_adc_value = 5;
      GPIO_Configure_as_Output(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin);
      GPIO_Change_Pin_State(VN5025_Interface[vn_indexer_count].mcu_enable_port,VN5025_Interface[vn_indexer_count].mcu_enable_pin,1);
      vn_indexer_count++;
      break;

    default:
      Error_Handler();
      break;
  }
}

void VN5025_Init_Protection_Task(void)
{
  MX_TIM6_Init();

  osThreadDef(vn5025Task, Vn5025Task, osPriorityAboveNormal, 0, 256);
  vn5025TaskId = osThreadCreate(osThread(vn5025Task), NULL);

  VN5025AdcPoolId = osPoolCreate(osPool(VN5025Pool));
  VN5025_Adc = osPoolCAlloc (VN5025AdcPoolId);

  VN5025FlagsPoolId = osPoolCreate(osPool(VN5025FlagsPool));
  Outputs_Flags = osPoolCAlloc (VN5025FlagsPoolId);
}

uint16_t average_value = 0;

void Vn5025Task(void const * argument)
{
  osEvent evt;
  uint8_t vn_scanner_index = firts_output_index;
  uint8_t convertion_started = 0;

  TIM_Start_Base(&htim6);
  for(;;)
    {
      if(!convertion_started)
	{
	  GPIO_Change_Pin_State(VN5025_Interface[vn_scanner_index].mcu_enable_port,VN5025_Interface[vn_scanner_index].mcu_enable_pin,0);
	  convertion_started = 1;
	  VN5025_Adc->VN_CSD1_SAMPLES_COUNT = 0;
	  VN5025_Adc->VN_CSD2_SAMPLES_COUNT = 0;
	  VN5025_Adc->VN_CSD1_SUM_VAL = 0;
	  VN5025_Adc->VN_CSD2_SUM_VAL = 0;
	}
      else
	{

	  if(VN5025_Interface[vn_scanner_index].adc_channel == ADC_15)
	    {
	      average_value = VN5025_Adc->VN_CSD1_SUM_VAL / VN5025_Adc->VN_CSD1_SAMPLES_COUNT;
	    }
	  else
	    {
	      average_value = VN5025_Adc->VN_CSD2_SUM_VAL / VN5025_Adc->VN_CSD2_SAMPLES_COUNT;
	    }

	  convertion_started = 0;
	  GPIO_Change_Pin_State(VN5025_Interface[vn_scanner_index].mcu_enable_port,VN5025_Interface[vn_scanner_index].mcu_enable_pin,1);

	  if(average_value >= VN5025_Interface[vn_scanner_index].max_adc_value)
	    {
	      Outputs_Flags->Outputs_Error |= (uint16_t) (0x01<<vn_scanner_index);
	    }
	  else
	    {
	      Outputs_Flags->Outputs_Error &= (uint16_t)~(0x01<<vn_scanner_index);
	    }

	  vn_scanner_index++;

	  if(vn_scanner_index > last_output_index)
	    {
	      vn_scanner_index = firts_output_index;
	    }

	}
      evt = osSignalWait(0x01, osWaitForever);
      evt = evt;
    }
}

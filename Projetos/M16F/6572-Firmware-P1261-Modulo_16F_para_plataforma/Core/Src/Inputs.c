/*
 * Inputs.c
 *
 *  Created on: 14 de jan de 2019
 *      Author: giovani
 */

#include "Inputs.h"
#include "adc.h"
uint8_t inputs_index = 0;
//static uint16_t inputs_raw_adc[INPUTS_COUNT];
uint8_t adc_input_count = 0;
uint8_t digital_input_count = 0;

void Inputs_Configure( GPIO_TypeDef  *GPIOx, uint32_t in_pin, App_Inputs input_name, input_function function, uint32_t debounce_up, uint32_t debounce_down,uint16_t adc_th)
{
  if(inputs_index < INPUTS_COUNT)
    {
      Inputs_Interface[inputs_index].mcu_input_port = GPIOx;
      Inputs_Interface[inputs_index].mcu_input_pin = in_pin;
      Inputs_Interface[inputs_index].app_input_name = input_name;
      Inputs_Interface[inputs_index].input_function = function;

      Inputs_Interface[inputs_index].debounce_up = debounce_up;
      Inputs_Interface[inputs_index].debouce_down = debounce_down;

      Inputs_Interface[inputs_index].debouce_down_counter = 0;
      Inputs_Interface[inputs_index].debouce_up_counter = 0;

      Inputs_Interface[inputs_index].old_state_flag = 0;
      Inputs_Interface[inputs_index].aux_flag = 0;
      Inputs_Interface[inputs_index].hit_flag = 0;
      Inputs_Interface[inputs_index].state_flag = 0;

      Inputs_Interface[inputs_index].adc_threshold = adc_th;
      Inputs_Interface[inputs_index].adc_value = 0;

      if(function == DIGITAL)
	{
	  digital_input_count++;
	  GPIO_Configure_as_Input(GPIOx, in_pin);
	}
      else if(function == ANALOG)
	{
	  adc_input_count ++;
	  GPIO_Configure_as_Analog(GPIOx,in_pin);
	}
      inputs_index++;
    }
}

void Inputs_Digital_Filter(void)
{
  uint8_t i;
  uint8_t state;
  for(i = 0; i < inputs_index ; i++)
    {
      if(Inputs_Interface[i].input_function == DIGITAL)
	{
	  state = HAL_GPIO_ReadPin(Inputs_Interface[i].mcu_input_port , Inputs_Interface[i].mcu_input_pin);
	  if(!state)
	    {
	      if(!Inputs_Interface[i].state_flag)
		{
		  if(Inputs_Interface[i].debouce_down_counter < Inputs_Interface[i].debouce_down)
		    {
		      Inputs_Interface[i].debouce_down_counter++;
		    }
		  else
		    {
		      Inputs_Interface[i].debouce_up_counter = 0;
		      Inputs_Interface[i].state_flag = 1;

		      if(Inputs_Interface[i].state_flag != Inputs_Interface[i].old_state_flag)
			{
			  Inputs_Interface[i].old_state_flag = Inputs_Interface[i].state_flag;
			  Inputs_Interface[i].hit_flag = 1;
			}
		    }
		}
	    }
	  else
	    {
	      if(Inputs_Interface[i].state_flag)
		{
		  if(Inputs_Interface[i].debouce_up_counter < Inputs_Interface[i].debounce_up)
		    {
		      Inputs_Interface[i].debouce_up_counter++;
		    }
		  else
		    {
		      Inputs_Interface[i].debouce_down_counter = 0;
		      Inputs_Interface[i].state_flag = 0;
		      if(Inputs_Interface[i].state_flag  !=  Inputs_Interface[i].old_state_flag)
			{
			  Inputs_Interface[i].old_state_flag = Inputs_Interface[i].state_flag;
			  Inputs_Interface[i].hit_flag = 1;
			}
		    }
		}
	    }
	}
    }
}


void Inputs_Analog_Filter(void)
{
  uint8_t i = 0;
  if(ADC_is_Convertion_Completed())
    {
      for(i = 0; i < inputs_index ; i++)
	{
	  if(Inputs_Interface[i].input_function == ANALOG)
	    {
	      Inputs_Interface[i].adc_value =  GetRawAdcValue(i);
	      if(Inputs_Interface[i].adc_value < Inputs_Interface[i].adc_threshold)
		{
		  if(Inputs_Interface[i].state_flag)
		    {
		      if(Inputs_Interface[i].debouce_down_counter < Inputs_Interface[i].debouce_down)
			{
			  Inputs_Interface[i].debouce_down_counter++;
			}
		      else
			{
			  Inputs_Interface[i].debouce_up_counter = 0;
			  Inputs_Interface[i].state_flag = 0;

			  if(Inputs_Interface[i].state_flag != Inputs_Interface[i].old_state_flag)
			    {
			      Inputs_Interface[i].old_state_flag = Inputs_Interface[i].state_flag;
			      Inputs_Interface[i].hit_flag = 1;
			    }
			}
		    }
		}
	      else
		{
		  if(!Inputs_Interface[i].state_flag)
		    {
		      if(Inputs_Interface[i].debouce_up_counter < Inputs_Interface[i].debounce_up)
			{
			  Inputs_Interface[i].debouce_up_counter++;
			}
		      else
			{
			  Inputs_Interface[i].debouce_down_counter = 0;
			  Inputs_Interface[i].state_flag = 1;
			  if(Inputs_Interface[i].state_flag  !=  Inputs_Interface[i].old_state_flag)
			    {
			      Inputs_Interface[i].old_state_flag = Inputs_Interface[i].state_flag;
			      Inputs_Interface[i].hit_flag = 1;
			    }
			}
		    }
		}
	    }
	}
    }

}

void Inputs_Start_Analog(void)
{
  uint8_t i;
  uint32_t channel_tmp = 0;
  uint8_t rank_number = 1;
  MX_ADC_Init();
  for(i = 0; i <inputs_index; i++)
    {
      if(Inputs_Interface[i].input_function == ANALOG)
	{
	  channel_tmp = ADC_Get_Channel(Inputs_Interface[i].mcu_input_port,Inputs_Interface[i].mcu_input_pin);
	  ADC_Configure_Channel(channel_tmp,rank_number);
	  rank_number++;
	}
    }
  ADC_Start_Convertion(adc_input_count);
}


uint8_t Inputs_Get_Input_State(App_Inputs app_input_name)
{
  uint8_t i;
  for(i = 0; i < inputs_index; i++)
    {
      if(Inputs_Interface[i].app_input_name == app_input_name)
	{
	  return Inputs_Interface[i].state_flag;
	}
    }
  return 0 ;
}

uint16_t Inputs_Get_Analog_Value(App_Inputs app_input_name)
{
  uint8_t i;
  for(i = 0; i < inputs_index; i++)
    {
      if(Inputs_Interface[i].app_input_name == app_input_name)
	{
	  return Inputs_Interface[i].adc_value;
	}
    }
  return 0;
}


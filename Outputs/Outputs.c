/*
 * Ouputs.c
 *
 *  Created on: 11 de jan de 2019
 *      Author: giovani
 */



#include "Application_x.h"
#include "Outputs.h"


uint8_t outputs_index = 0;
uint8_t relay_index = 0;
uint8_t pwm_index = 0;
uint8_t vn_index = 1;


void Outputs_Configure( GPIO_TypeDef  *GPIOx, uint32_t out_pin,  App_Outputs app_name, output_function function )
{
  if(outputs_index < OUTPUTS_COUNT)
    {
      Outputs_Interface[outputs_index].mcu_output_port = GPIOx;
      Outputs_Interface[outputs_index].mcu_output_pin = out_pin;
      Outputs_Interface[outputs_index].app_output_name = app_name;
      Outputs_Interface[outputs_index].output_function = function;
      Outputs_Interface[outputs_index].output_state = 0;
      if(function == RELAY)
	{
	  relay_index++;
	  Outputs_Interface[outputs_index].output_pwm = 0;
	  GPIO_Configure_as_Output(GPIOx,out_pin);
	}
      else if(function == PWM)
	{
	  TIM_Init_Output_PWM(GPIOx,out_pin);
	  Pwm_Interface[pwm_index].timer_handler = TIM_Get_Handler(GPIOx, out_pin);
	  Pwm_Interface[pwm_index].channel = TIM_Get_Channel(GPIOx, out_pin);
	  Pwm_Interface[pwm_index].duty_cycle = 0;
	  Pwm_Interface[pwm_index].duty_target = 0;
	  Outputs_Interface[outputs_index].output_pwm = &Pwm_Interface[pwm_index];
	  Outputs_Interface[outputs_index].pcb_output_name = GPIO_Return_PCB_Out(GPIOx,out_pin);
#if VN5025_PROTECTION_ACTIVE
	  VN5025_Init(Outputs_Interface[outputs_index].pcb_output_name);
#endif
	  pwm_index++;
	}
      outputs_index++;
    }
}


uint8_t Outputs_Get_PWM_Out_Counter(void)
{
  return pwm_index;
}


void Outputs_Disable_All(void)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {
      GPIO_Change_Pin_State(Outputs_Interface[i].mcu_output_port,Outputs_Interface[i].mcu_output_pin,0);
      Outputs_Interface[i].output_state = 0;
    }
}


void Outputs_Change_State(App_Outputs out_name, output_state state)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {
      if(Outputs_Interface[i].app_output_name == out_name)
	{
	  GPIO_Change_Pin_State(Outputs_Interface[i].mcu_output_port, Outputs_Interface[i].mcu_output_pin, state);

	  Outputs_Interface[i].output_state = state;
	  break;

	}

      Outputs_Interface[i].output_state = Outputs_Interface[i].output_state;
    }
}


/*
 * 		Rotina para ler o status atual de uma saida
 * 		retorna 0 para desligada e 1 para ligada
 * 		Gerry
 */
output_state Outputs_Get_State(App_Outputs out_name)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {
      if(Outputs_Interface[i].app_output_name == out_name)
	{
	  return(Outputs_Interface[i].output_state);
	}
    }
  return(ERROR);
}


void Outputs_Toggle(App_Outputs out_name)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {
      if(Outputs_Interface[i].app_output_name == out_name)
	{
	  GPIO_Toggle_Pin(Outputs_Interface[i].mcu_output_port,Outputs_Interface[i].mcu_output_pin);
	  break;
	}
    }
}


void Outputs_Start_PWM(void)
{
  uint8_t i;
  uint8_t htim1_started = 0,htim2_started = 0,htim3_started = 0,htim15_started = 0,htim16_started = 0,htim17_started = 0;

  for(i = 0; i<outputs_index ; i++)
    {
      if(Outputs_Interface[i].output_function == PWM)
	{
	  if(Outputs_Interface[i].output_pwm->timer_handler == &htim1 && !htim1_started)
	    {
	      MX_TIM1_Init();
	      htim1_started = 1;
	    }
	  else if(Outputs_Interface[i].output_pwm->timer_handler == &htim2 && !htim2_started)
	    {
	      MX_TIM2_Init();
	      htim2_started = 1;
	    }
	  else if(Outputs_Interface[i].output_pwm->timer_handler == &htim3  && !htim3_started)
	    {
	      MX_TIM3_Init();
	      htim3_started = 1;
	    }
	  else if(Outputs_Interface[i].output_pwm->timer_handler == &htim15  && !htim15_started)
	    {
	      MX_TIM15_Init();
	      htim15_started = 1;
	    }
	  else if(Outputs_Interface[i].output_pwm->timer_handler == &htim16  && !htim16_started)
	    {
	      MX_TIM16_Init();
	      htim16_started  = 1;
	    }
	  else if(Outputs_Interface[i].output_pwm->timer_handler == &htim17  && !htim17_started)
	    {
	      MX_TIM17_Init();
	      htim17_started = 1;
	    }
	  TIM_Config_Channel(Outputs_Interface[i].output_pwm->timer_handler,Outputs_Interface[i].output_pwm->channel);
	  HAL_TIM_PWM_Start(Outputs_Interface[i].output_pwm->timer_handler, Outputs_Interface[i].output_pwm->channel);
	}
    }
}

/*
 * 		Rotina para setar o target do PWM
 * 		recebe a saida e o valor para o target
 *
 */
void Outputs_Change_Duty_Cycle(App_Outputs out_name, uint16_t duty_cycle)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {
      if(Outputs_Interface[i].app_output_name == out_name && Outputs_Interface[i].output_function == PWM)
	{
	  Outputs_Interface[i].output_pwm->duty_cycle = duty_cycle;

	  TIM_Change_Duty_Cycle(Outputs_Interface[i].output_pwm->timer_handler,Outputs_Interface[i].output_pwm->channel,Outputs_Interface[i].output_pwm->duty_cycle);
	  break;
	}
    }
}

/*
 * 		Rotina para retornar o target do PWM
 * 		recebe a saida e o valor para o target
 *
 */
uint16_t Outputs_Get_Duty_Cycle(App_Outputs out_name)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {
      if(Outputs_Interface[i].app_output_name == out_name && Outputs_Interface[i].output_function == PWM)
	{
	  return(Outputs_Interface[i].output_pwm->duty_cycle);
	}
    }
  return(0);
}

/*
 * 		Rotina para setar o target do PWM
 * 		recebe a saida e o valor para o target
 * 		Gerry
 */
void Outputs_Change_Duty_Target(App_Outputs out_name, uint16_t duty_target)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {
      if(Outputs_Interface[i].app_output_name == out_name && Outputs_Interface[i].output_function == PWM)
	{
	  Outputs_Interface[i].output_pwm->duty_target = duty_target;
	  break;
	}
    }
}

/*
 * 		Rotina para retornar o target do PWM
 * 		recebe a saida e o valor para o target
 * 		Gerry
 */
uint16_t Outputs_Get_Duty_Target(App_Outputs out_name)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {
      if(Outputs_Interface[i].app_output_name == out_name && Outputs_Interface[i].output_function == PWM)
	{
	  return(Outputs_Interface[i].output_pwm->duty_target);
	}
    }
  return(0);
}

/*
 *  Controlador de rampa do PWM
 *	Compara o duty com o target e equaliza ambos
 *  Gerry
 */

void OutputsPwmRampController(App_Outputs out_name, uint8_t Rampa)
{
  uint8_t i;
  for(i = 0; i < OUTPUTS_COUNT ; i++)
    {

      if(Outputs_Interface[i].app_output_name == out_name && Outputs_Interface[i].output_function == PWM)
	{

	  if(Outputs_Interface[i].output_pwm->duty_target > Outputs_Interface[i].output_pwm->duty_cycle)
	    {
	      Outputs_Interface[i].output_pwm->duty_cycle += Rampa;
	    }

	  else if(Outputs_Interface[i].output_pwm->duty_target < Outputs_Interface[i].output_pwm->duty_cycle)
	    {
	      Outputs_Interface[i].output_pwm->duty_cycle -= Rampa;
	    }

	  if((Outputs_Interface[i].output_pwm->duty_cycle) >= 49)
	    {
	      Outputs_Interface[i].output_pwm->duty_cycle = 49;
	    }

	  if((Outputs_Interface[i].output_pwm->duty_cycle) <= 1)
	    {
	      Outputs_Interface[i].output_pwm->duty_cycle = 1;
	    }

	  Outputs_Change_Duty_Cycle(out_name , Outputs_Interface[i].output_pwm->duty_cycle);
	  break;
	}
    }
}









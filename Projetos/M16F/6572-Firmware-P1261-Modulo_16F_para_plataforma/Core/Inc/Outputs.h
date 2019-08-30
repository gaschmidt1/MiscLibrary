/*
 * Outputs.h
 *
 *  Created on: 11 de jan de 2019
 *      Author: giovani
 */

#ifndef INC_OUTPUTS_H_
#define INC_OUTPUTS_H_


#include "tim.h"
#include "VN5025.h"

#define OUTPUTS_COUNT 16


typedef enum
{
	RELAY = 0,
	PWM = 1,
}output_function;


typedef enum
{
	OFF = 0,
	ON = 1,
}output_state;


typedef enum
{
	eF01 = 0,
	eF02,
	eF03,
	eF04,

	eF05,
	eF06,
	eF07,
	eF08,

	eF09,
	eF10,
	eF11,
	eF12,

	eF13,
	eF14,
	eF15,
	eF16,

}App_Outputs;

typedef struct
{
	TIM_HandleTypeDef *timer_handler;
	uint32_t channel;
	uint32_t freq_hz;
	uint8_t duty_cycle;
	uint8_t duty_target;
}pwm_struct;

pwm_struct Pwm_Interface[OUTPUTS_COUNT];

typedef struct
{
	GPIO_TypeDef  *mcu_output_port;
	uint32_t mcu_output_pin;

	PCB_Outputs_TypeDefs pcb_output_name;
	App_Outputs app_output_name;
	output_function output_function;

	output_state output_state;
	pwm_struct *output_pwm;
}outputs_struct;

outputs_struct Outputs_Interface [OUTPUTS_COUNT];




void Outputs_Configure( GPIO_TypeDef  *GPIOx, uint32_t out_pin,  App_Outputs app_name, output_function function );
void Outputs_Change_State(App_Outputs out_name, output_state state);
output_state Outputs_Get_State(App_Outputs out_name);
void Outputs_Toggle(App_Outputs out_name);
void Outputs_Change_Duty_Cycle(App_Outputs out_name, uint16_t duty_cycle);
uint16_t Outputs_Get_Duty_Cycle(App_Outputs out_name);
void Outputs_Change_Duty_Target(App_Outputs out_name, uint16_t duty_target);
uint16_t Outputs_Get_Duty_Target(App_Outputs out_name);
void OutputsPwmRampController(App_Outputs out_name, uint8_t Rampa);
void Outputs_Disable_All(void);
void Outputs_Start_PWM(void);
uint8_t Outputs_Get_PWM_Out_Counter(void);




#endif /* INC_OUTPUTS_H_ */

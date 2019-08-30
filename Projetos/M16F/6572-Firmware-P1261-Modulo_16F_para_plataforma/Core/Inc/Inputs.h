/*
 * Inputs.h
 *
 *  Created on: 14 de jan de 2019
 *      Author: giovani
 */

#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_


#include "gpio.h"

#define INPUTS_COUNT 16

typedef enum
{
  DIGITAL = 0,
  ANALOG = 1,
}input_function;

typedef enum
{
  eEntradaF1 = 0,
  eEntradaF2,
  eEntradaF3,
  eEntradaF4,

  eEntradaF5,
  eEntradaF6,
  eEntradaF7,
  eEntradaF8,

  eEntradaF9,
  eEntradaF10,
  eEntradaF11,
  eEntradaF12,

  eEntradaF13,
  eEntradaF14,
  eEntradaF15,
  eEntradaF16,
}App_Inputs;

typedef struct
{
  GPIO_TypeDef  *mcu_input_port;
  uint32_t mcu_input_pin;

  App_Inputs app_input_name;
  input_function input_function;

  uint32_t debouce_down;
  uint32_t debounce_up;
  uint8_t state_flag;
  uint8_t old_state_flag;
  uint8_t aux_flag;
  uint8_t hit_flag;
  uint32_t debouce_down_counter;
  uint32_t debouce_up_counter;

  uint16_t adc_value;
  uint16_t adc_threshold;

}inputs_struct;


inputs_struct Inputs_Interface [INPUTS_COUNT];

void Inputs_Digital_Filter(void);
void Inputs_Configure( GPIO_TypeDef  *GPIOx, uint32_t in_pin, App_Inputs input_name, input_function function, uint32_t debounce_up, uint32_t debounce_down,uint16_t adc_th);
void Inputs_Start_Analog(void);
void Inputs_Analog_Filter(void);
uint8_t Inputs_Get_Input_State(App_Inputs app_input_name);
uint16_t Inputs_Get_Analog_Value(App_Inputs app_input_name);
#endif /* INC_INPUTS_H_ */



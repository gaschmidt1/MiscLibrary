/*
 * VN5025.h
 *
 *  Created on: 18 de jan de 2019
 *      Author: giovani
 */

#ifndef INC_VN5025_H_
#define INC_VN5025_H_

#include "cmsis_os.h"
#include "gpio.h"

#define VN5025_PROTECTION_ACTIVE 0U
#define VN5025_COUNT 16

void VN5025_Init(PCB_Outputs_TypeDefs pcb_output);
void VN5025_Init_Protection_Task(void);

osThreadId vn5025TaskId;
osPoolId  VN5025AdcPoolId;
osPoolId  VN5025FlagsPoolId;

typedef union
{
  uint16_t Outputs_Error;
  struct
  {
    uint16_t Out_1:1;
    uint16_t Out_2:1;
    uint16_t Out_3:1;
    uint16_t Out_4:1;
    uint16_t Out_5:1;
    uint16_t Out_6:1;
    uint16_t Out_7:1;
    uint16_t Out_8:1;
    uint16_t Out_9:1;
    uint16_t Out_10:1;
    uint16_t Out_11:1;
    uint16_t Out_12:1;
    uint16_t Out_13:1;
    uint16_t Out_14:1;
    uint16_t Out_15:1;
    uint16_t Out_16:1;
  };
}Outputs_State_Typedef;

Outputs_State_Typedef *Outputs_Flags;

typedef enum
{
  ADC_15 = 0,
  ADC_16,
}Associate_Analog_Channel;

typedef struct
{
  uint16_t max_adc_value;
  uint32_t mcu_enable_pin;
  GPIO_TypeDef  *mcu_enable_port;
  Associate_Analog_Channel adc_channel;
}VN5025_struct;


VN5025_struct VN5025_Interface[VN5025_COUNT];

typedef struct
{
  uint32_t VN_CSD1_SUM_VAL;
  uint32_t VN_CSD2_SUM_VAL;
  uint16_t VN_CSD1_SAMPLES_COUNT;
  uint16_t VN_CSD2_SAMPLES_COUNT;
}VN50250_ADC_Values_Typedef;

VN50250_ADC_Values_Typedef * VN5025_Adc;
#endif /* INC_VN5025_H_ */

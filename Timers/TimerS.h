



#ifndef __TIMER_S_H_
#define __TIMER_S_H_


#include "stm32f0xx_hal.h"
#include <stdbool.h>

/* exemplo

  MX_GPIO_Init();
  MX_TIM2_Init();

  
  uint8_t tmrId1, tmrId2, tmrId3;
  
  TmrInit(&htim2);
  
  tmrId1 = TmrCreate();  
  TmrConfig(tmrId1, 500, test1Function, NULL, false);
  tmrId2 = TmrCreate();  
  TmrConfig(tmrId2, 250, test2Function, NULL, false);
  tmrId3 = TmrCreate();
  TmrConfig(tmrId3,1000, test2Function, NULL, false);
    
  TmrStart(tmrId1);
  TmrStart(tmrId2);
  TmrStart(tmrId3);
  
  HAL_TIM_Base_Start_IT(&htim2);
*/

#define TMR_MAX_SIZE 16
#define UNSUCCESSFUL 0xFF

typedef void (*tmrFnctPtr)(uint8_t);


typedef struct tmr
{
  bool tmrEnable;
  bool tmrStart;
  bool oneTime;
  uint8_t tmrId;
  uint16_t tmrCounter;
  uint16_t tmrMaxValue;
  void (*tmrFnctPtr)(uint8_t);
  uint8_t arg;
} TMR;


void TmrInit(TIM_HandleTypeDef *htim);
uint8_t TmrCreate();
bool TmrConfig(uint8_t tmrId, uint16_t tmrMaxValue, void (*tmrFnctPtr)(uint8_t), uint8_t arg, bool oneTime);
bool TmrStart( uint8_t timerId );
bool TmrStop( uint8_t timerId );
bool TmrReset( uint8_t timerId );
bool TmrDelete( uint8_t timerId );
void TmrProcessPeriodic(TIM_HandleTypeDef *htim);

#endif

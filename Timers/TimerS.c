

#include "TimerS.h"

static TMR TmrModuleArray[TMR_MAX_SIZE];
static TIM_HandleTypeDef *Htim;


bool StopTimer( uint8_t timerId );
bool DeleteTimer( uint8_t timerId );


void TmrInit(TIM_HandleTypeDef *htim)
{
    Htim = htim;

    for (int i=0; i<TMR_MAX_SIZE; i++)
    {
      TmrModuleArray[i].tmrEnable = false;
      TmrModuleArray[i].tmrStart = false;
      TmrModuleArray[i].oneTime = false;
      TmrModuleArray[i].tmrId = 0;
      TmrModuleArray[i].tmrCounter = 0;
      TmrModuleArray[i].tmrMaxValue = 0;
      TmrModuleArray[i].tmrFnctPtr = NULL;
      TmrModuleArray[i].arg = 0;
    }
}

uint8_t TmrCreate(void)
{
  int i = UNSUCCESSFUL;
  
  for (i=0; i<TMR_MAX_SIZE; i++)
  {
    if (TmrModuleArray[i].tmrEnable == false)
    {
       TmrModuleArray[i].tmrEnable = true;
       break;
    }
  }
  
  return (i);
}

bool TmrConfig(uint8_t tmrId, uint16_t tmrMaxValue, void (*tmrFnctPtr)(uint8_t), uint8_t arg, bool oneTime)
{ 
  if ((tmrId > TMR_MAX_SIZE) || (TmrModuleArray[tmrId].tmrEnable == false))
  {
    return (false);
  }
  
  TmrModuleArray[tmrId].tmrStart = false;
  TmrModuleArray[tmrId].tmrCounter = 0;
  
  TmrModuleArray[tmrId].tmrId = tmrId;
  TmrModuleArray[tmrId].tmrMaxValue = tmrMaxValue;
  TmrModuleArray[tmrId].tmrFnctPtr = tmrFnctPtr;
  TmrModuleArray[tmrId].arg = arg;
  TmrModuleArray[tmrId].oneTime = oneTime;
  
  return (true);  
}

bool TmrStart( uint8_t timerId )
{
  
  if ((TmrModuleArray[timerId].tmrEnable == false) ||
     (TmrModuleArray[timerId].tmrStart == true) || 
     (timerId >=  TMR_MAX_SIZE))
  {
    return (false);
  }
  
  TmrModuleArray[timerId].tmrStart = true;
  return (true);
}

bool TmrStop( uint8_t timerId )
{
  return (StopTimer(timerId));
}

bool TmrReset( uint8_t timerId )
{
  if ((TmrModuleArray[timerId].tmrEnable == true) ||
     (TmrModuleArray[timerId].tmrStart == true) ||
     (timerId >=  TMR_MAX_SIZE))
  {
    return (false);
  }
  
  TmrModuleArray[timerId].tmrCounter = 0;
  return (true);
}

bool TmrDelete( uint8_t timerId )
{
  return (DeleteTimer(timerId));
}              

void TmrProcessPeriodic(TIM_HandleTypeDef *htim)
{
  int i;
  
  if (htim->Instance == Htim->Instance)
  {
      for (i=0; i<TMR_MAX_SIZE; i++)
      {
        if (TmrModuleArray[i].tmrEnable == true)
        {
          if (TmrModuleArray[i].tmrStart == true)
          {
            if (TmrModuleArray[i].tmrCounter >= TmrModuleArray[i].tmrMaxValue)
            {
                TmrModuleArray[i].tmrFnctPtr(TmrModuleArray[i].tmrId);
                TmrModuleArray[i].tmrCounter = 0;
                if (TmrModuleArray[i].oneTime == true)
                {
                  StopTimer(i);
                  DeleteTimer(i);
                }
            }
            else
            {
                TmrModuleArray[i].tmrCounter++;
            }
          }   
        }
      }
  }  
}

bool StopTimer( uint8_t timerId )
{
    if ((TmrModuleArray[timerId].tmrEnable == false) ||
     (TmrModuleArray[timerId].tmrStart == false) ||
     (timerId >=  TMR_MAX_SIZE))
  {
    return (false);
  }
  
  TmrModuleArray[timerId].tmrStart = false;
  return (true);
}

bool DeleteTimer( uint8_t timerId )
{
    if ((TmrModuleArray[timerId].tmrEnable == false) ||
     (TmrModuleArray[timerId].tmrStart == true) || 
     (timerId >=  TMR_MAX_SIZE))
  {
    return (false);
  }
  
  TmrModuleArray[timerId].tmrEnable = false;
  TmrModuleArray[timerId].tmrStart = false;
  TmrModuleArray[timerId].oneTime = false;
  TmrModuleArray[timerId].tmrId = 0;
  TmrModuleArray[timerId].tmrCounter = 0;
  TmrModuleArray[timerId].tmrMaxValue = 0;
  TmrModuleArray[timerId].tmrFnctPtr = NULL;
  return (true);
}

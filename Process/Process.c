/*
 * Process.c
 *
 *  Created on: 4 de mar de 2019
 *      Author: gerry
 */

/****************************************************************************
 * Copyright (C) 2019 by gaschmidt                                  		*
 *                                                                          *
 * This file is part of P1176 ComLink product.                              *
 *																			*
 ****************************************************************************/

/**
 * @file Process.h
 * @author gaschmidt
 * @date 4 Mar 2019
 * @brief File containing applications for product P1176 usage for quick reference.
 *
 */

#include <Inputs.h>
#include <main.h>
#include <Outputs.h>
#include <Process.h>
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "adc.h"




void SetCallbackFunc(uint8_t Index, uint16_t nRfKey, void *Function, App_Outputs out_name, output_state stateSet, output_state stateClear, uint8_t TimeOut)
{
  processVector[Index].nRFKey = nRfKey;
  processVector[Index].out_name = out_name;
  processVector[Index].stateSet = stateSet;
  processVector[Index].stateClear = stateClear;
  processVector[Index].Function = Function;
  processVector[Index].TimeOut = TimeOut;
}


void ProcessInit(void)
{
  SetCallbackFunc( 0, kTeclaF1, &Outputs_Change_State, eF01, ON, OFF, 200);
  SetCallbackFunc( 1, kTeclaF2, &Outputs_Change_State, eF11, ON, OFF, 200);
  SetCallbackFunc( 2, kTeclaF3, &Outputs_Change_State, eF03, ON, OFF, 200);

  SetCallbackFunc( 3, kTeclaF4, &Outputs_Change_State, eF02, ON, OFF, 200);
  SetCallbackFunc( 4, kTeclaF5, &Outputs_Change_State, eF12, ON, OFF, 200);
  SetCallbackFunc( 5, kTeclaF6, &Outputs_Change_State, eF04, ON, OFF, 200);

  SetCallbackFunc( 6, kTeclaF7, &Outputs_Change_State, eF05, ON, OFF, 200);
  SetCallbackFunc( 7, kTeclaF8, &Outputs_Change_State, eF06, ON, OFF, 200);
  SetCallbackFunc( 8, kTeclaF9, &Outputs_Change_State, eF07, ON, OFF, 200);

  SetCallbackFunc( 9, kTeclaFA, &Outputs_Change_State, eF09, ON, OFF, 200);
  SetCallbackFunc(10, kTeclaFB, &Outputs_Change_State, eF10, ON, OFF, 200);
  SetCallbackFunc(11, kTeclaFC, &Outputs_Change_State, eF08, ON, OFF, 200);

//  SetCallbackFunc(12, kTeclaFD, &Outputs_Change_State, eF13, ON, OFF, 200);
//  SetCallbackFunc(13, kTeclaFE, &Outputs_Change_State, eF14, ON, OFF, 200);
//  SetCallbackFunc(14, kTeclaFF, &Outputs_Change_State, eF15, ON, OFF, 200);
//  SetCallbackFunc(15, kTeclaFG, &Outputs_Change_State, eF16, ON, OFF, 200);
//
//  SetCallbackFunc( 0, kTeclaF1, &Outputs_Change_State, eF01, ON, OFF, 200);
//  SetCallbackFunc( 1, kTeclaF2, &Outputs_Change_State, eF02, ON, OFF, 200);
//  SetCallbackFunc( 2, kTeclaF3, &Outputs_Change_State, eF03, ON, OFF, 200);
//
//  SetCallbackFunc( 3, kTeclaF4, &Outputs_Change_State, eF04, ON, OFF, 200);
//  SetCallbackFunc( 4, kTeclaF5, &Outputs_Change_State, eF05, ON, OFF, 200);
//  SetCallbackFunc( 5, kTeclaF6, &Outputs_Change_State, eF06, ON, OFF, 200);
//
//  SetCallbackFunc( 6, kTeclaF7, &Outputs_Change_State, eF07, ON, OFF, 200);
//  SetCallbackFunc( 7, kTeclaF8, &Outputs_Change_State, eF08, ON, OFF, 200);
//  SetCallbackFunc( 8, kTeclaF9, &Outputs_Change_State, eF09, ON, OFF, 200);
//
//  SetCallbackFunc( 9, kTeclaFA, &Outputs_Change_State, eF10, ON, OFF, 200);
//  SetCallbackFunc(10, kTeclaFB, &Outputs_Change_State, eF11, ON, OFF, 200);
//  SetCallbackFunc(11, kTeclaFC, &Outputs_Change_State, eF12, ON, OFF, 200);
//
//  SetCallbackFunc(12, kTeclaFD, &Outputs_Change_State, eF13, ON, OFF, 200);
//  SetCallbackFunc(13, kTeclaFE, &Outputs_Change_State, eF14, ON, OFF, 200);
//  SetCallbackFunc(14, kTeclaFF, &Outputs_Change_State, eF15, ON, OFF, 200);
//  SetCallbackFunc(15, kTeclaFG, &Outputs_Change_State, eF16, ON, OFF, 200);
}

volatile uint8_t Time;

void Processo(uint16_t nRF905Key)
{

  uint8_t i;
  //char debug[20];

  if(nRF905Key != 0)
    {
      for(i = 0; i < kProcesscommands; i++)
	{
	  if(processVector[i].nRFKey == nRF905Key)
	    {
	      (*processVector[i].Function)(processVector[i].out_name, processVector[i].stateSet);
	      processVector[i].TimeCout  = (processVector[i].TimeOut /  kProcessInterval);
	    }
	  else
	    {
	      (*processVector[i].Function)(processVector[i].out_name, processVector[i].stateClear);
	    }
	}
    }
  else
    {
      for(i = 0; i < kProcesscommands; i++)
	{
	  if(processVector[i].TimeCout > 0)
	    {
	      processVector[i].TimeCout--;
	    }
	  else
	    {
	      (*processVector[i].Function)(processVector[i].out_name, processVector[i].stateClear);
	    }
	}
    }
  nRF905Key = 0;
}





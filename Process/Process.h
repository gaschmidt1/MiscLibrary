/****************************************************************************
 * Copyright (C) 2019 by gaschmidt                                  		*
 *                                                                          *
 * This file is part of P1176 ComLink product.                              *
 *																			*
 ****************************************************************************/

/**
 * @file Process.h
 * @author My Self
 * @date 9 Sep 2012
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <cmsis_os.h>
#include <Outputs.h>
#include <sys/_stdint.h>

/**
 * @brief Used to status control off the engine.
 *
 */


#define kProcessInterval 20U
#define kProcesscommands 12U



#define kTeclaF1                0x0800
#define kTeclaF2                0x0080
#define kTeclaF3                0x0008

#define kTeclaF4                0x0400
#define kTeclaF5                0x0040
#define kTeclaF6                0x0004

#define kTeclaF7                0x0200
#define kTeclaF8                0x0020
#define kTeclaF9                0x0002

#define kTeclaFA                0x0100
#define kTeclaFB                0x0010
#define kTeclaFC                0x0001

#define kTeclaFD                0x0011
#define kTeclaFE                0x0012
#define kTeclaFF                0x0014
#define kTeclaFG                0x0018


typedef struct
{
  uint8_t TimeOut;
  uint8_t TimeCout;
  uint16_t nRFKey;
  App_Outputs out_name;
  output_state stateSet;
  output_state stateClear;
  void (*Function)(App_Outputs, output_state);
}ProcessStruct;

/**
 * @brief To start Variables status the machine.
 * @param void.
 * @retval void.
 */
void ProcessInit(void);

/**
 * @brief To receive the remote control and operate the engine and machine controls.
 * @param void.
 * @retval void.
 */
void Processo(uint16_t nRF905Key);

volatile ProcessStruct processVector[kProcesscommands];

void SetCallbackFunc(uint8_t Index, uint16_t nRfKey, void *Function, App_Outputs out_name, output_state stateSet, output_state stateClear, uint8_t TimeOut);




#endif /* PROCESS_H_ */



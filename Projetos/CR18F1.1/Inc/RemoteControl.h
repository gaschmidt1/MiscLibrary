/*
 * RemoteControl.h
 *
 *  Created on: Aug 27, 2019
 *      Author: gerry
 */

#ifndef SRC_REMOTECONTROL_H_
#define SRC_REMOTECONTROL_H_

#include "main.h"
#include "NRF905.h"
#include "MyFlash.h"
#include "Inputs.h"

#define kRemoteControlInterval 20U
#define kRemoteControlCommands 18U

/* */
 #define kRemoteControlTxAdress (kFlashStartDataAddress)
/* */
 #define kRemoteControlRxAdress (kFlashStartDataAddress + 4)
/* */
#define IsInputsInConfigMode() (InputsGetState (In07))//InputsGetState (In01) &&
/* */
#define nRfAddressConfig     65535//0x0000FFFF
/* */
#define nRfAddressRxOffset 0x00008000

/* Keyboard Coding */

#define kSw01 (uint32_t)(1<< 0)
#define kSw02 (uint32_t)(1<< 1)
#define kSw03 (uint32_t)(1<< 2)
#define kSw04 (uint32_t)(1<< 3)
#define kSw05 (uint32_t)(1<< 4)
#define kSw06 (uint32_t)(1<< 5)

#define kSw07 (uint32_t)(1<< 6)
#define kSw08 (uint32_t)(1<< 7)
#define kSw09 (uint32_t)(1<< 8)
#define kSw10 (uint32_t)(1<< 9)
#define kSw11 (uint32_t)(1<< 10)
#define kSw12 (uint32_t)(1<< 11)

#define kSw13 (uint32_t)(1<< 12)
#define kSw14 (uint32_t)(1<< 13)
#define kSw15 (uint32_t)(1<< 14)
#define kSw16 (uint32_t)(1<< 15)
#define kSw17 (uint32_t)(1<< 16)
#define kSw18 (uint32_t)(1<< 17)

#define kSwProg (uint32_t)(kSw01 | kSw03)

typedef struct
{
	InputNameType Input;
	uint32_t KeyValue;
}RemoteControlConfig_t;

RemoteControlConfig_t RemoteControlVector[kRemoteControlCommands] ;

void RemoteControlInit(void);
void RemoteControlConfigCallback(uint8_t Index, InputNameType Input, uint32_t KeyValue);
void RemoteControlConfigProcessRF(void);
void RemoteControlPeriodic(InputNameType Input);

#endif /* SRC_REMOTECONTROL_H_ */


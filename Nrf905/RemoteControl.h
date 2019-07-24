/*
 * RemoteControl.h
 *
 *  Created on: 4 de jun de 2019
 *      Author: gerry
 */

#ifndef INC_REMOTECONTROL_H_
#define INC_REMOTECONTROL_H_

#include "spi.h"
#include "nRf905.h"
#include "fifo.h"
#include "main.h"

#define nRf905AddressConfig 65535U
#define nRf905TimeToConnect 5000U
#define nRf905TxBufferlenght 4u
#define nRf905RxBufferlenght 4u

fifo_t RemoteControlQueue;

void RemoteControlInit(void);
void RemoteControlPeriodic(void);
void RemoteControlConfigAddress(void);

#endif /* INC_REMOTECONTROL_H_ */


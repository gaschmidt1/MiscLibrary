/*
 * Process.h
 *
 *  Created on: 16 de abr de 2019
 *      Author: gerry
 */

#ifndef SRC_PROCESS_H_
#define SRC_PROCESS_H_

#include "main.h"

void RS485Periodic(void);
void ProcessInit(void);
void ConvertAnSendOverCAN(void);
void StkPeriodic(void);
void StartConversion(void);

#endif /* SRC_PROCESS_H_ */

/* 
 * File:   Rs485.h
 * Author: gerry
 *
 * Created on May 23, 2019, 11:55 AM
 */

#ifndef RS485_H
#define	RS485_H

#ifdef	__cplusplus
extern "C"
{
#endif
  
/*******************************************************************************
 * Include Files
 */  
#include "mcc_generated_files/mcc.h"
#include "pic18.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
  
  /*******************************************************************************
 * Functions
 */
void PutsRS485(char* s ); 
uint8_t GetsRS485(uint8_t *RxData);


#ifdef	__cplusplus
}
#endif

#endif	/* RS485_H */


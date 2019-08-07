/* 
 * File:   Application.h
 * Author: gerry
 *
 * Created on May 23, 2019, 12:56 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "mcc_generated_files/mcc.h"
#include "Rs485.h" 
#include "Queue.h"

/*******************************************************************************
 * Exported prototypes
 */
 
void ProcessInit(void);
void ProcessPeriodic(void);



#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */


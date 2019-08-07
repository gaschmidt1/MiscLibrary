/*
 * J1939.c
 *
 *  Created on: 7 de jul de 2016
 *      Author: giovani
 */
#include "J1939.h"
#include "J1939_DL.h"
#include "J1939_AL.h"
#include "J1939_TL.h"
#include "J1939_NML.h"
//========================================================================================
//protocol stack Interface Functions
//========================================================================================

J1939_STRUCTURE J1939;
//static J1939_TX_MESSAGE_T TxJ1939msg;
//static J1939_RX_MESSAGE_T RxJ1939msg;

void J1939_stk_init(void)//Stack Initialization function
{
	J1939.Addr_Status = ADDR_CLAIMED;
	J1939.General_status = ONLINE;


	DL_init();
	//TL_init();
	NML_init();
	AL_init();
}
void J1939_stk_periodic(void)//Stack cycle handler
{
	DL_periodic();
	//TL_periodic();
	NML_Periodic();
}


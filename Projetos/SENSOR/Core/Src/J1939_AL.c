/*
 * J1939_AL.c
 *
 *  Created on: 7 de jul de 2016
 *      Author: giovani
 */
#include <stdint.h>
#include "J1939.h"
#include "J1939_AL.h"
#include "J1939_NML.h"
#include "J1939_FRAMES.h"



//PGN

const PGN_T _pgn_table[PGN_NUM] =
    {
	59904,			//	Request PGN
	60928, 			// 	ADDR_CLAIM
    };

FAULT_CODE_T FaultCode;

J1939_TX_MESSAGE_T J1939msg;



U08 ADDR_RQST = 0;


//========================================================================================
//Application Interface Functions
//========================================================================================
/****************************************************************************************
@function          	: void Rev_J1939msg(J1939_RX_MESSAGE_T *msg_ptr)
@parameters       	: None
@return            	: J1939_RX_MESSAGE_T *msg_ptr
@Description       	: Packet processing functions , according to the actual need to write
 *****************************************************************************************/
void Rev_J1939msg(J1939_RX_MESSAGE_T *msg_ptr)
{
  J1939_ProtocolRun(msg_ptr->PGN, msg_ptr->data,msg_ptr->dest_addr, msg_ptr->source_addr);
}

/****************************************************************************************
@function           : void AL_init(void)
@Parâmetros         : none
@return             : none
@Descrption         : Initialization function
 *****************************************************************************************/
void AL_init(void)
{
  U08 i;

  FaultCode.count = 0;
  for(i=0;i<J1939_FAULT_NUM;i++)
    {
      FaultCode.fault_code[i].spn = 0;
      FaultCode.fault_code[i].fmi = 0;
      FaultCode.fault_code[i].oc = 0;
    }
}

/****************************************************************************************
@function           : U08 PGN_filter(PGN_T pgn);
@parameters        	: PGN_T pgn need lookup table PGN
@return             : Back 1 succeeds , returns 0 no such PGN
@Description        : Packet filtering function
 *****************************************************************************************/
U08 PGN_filter(PGN_T pgn)
{
  U08 left = 0;
  U08 right = PGN_NUM - 1;
  U08 middle = 0;

  while(left<=right)
    {
      middle = (U08)((left + right) >> 1);
      if(pgn==_pgn_table[middle])
	{
	  return TRUE;
	}

      if(pgn>_pgn_table[middle])
	{
	  left = middle + 1;
	}
      else
	{
	  right = middle - 1;
	}
    }
  return FALSE;
}


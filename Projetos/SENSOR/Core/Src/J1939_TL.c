/*
 * J1939_TL.c
 *
 *  Created on: 7 de jul de 2016
 *      Author: giovani
 */


#include "J1939.h"
#include "J1939_TL.h"
#include "J1939_DL.h"
#include "J1939_AL.h"

static J1939_RX_MESSAGE_T J1939MPMessage;            //Multiple-packet transmission buffer
static RECEIVE_STATU_MACHINE_T ReceiveStatuMachine;  //BAM STATE MACHINE
static J1939_PDU_T J1939PDU;                         //PDU RECEIVED PACKETS

/****************************************************************************************
@function           : void J1939_TL_init( void )
@Parameter           : None
@Return              : None
@Description         : At system startup called to set all state machines to a known state
 *****************************************************************************************/
void TL_init( void )
{
  U08 i;

  J1939MPMessage.PGN = 0;
  J1939MPMessage.dest_addr = 0;
  J1939MPMessage.source_addr = 0;
  J1939MPMessage.byte_count = 0;

  J1939PDU.PGN = 0;
  J1939PDU.dest_addr = 0;
  J1939PDU.source_addr = 0;
  J1939PDU.byte_count = 0;

  ReceiveStatuMachine.PGN = 0;
  ReceiveStatuMachine.dest_addr = 0;
  ReceiveStatuMachine.source_addr = 0;
  ReceiveStatuMachine.packet_number = 0;
  ReceiveStatuMachine.timer_counter = 0;
  ReceiveStatuMachine.total_packet_number = 0;
  ReceiveStatuMachine.byte_count = 0;
  ReceiveStatuMachine.status = WAIT_FOR_MESSAGE;
  ReceiveStatuMachine.TP = TP_NONE;


  for(i=0;i<NUMBER_TRANS_RX_BUFFERS;i++)
    {
      J1939MPMessage.data[i] = 0;
    }

  for(i=0;i<NUMBER_PDU_BUFFERS;i++)
    {
      J1939PDU.data[i] = 0;
    }

  //TimerCounter = 0;       //The counter is cleared
}

/****************************************************************************************
@function           : U08 Trans_J1939msg(J1939_TX_MESSAGE_T *msg_ptr)
@Parameter           : None
@Return               : None
@Description          :  J1939 message sent by the protocol stack function
 *****************************************************************************************/
U08 Trans_J1939msg(J1939_TX_MESSAGE_T *msg_ptr)
{
  if(msg_ptr->byte_count>8)
    {

      //	/ * Use multi-function transport protocol packet * /
    }
  else
    {
      Build_CANpkt(msg_ptr,0);
    }
  return TRUE;
}

/****************************************************************************************
@function             : void TL_process (J1939_RX_MESSAGE_T *msg_ptr)
@Parameter            : None
@Return               : None
@Description          : Transport Layer Interface Functions
 *****************************************************************************************/
void TL_process(J1939_PDU_T *pdu_ptr)
{
  U08 i;
  J1939_RX_MESSAGE_T msg;

  if((pdu_ptr->PGN==TP_CM)||(pdu_ptr->PGN==TP_DT))
    {
      J1939PDU.PGN = pdu_ptr->PGN;
      J1939PDU.dest_addr = pdu_ptr->dest_addr;
      J1939PDU.source_addr = pdu_ptr->source_addr;
      J1939PDU.byte_count = pdu_ptr->byte_count;

      for(i=0;i<NUMBER_PDU_BUFFERS;i++)
	{
	  J1939PDU.data[i] = pdu_ptr->data[i];
	}
    }
  else
    {
      msg.PGN = pdu_ptr->PGN;
      //J1939.rxJ1939->PGN = pdu_ptr->PGN;
      //J1939.rxJ1939->dest_addr = pdu_ptr->dest_addr;
      // J1939.rxJ1939->source_addr = pdu_ptr->source_addr;
      //J1939.rxJ1939->byte_count = pdu_ptr->byte_count;
      msg.dest_addr = pdu_ptr->dest_addr;
      msg.source_addr = pdu_ptr->source_addr;
      msg.byte_count = pdu_ptr->byte_count;

      for(i=0;i<NUMBER_TRANS_RX_BUFFERS;i++)
	{
	  // 	J1939.rxJ1939->data[i] = pdu_ptr->data[i];
	  msg.data[i] = pdu_ptr->data[i];
	}
      Rev_J1939msg(&msg);
    }

  return;
}

/****************************************************************************************
@function          : void TL_periodic ( void )
@Parameter            : None
@Return              : None
@Description         :Transport Layer periodic function , processing and transmission protocol state machine function
 *****************************************************************************************/
void TL_periodic(void)
{
  //	U08 i;
  //	U08 go_on;
  //
  //	go_on = TRUE;
  //	ReceiveStatuMachine.timer_counter++;    //TimerCounter++;     //Counter is incremented
  //	// TimerCounter++;//test
  //	while(go_on)
  //	{
  //		switch (ReceiveStatuMachine.status)
  //		{
  //		case  WAIT_FOR_MESSAGE:
  //		{
  //			if(J1939PDU.PGN==TP_CM&&J1939PDU.dest_addr==GLOBADDR||J1939PDU.dest_addr==NODEADDR)
  //			{
  //				if(J1939PDU.data[0]==TP_CM_RTS)
  //				{
  //					ReceiveStatuMachine.PGN = J1939PDU.data[6];
  //					ReceiveStatuMachine.PGN <<= 8;
  //					ReceiveStatuMachine.PGN += J1939PDU.data[5];
  //					ReceiveStatuMachine.dest_addr = J1939PDU.dest_addr;
  //					ReceiveStatuMachine.source_addr = J1939PDU.source_addr;
  //					ReceiveStatuMachine.packet_number = 0;
  //					ReceiveStatuMachine.timer_counter = 0;
  //					ReceiveStatuMachine.total_packet_number = J1939PDU.data[3];
  //					ReceiveStatuMachine.byte_count = J1939PDU.data[2];
  //					ReceiveStatuMachine.byte_count <<= 8;
  //					ReceiveStatuMachine.byte_count += J1939PDU.data[1];
  //					ReceiveStatuMachine.status = INIT_REASSEMBLE_STRUCTURE;
  //					ReceiveStatuMachine.TP = TP_CM_RTS;
  //				}
  //				else if(J1939PDU.data[0]==TP_CM_BAM)
  //				{
  //					ReceiveStatuMachine.PGN = J1939PDU.data[6];
  //					ReceiveStatuMachine.PGN <<= 8;
  //					ReceiveStatuMachine.PGN += J1939PDU.data[5];
  //					ReceiveStatuMachine.dest_addr = J1939PDU.dest_addr;
  //					ReceiveStatuMachine.source_addr = J1939PDU.source_addr;
  //					ReceiveStatuMachine.packet_number = 0;
  //					ReceiveStatuMachine.timer_counter = 0;
  //					ReceiveStatuMachine.total_packet_number = J1939PDU.data[3];
  //					ReceiveStatuMachine.byte_count = J1939PDU.data[2];
  //					ReceiveStatuMachine.byte_count <<= 8;
  //					ReceiveStatuMachine.byte_count += J1939PDU.data[1];
  //					ReceiveStatuMachine.status = INIT_REASSEMBLE_STRUCTURE;
  //					ReceiveStatuMachine.TP = TP_CM_BAM;
  //				}
  //				else
  //				{
  //					go_on = FALSE;//break;
  //				}
  //			}
  //			else
  //			{
  //				go_on = FALSE;//break;
  //			}
  //			break;
  //		}
  //
  //		case INIT_REASSEMBLE_STRUCTURE:                     //INIT_REASSEMBLE_STRUCTURE和CHECK_PACKET
  //		{                                                                   //Synthesis of a state
  //			if(ReceiveStatuMachine.TP==TP_CM_RTS)           //Long connection-oriented message transmission request
  //			{
  //			}
  //			else if(ReceiveStatuMachine.TP==TP_CM_BAM)      //Request for BAM unconnected
  //					{
  //				if(ReceiveStatuMachine.byte_count<NUMBER_TRANS_RX_BUFFERS) //Determine whether the buffer is exceeded
  //						{
  //					J1939MPMessage.PGN = ReceiveStatuMachine.PGN;
  //					J1939MPMessage.dest_addr = ReceiveStatuMachine.dest_addr;
  //					J1939MPMessage.source_addr = ReceiveStatuMachine.source_addr;
  //					J1939MPMessage.byte_count = ReceiveStatuMachine.byte_count;
  //
  //					for(i=0;i<NUMBER_TRANS_RX_BUFFERS;i++)
  //					{
  //						J1939MPMessage.data[i] = 0;
  //					}
  //					ReceiveStatuMachine.status = WAIT_FOR_DATA;
  //						}
  //				else
  //				{
  //					ReceiveStatuMachine.status= WAIT_FOR_MESSAGE;
  //					ReceiveStatuMachine.timer_counter = 0;
  //					go_on = FALSE;
  //					//break;
  //				}
  //					}
  //			else
  //			{
  //				ReceiveStatuMachine.status = WAIT_FOR_MESSAGE;
  //				ReceiveStatuMachine.timer_counter = 0;
  //				go_on = FALSE;
  //				//break;
  //			}
  //			break;
  //		}
  //
  //		case CHECK_PACKET:
  //		{
  //			break;
  //		}
  //
  //		case SEND_ABORT:
  //		{
  //			break;
  //		}
  //
  //		case SEND_CTS_WITH_COUNT:
  //		{
  //			break;
  //		}
  //
  //		case WAIT_FOR_DATA:
  //		{
  //			//printp("mn=%d",J1939PDU.data[0]);//test
  //			if(J1939PDU.PGN==TP_DT)
  //			{
  //				ReceiveStatuMachine.status = CHECK_DATA_PACKET;
  //				// printp("mn=%d",J1939PDU.data[0]);//test
  //				//break;
  //			}
  //			else
  //			{
  //				ReceiveStatuMachine.status = CHECK_TIMER;
  //				//break;
  //			}
  //			break;
  //		}
  //
  //		case CHECK_TIMER:
  //		{
  //			if(ReceiveStatuMachine.timer_counter>(750/TICK))    //750ms timeout
  //			{
  //				ReceiveStatuMachine.status = RESET_REASSEMBLY_STRUCTURE;
  //				//ReceiveStatuMachine.timer_counter = 0;
  //				//break;
  //			}
  //			else
  //			{
  //				ReceiveStatuMachine.status = WAIT_FOR_DATA;
  //				go_on = FALSE;//break;
  //			}
  //			break;
  //		}
  //
  //		case RESET_REASSEMBLY_STRUCTURE:
  //		{
  //			ReceiveStatuMachine.PGN = 0;
  //			ReceiveStatuMachine.dest_addr = 0;
  //			ReceiveStatuMachine.source_addr = 0;
  //			ReceiveStatuMachine.packet_number = 0;
  //			ReceiveStatuMachine.timer_counter = 0;
  //			ReceiveStatuMachine.total_packet_number = 0;
  //			ReceiveStatuMachine.byte_count = 0;
  //			J1939MPMessage.PGN = 0;
  //			J1939MPMessage.dest_addr = 0;
  //			J1939MPMessage.source_addr = 0;
  //			J1939MPMessage.byte_count = 0;
  //			for(i=0;i<NUMBER_TRANS_RX_BUFFERS;i++)
  //			{
  //				J1939MPMessage.data[i] = 0;
  //			}
  //			ReceiveStatuMachine.status = WAIT_FOR_MESSAGE;
  //			go_on = FALSE;
  //			break;
  //		}
  //
  //		case CHECK_DATA_PACKET:
  //		{
  //			if(ReceiveStatuMachine.TP==TP_CM_BAM)           //Oriented BAM unconnected
  //					{
  //				if(J1939PDU.source_addr==ReceiveStatuMachine.source_addr&&
  //						J1939PDU.dest_addr==ReceiveStatuMachine.dest_addr)
  //				{
  //					//printp("mn=%d",J1939PDU.data[0]);//test
  //					if(ReceiveStatuMachine.packet_number==J1939PDU.data[0]-1)
  //					{
  //						ReceiveStatuMachine.status = SAVE_DATA;
  //						ReceiveStatuMachine.timer_counter = 0;
  //						J1939PDU.data[0] = 0;
  //					}
  //					else if(J1939PDU.data[0]!=0)
  //					{
  //						ReceiveStatuMachine.status = RESET_REASSEMBLY_STRUCTURE;     //Wrong wrong packet number
  //					}
  //					else
  //					{
  //						ReceiveStatuMachine.status = WAIT_FOR_DATA;
  //						go_on = FALSE;
  //					}
  //				}
  //				else
  //				{
  //					ReceiveStatuMachine.status = WAIT_FOR_DATA;
  //					go_on = FALSE;
  //				}
  //					}
  //			else if(ReceiveStatuMachine.TP==TP_CM_RTS)  //Long connection-oriented packet transport
  //			{}
  //			else
  //			{}
  //			break;
  //		}
  //
  //		case SAVE_DATA:
  //		{
  //			i=0;
  //
  //			while((i<7)&&((ReceiveStatuMachine.packet_number*7+i)<=ReceiveStatuMachine.byte_count))
  //			{
  //				J1939MPMessage.data[ReceiveStatuMachine.packet_number*7+i] = J1939PDU.data[i+1];
  //				J1939PDU.data[i+1] = 0;
  //				i++;
  //			}
  //			ReceiveStatuMachine.packet_number++;
  //
  //			if(ReceiveStatuMachine.packet_number==ReceiveStatuMachine.total_packet_number)
  //			{
  //				ReceiveStatuMachine.status = FILL_USER_MESSAGE;
  //			}
  //			else
  //			{
  //				ReceiveStatuMachine.status = WAIT_FOR_DATA;
  //				go_on = FALSE;
  //			}
  //			break;
  //		}
  //
  //		case SEND_EOM:
  //		{
  //		}
  //
  //		case SEND_CTS:
  //		{
  //		}
  //
  //		case FILL_USER_MESSAGE:
  //		{
  //			ReceiveStatuMachine.status = RESET_REASSEMBLY_STRUCTURE;
  //			ReceiveStatuMachine.timer_counter = 0;
  //			// NML_process(&J1939MPMessage);					//Processing message
  //
  //			//go_on = FALSE;
  //			break;
  //		}
  //
  //
  //		default:
  //		{
  //			go_on = FALSE;
  //			break;
  //		}
  //
  //		}//end switch
  //	}//end while
}

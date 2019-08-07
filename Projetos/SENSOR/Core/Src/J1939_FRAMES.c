/*
 * J1939_FRAMES.c
 *
 *  Created on: 18 de jul de 2016
 *      Author: Giovani
 */


#include "J1939_FRAMES.h"
#include "J1939.h"
#include "J1939_AL.h"
#include "J1939_DL.h"
#include "J1939_NML.h"


extern Network_data Net;


J1939_Protocol_Frames_t J1939_Protocol_Frames[J1939_PROTOCOL_MAX_COMMANDS];

static uint8_t CurrentNumberOfCommands = 0;
uint8_t teste = 0;
uint8_t AppData[2];
uint64_t Name_rcvd = 0;
U16 PGN_RQST = 0;

void SendData_A_Callback(uint8_t* Data, uint16_t PGN, uint8_t Dest,uint8_t Source)  // CALLED WHEN A DATA IS REQUESTED BY THE PGN 59904
{
  J1939_TX_MESSAGE_T J1939msg;
  PGN_RQST = Data[1];
  PGN_RQST = (PGN_RQST<<8) + Data[2];

  switch(PGN_RQST)
  {
    case 65164:
      if(J1939.Addr_Status == ADDR_CLAIMED)
	{
	  //			App_GetVals(DataToSend);
	  J1939msg.PGN = PGN_RQST;
	  J1939msg.byte_count = 8;
	  J1939msg.priority = 7;
	  J1939msg.source_addr = Net.Address;
	  J1939msg.data[0] = 0xFF;
	  J1939msg.data[1] = 0xFF;
	  J1939msg.data[2] = 0xFF;
	  J1939msg.data[3] = 0xFF;
	  J1939msg.data[4] = 0xFF;
	  J1939msg.data[5] = 0xFF;
	  J1939msg.data[6] = 0xFF;
	  J1939msg.data[7] = 0xFF;
	  Build_CANpkt(&J1939msg,0);
	}
      break;

    case 60928:
      J1939msg.PGN = PGN_RQST;
      J1939msg.byte_count = 8;
      J1939msg.priority = 7;
      J1939msg.source_addr = Net.Address;
      J1939msg.data[0] = Net.Name[0];
      J1939msg.data[1] = Net.Name[1];
      J1939msg.data[2] = Net.Name[2];
      J1939msg.data[3] = Net.Name[3];
      J1939msg.data[4] = Net.Name[4];
      J1939msg.data[5] = Net.Name[5];
      J1939msg.data[6] = Net.Name[6];
      J1939msg.data[7] = Net.Name[7];
      J1939msg.dest_addr = GLOBADDR;
      Build_CANpkt(&J1939msg,0);
      break;
  }

}

void SendPeriodicData(uint8_t* Data, uint16_t PGN, uint8_t Dest ,uint8_t Source)
{
  J1939_TX_MESSAGE_T J1939msg;

  if(J1939.Addr_Status == ADDR_CLAIMED)
    {
      J1939msg.PGN = PGN;
      J1939msg.byte_count = 8;
      J1939msg.priority = 7;
      J1939msg.source_addr = Net.Address;
      J1939msg.data[0] = Data[0];
      J1939msg.data[1] = 0xFF;
      J1939msg.data[2] = 0xFF;
      J1939msg.data[3] = 0xFF;
      J1939msg.data[4] = 0xFF;
      J1939msg.data[5] = 0xFF;
      J1939msg.data[6] = 0xFF;
      J1939msg.data[7] = Data[1];
      Build_CANpkt(&J1939msg,0);
    }

}

void SendTeste(uint8_t* Data, uint16_t PGN, uint8_t Dest ,uint8_t Source)
{
  J1939_TX_MESSAGE_T J1939msg;

  if(J1939.Addr_Status == ADDR_CLAIMED)
    {
      J1939msg.PGN = PGN;
      J1939msg.byte_count = 8;
      J1939msg.priority = 7;
      J1939msg.source_addr = Net.Address;
      J1939msg.data[0] = Data[0];
      J1939msg.data[1] = 0xFF;
      J1939msg.data[2] = 0xFF;
      J1939msg.data[3] = 0xFF;
      J1939msg.data[4] = 0xFF;
      J1939msg.data[5] = 0xFF;
      J1939msg.data[6] = 0xFF;
      J1939msg.data[7] = Data[1];
      Build_CANpkt(&J1939msg,0);
    }
}



void CompareName_B_Callback (uint8_t* Data, uint16_t PGN, uint8_t Dest ,uint8_t Source)
{
  J1939_TX_MESSAGE_T J1939msg;
  int8_t i;

  if(Source == Net.Address)  // Only process incoming NAME if the claimed address is on my own
    {
      Name_rcvd = 0;
      for(i = 7; i>=0 ; i--)
	{
	  Name_rcvd += Data[i];
	  if(i>0)
	    {
	      Name_rcvd <<= 8;
	    }
	}

      if(Name_rcvd>Net.Name_Cpt)     //ADDRESS CAN BE CLAIMED
	{
	  J1939.Addr_Status = ADDR_CLAIMED;

	}
      else if (Name_rcvd<Net.Name_Cpt) // ADDRESS CANNOT BE CLAIMED
	{
	  J1939.Addr_Status = ADDR_CANNOT_CLAIM;
	  Net.Address = NULLADDR;
	}
      J1939msg.dest_addr = GLOBADDR;
      J1939msg.PGN = PGN;
      J1939msg.byte_count = 8;
      J1939msg.priority = 6;
      J1939msg.source_addr = Net.Address;
      J1939msg.data[0] = Net.Name[0];
      J1939msg.data[1] = Net.Name[1];
      J1939msg.data[2] = Net.Name[2];
      J1939msg.data[3] = Net.Name[3];
      J1939msg.data[4] = Net.Name[4];
      J1939msg.data[5] = Net.Name[5];
      J1939msg.data[6] = Net.Name[6];
      J1939msg.data[7] = Net.Name[7];
      Build_CANpkt(&J1939msg,0);
    }

}



/*=========================================================================================================================
 * ========================================================================================================================
 * ========================================================================================================================
 ===========================================================================================================================*/

uint8_t J1939_AddProtocolFrames(uint16_t Command, J1939_Protocol_Callback_t FunctionToCallback)
{
  if(CurrentNumberOfCommands <  J1939_PROTOCOL_MAX_COMMANDS)
    {
      J1939_Protocol_Frames[CurrentNumberOfCommands].CommandToCall = Command;
      J1939_Protocol_Frames[CurrentNumberOfCommands].FuntionCallback = FunctionToCallback;
      CurrentNumberOfCommands++;
      return (1);
    }
  return 0;
}

void J1939_ProtocolInit(void)
{
  J1939_AddProtocolFrames(59904,SendData_A_Callback);
  J1939_AddProtocolFrames(60928,CompareName_B_Callback);
  J1939_AddProtocolFrames(65164,SendPeriodicData);
  //J1939_AddProtocolFrames(64991,SendTeste);

}

void J1939_ProtocolRun(uint16_t Command, uint8_t *Data, uint8_t Dest, uint8_t Source)
{
  uint16_t frame_type;
  char i;
  frame_type = Command;

  for (i = 0; i < CurrentNumberOfCommands; i++)
    {
      if (frame_type == J1939_Protocol_Frames[i].CommandToCall)
	{
	  J1939_Protocol_Frames[i].FuntionCallback(Data, Command, Dest, Source);
	  break;
	}
    }

}

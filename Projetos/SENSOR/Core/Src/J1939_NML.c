/*
 * J1939_NML.c
 *
 *  Created on: 14 de jul de 2016
 *      Author: Giovani
 */

#include "J1939_NML.h"
#include "J1939.h"
#include "J1939_FRAMES.h"
#include "J1939_DL.h"
#include "gpio.h"


Network_data Net;
uint64_t NAME_COMPLETE = 0;
uint8_t claim_sent = 0;
uint16_t counter = 0;
void NML_init(void)
{
  int8_t i ;
  Net.Address = NODEADDR;
  Net.Name[0] = (uint8_t) IDENTITY_NUMBER;								//LEAST SIGNIFICANT BYTE OF IDENTITY NUMBER (8bits)
  Net.Name[1] = (uint8_t)(IDENTITY_NUMBER>>8);							//SECOND BYTE OF IDENTITY  (8 bits)
  Net.Name[2] = (uint8_t)(IDENTITY_NUMBER>>16)&(0x1F); 					// MOST SIGINIFICANT BYTE OF IDENTITY (5 bits)  TOTAL:21 bits
  Net.Name[2] = Net.Name[2] | (((uint8_t)MANUFACTURER_NUMBER<<4))<<1; 	//LEAST SIGNIFICANT BITS OF MANUFACTURER CODE (3bits)
  Net.Name[3] = (MANUFACTURER_NUMBER>>4);                   		// MOST SIGNIFICANT MANUFACTURER CODE BITS (8bits ) TOTAL:11 bits

  Net.Name[4] = (ECU_INSTANCE & 0x7)|((FUNCTION_INSTANCE & 0x1F)<<4);		//3 BITS FOR ECU INSTANCE and 5 BITS FOR FUNCTION INSTANCE
  Net.Name[5] = FUNCTION_NUMBER;											// FUNCTION NUMBER
  Net.Name[6] = RESERVED_BIT |((VEHICLE_SYS&0x7F)<<1);						// RESERVED BIT (1bit) or VEHICLE SYS( 7 bit)
  Net.Name[7] = (ARBITRARY_ADDRESS_CAPABLE<<7);
  Net.Name[7] = Net.Name[7] | ((INDUSTRY_GROUP &0x7)<<4);
  Net.Name[7] = Net.Name[7] | (VEHICLE_SYS_INST &0x0F);

  Net.Name_Cpt = 0;
  for(i = 7; i>=0 ; i--)
    {
      Net.Name_Cpt += Net.Name[i];
      if(i>0)
	{
	  Net.Name_Cpt <<= 8;
	}
    }
}


uint16_t NML_counter = 0;
void NML_Periodic(void)
{
  J1939_TX_MESSAGE_T J1939msg;

  switch(J1939.Addr_Status)
  {
    case CLAIMING_ADDR:
      if(!claim_sent)
	{
	  claim_sent = 1;
	  J1939msg.PGN = 60928;
	  J1939msg.byte_count = 8;
	  J1939msg.priority = 6;
	  J1939msg.dest_addr = GLOBADDR;
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
      else
	{
	  counter++;
	  if(counter>250)
	    {
	      J1939.Addr_Status = ADDR_CLAIMED;
	      //	GPIO_WritePin(LED1_PORT,LED1_PIN,OFF);
	      counter = 0;
	    }
	  else if((J1939.Addr_Status==ADDR_CANNOT_CLAIM))
	    {
	      counter = 0;
	    }
	  NML_counter++;
	  if(NML_counter > 30)
	    {
	      NML_counter = 0;
	      //	GPIO_TogglePin(LED1_PORT,LED1_PIN);
	    }

	}
      break;

    case ADDR_CANNOT_CLAIM:
      NML_counter++;
      if(NML_counter > 250)
	{
	  NML_counter = 0;
	  //	GPIO_WritePin(LED1_PORT,LED1_PIN,1);
	}

      break;

    case ADDR_CLAIMED:

      break;


    default:
      break;


  }

}


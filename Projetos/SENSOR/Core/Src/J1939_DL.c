/*
 * J1939_DL.c
 *
 *  Created on: 7 de jul de 2016
 *      Author: giovani
 */

#include "J1939.h"
#include "J1939_DL.h"
#include "can.h"
#include "J1939_TL.h"
#include "J1939_NML.h"


extern Network_data Net;
CAN_PACKET_T InBoundBuffer[IN_BUFFER_SIZE];

CAN_PACKET_T OutBoundBuffer[OUT_BUFFER_SIZE];

RING_T RingInBuffer;
RING_T RingOutBuffer;

U08 DL_state;



//==========================================================================================
//Datalink Modular Interfaces
//==========================================================================================
/****************************************************************************************
@Function           : void DL_init(void)
@Parameter          : None
@Return             : None
@Description        :Initialization function settings the datalink layer's packet buffers
                      And settings the datalink module into a "not primed" state

 *****************************************************************************************/
void DL_init(void)
{
  U08 i,j;

  for(i=0;i<IN_BUFFER_SIZE;i++)
    {
      InBoundBuffer[i].byte_count = 0;
      InBoundBuffer[i].identifier = 0;
      for(j=0;j<CAN_MAX_BYTE_COUNT;j++)
	{
	  InBoundBuffer[i].data[j] = 0;
	}
    }

  for(i=0;i<OUT_BUFFER_SIZE;i++)
    {
      OutBoundBuffer[i].byte_count = 0;
      OutBoundBuffer[i].identifier = 0;
      for(j=0;j<CAN_MAX_BYTE_COUNT;j++)
	{
	  OutBoundBuffer[i].data[j] = 0;
	}
    }

  RingInBuffer.buffer = &InBoundBuffer[0];
  RingInBuffer.head = 0;
  RingInBuffer.tail = 0;
  RingInBuffer.buffer_size = IN_BUFFER_SIZE - 1;

  RingOutBuffer.buffer = &OutBoundBuffer[0];
  RingOutBuffer.head = 0;
  RingOutBuffer.tail = 0;
  RingOutBuffer.buffer_size = OUT_BUFFER_SIZE - 1;

  //Set the link layer state machine
  DL_state = NOTPRIMED;

  return;
}

/****************************************************************************************
@Function          : void Rev_CANpkt( const CAN_PACKET_T* pkt_ptr )
@Parameter               : const CAN_PACKET_T* pkt_ptr
@Return            : None
@description            : Stack interface function between the data link layer and physical layer. The physical layer is called the receive interrupt function call
                      This function , when the function is called the CAN_PACKET_T mirror copy of the data link layer to the stack ring buffer
                      Red zone
 *****************************************************************************************/

//#pragma CODE_SEG NON_BANKED
void Rev_CANpkt(const CAN_PACKET_T *pkt_ptr)
{
  rng_enqueue(*pkt_ptr,&RingInBuffer);
  return;
}

/****************************************************************************************
@Function          : void J1939_DL_periodic(void)
@Parameter               :
@Return             :
@Description               : From J1939 week function, call TICK. Data link layer function drive internal processing
 *****************************************************************************************/

//#pragma CODE_SEG NON_BANKED
void DL_periodic(void)
{
  U08 m_DA,m_SA,m_PF,i;
  U32 m_ID;
  PGN_T m_PGN;
  CAN_PACKET_T *rpkt_ptr;
  CAN_PACKET_T *tpkt_ptr;
  J1939_PDU_T pdu;

  m_DA = 0;//initialization
  m_SA = 0;
  m_PF = 0;
  m_ID = 0;
  m_PGN = 0;

  i = 0;
  /*ringoutbuffer Dequeue packets*/
  tpkt_ptr = rng_dequeue(&RingOutBuffer);
  if(tpkt_ptr != NULL)
    {
      CAN_Transmit_IT1(tpkt_ptr);

    }


  /*Invoking transport- layer functions , message reception*/
  while(TRUE)
    {
      rpkt_ptr = rng_dequeue(&RingInBuffer);
      if(rpkt_ptr == NULL)                     //Receive buffer empty
	{
	  break;
	}
      else
	{
	  m_ID = rpkt_ptr->identifier;
	  m_SA = (U08)m_ID;    		// SOURCE ADDR
	  m_DA = (U08)(m_ID>>8); 		//
	  m_PGN = (uint16_t)(m_ID>>8);
	  m_PF = (U08)(m_ID>>16);     // PARAMETER FORMAT

	  if (m_PF < 240)                     //PDU1 format
	    {
	      if(m_DA==GLOBADDR)
		{
		  //continue;
		  pdu.PGN = m_PGN & 0xFF00;
		  pdu.byte_count = rpkt_ptr->byte_count;
		  pdu.dest_addr = GLOBADDR;
		  pdu.source_addr = m_SA;
		  for(i=0; i<pdu.byte_count; i++)
		    {
		      pdu.data[i] = rpkt_ptr->data[i];
		    }
		}
	      else if(m_DA==Net.Address)
		{
		  //continue;
		  pdu.PGN = m_PGN & 0xFF00;
		  pdu.byte_count = rpkt_ptr->byte_count;
		  pdu.dest_addr = m_DA;
		  pdu.source_addr = m_SA;
		  for(i=0;i<pdu.byte_count;i++)
		    {
		      pdu.data[i] = rpkt_ptr->data[i];
		    }
		}
	      else
		{
		  continue;
		}
	    }
	  else                                    //PDU2 format
	    {
	      pdu.PGN = m_PGN;
	      pdu.byte_count = rpkt_ptr->byte_count;
	      pdu.dest_addr = GLOBADDR;
	      pdu.source_addr = m_SA;
	      for(i=0;i<pdu.byte_count;i++)
		{
		  pdu.data[i] = rpkt_ptr->data[i];
		}
	    }
	}
      TL_process(&pdu);
    }
  return;
}

/****************************************************************************************
@Function           : const CAN_PACKET_T* Req_CANpkt(void)
@Parameter               : None
@Return             : const CAN_PACKET_T
@Description               :  Hardware abstraction layer in the transmission interrupt function calls this function to get a new data frame
 *****************************************************************************************/
const CAN_PACKET_T* Req_CANpkt(void)
{
  CAN_PACKET_T *pkt_ptr;
  pkt_ptr = rng_dequeue(&RingOutBuffer);
  if (pkt_ptr == NULL)
    {
      DL_state = NOTPRIMED;
      return NULL;
    }
  else
    {
      DL_state = PRIMED;
      return pkt_ptr;
    }
}

/****************************************************************************************
@Function          		: void Build_CANpkt(J1939_TX_MESSAGE_T *msg_ptr, U08 tflag)
@Parameter              : None
@Return             	: J1939_TX_MESSAGE_T *msg_ptr, U08 tflag
@Description            : This function is called the transport layer data link layer frame into the transmit buffer
 *****************************************************************************************/
void Build_CANpkt(J1939_TX_MESSAGE_T *msg_ptr,U08 tflag)
{
  CAN_PACKET_T pkt_ptr;
  U08 i;

  pkt_ptr.byte_count = (U08)msg_ptr->byte_count;
  pkt_ptr.identifier = msg_ptr->priority;
  pkt_ptr.identifier = (pkt_ptr.identifier<<18) + msg_ptr->PGN;
  if (msg_ptr->PGN < 0xF000)
    {
      pkt_ptr.identifier = pkt_ptr.identifier + msg_ptr->dest_addr;
    }
  pkt_ptr.identifier = (pkt_ptr.identifier<<8) + msg_ptr->source_addr;
  for(i=0;i<pkt_ptr.byte_count;i++)
    {
      pkt_ptr.data[i] = msg_ptr->data[i];
    }
  rng_enqueue(pkt_ptr,&RingOutBuffer);

  //Disable interrupts
  DL_state = PRIMED;
  //the opening break

  return;
}

/****************************************************************************************
@Function           : void rng_enqueue(CAN_PACKET_T msg, RING_T *ring)
@Parameter               : CAN_PACKET_T msg
                      RING_T *ring
@Return             :
@Description        :Function to CAN_PACKET_T msg added to the end point RING_T * ring structure
 *****************************************************************************************/

//#pragma CODE_SEG NON_BANKED
void rng_enqueue(CAN_PACKET_T msg, RING_T *ring)
{
  if(((ring->tail+1)==ring->head)||((ring->tail==ring->buffer_size)&&(ring->head==0)))//Circular queue is full
    {
      return;
    }
  else
    {
      ring->buffer[ring->tail] = msg;                         //enqueue CAN message
      ring->tail++;
      if(ring->tail > ring->buffer_size)                      //wrap,CAN_BUF_MAX ->0
	ring->tail = 0;
      return;
    }
}

/****************************************************************************************
@Function          : CAN_PACKET_T *rng_dequeue(RING_T *ring)
@Parameter               : RING_T *ring
@Return             :
@Description               : Remove the ring from a CAN_PACKET_T in the head , if it is empty or NULL
 *****************************************************************************************/

//#pragma CODE_SEG NON_BANKED
CAN_PACKET_T *rng_dequeue(RING_T *ring)
{
  CAN_PACKET_T *temp;

  if(ring->head == ring->tail)
    {
      return NULL;                                        //ring buffer is empty
    }
  else
    {
      temp = &ring->buffer[ring->head];
      ring->head++;
      if(ring->head > ring->buffer_size)
	ring->head = 0;                                 //wrap,CAN_BUF_MAX ->0
      return temp;
    }
}

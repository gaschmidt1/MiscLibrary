#ifndef _J1939_DL_H_
#define _J1939_DL_H_

#include "J1939.h"


//==========================================================================================
//Datalink Modular Interfaces
//==========================================================================================
void DL_init(void);//Initialization function , set buffer
void Rev_CANpkt(const CAN_PACKET_T* pkt_ptr);//Hardware abstraction layer calls the receive interrupt function call this function,,
const CAN_PACKET_T* Req_CANpkt(void);//Hardware abstraction layer calls the transmission interrupt function call this function,
void Build_CANpkt(J1939_TX_MESSAGE_T *msg_ptr, U08 tflag);//This function is called the transport layer data link layer frame into the transmit buffer
void DL_periodic(void);//Link layer periodic function

//========================================================================================
//Datalink Module Data Objects
//========================================================================================
void rng_enqueue(CAN_PACKET_T msg, RING_T *ring);//Function to CAN_PACKET_T msg added to the end point RING_T * ring structure
CAN_PACKET_T *rng_dequeue(RING_T *ring);//Remove the ring from a CAN_PACKET_T in the head , if it is empty or NULL

#endif

#ifndef _J1939_TL_H_
#define _J1939_TL_H_

//========================================================================================
//Transport Layer Functions
//========================================================================================										
void TL_init(void);//Transport Layer initialization
U08 Trans_J1939msg(J1939_TX_MESSAGE_T *msg_ptr);//Network layer and application layer calls this function , start sending a message J1939
void TL_periodic(void);// Transport Layer periodic function
void TL_process(J1939_PDU_T *msg_ptr);//Data link layer in dealing CAN packet call this function

#endif

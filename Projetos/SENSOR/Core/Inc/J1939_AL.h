#ifndef _J1939_AL_H_
#define _J1939_AL_H_



typedef struct
{
    U32 spn;
    U08 fmi;
    U08 oc;
}SERVICE_CODE_T;




typedef struct 
{
    SERVICE_CODE_T fault_code[J1939_FAULT_NUM];
    U08 count;    
}FAULT_CODE_T; 


//========================================================================================
//Application Interface Functions
//========================================================================================
void Rev_J1939msg(J1939_RX_MESSAGE_T *msg_ptr);//Processing the application layer packets
void AL_init(void);//Application layer initialization function
U08 PGN_filter(PGN_T pgn);//Packet filtering function

#endif 

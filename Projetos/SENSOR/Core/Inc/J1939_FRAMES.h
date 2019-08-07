/*
 * J1939_FRAMES.h
 *
 *  Created on: 18 de jul de 2016
 *      Author: Giovani
 */

#ifndef J1939_FRAMES_H_
#define J1939_FRAMES_H_
#include <stdint.h>

#define J1939_PROTOCOL_MAX_COMMANDS 10

typedef void (J1939_Protocol_Callback_t)(uint8_t*, uint16_t, uint8_t,uint8_t);
typedef struct{
	uint16_t CommandToCall;
	J1939_Protocol_Callback_t (*FuntionCallback);

}J1939_Protocol_Frames_t;


void SendData_A_Callback(uint8_t* Data, uint16_t PGN, uint8_t Dest , uint8_t Source);
void CompareName_B_Callback(uint8_t* Data, uint16_t PGN, uint8_t Dest,uint8_t Source);



extern J1939_Protocol_Frames_t J1939_Protocol_Frames[J1939_PROTOCOL_MAX_COMMANDS];

void J1939_ProtocolInit(void);
void J1939_ProtocolRun(uint16_t Command, uint8_t *Data, uint8_t Dest, uint8_t Source);

#endif /* J1939_FRAMES_H_ */

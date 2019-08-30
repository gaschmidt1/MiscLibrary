/*
 * CyBLE.h
 *
 *  Created on: 8 de fev de 2019
 *      Author: giovani
 */

#ifndef CYBLE_H_
#define CYBLE_H_
#include "cmsis_os.h"
#include "RingBuffer.h"
#include "Utilities.h"
osThreadId CyBLE_ProtocolThreadId;
osPoolId  CyBLE_DataPool_Id;

#define RING_BUFFER_SIZE 256

#define STX 0x02

#define ADDR_DEV 'a'

#define ADDR_BRO 'b'

#define ETX 0x03

#define NO_DATA_DELAY 100
#define READ_DATA_DELAY 1

void CyBLE_Init(void);

typedef enum
{
	START_FRAME= 0,
	CHECK_DEV_ADDR,
	CHECK_BRO_ADDR,
	CHECK_TYPE,
	GET_COMMAND,
	CHECKSUM,
	VERIFY_PARAMETER,
	RECEIVE_PARAMETERS,
	QUEUE_COMMAND,
	PROTOCOL_ERROR,
}CyBLE_Protocol_State_Typedef;

//typedef struct {
//
//  char buffer[RING_BUFFER_SIZE];
//
//  uint16_t tail_index;
//
//  uint16_t head_index;
//  uint8_t overwriten;
//}ring_buffer_typedef;

ring_buffer_typedef *CyBLE_RingBuffer;

//void CyBLE_Queue_Byte(uint8_t data_received);
//uint8_t CyBLE_Dequeue_Byte(void);
#endif /* CYBLE_H_ */

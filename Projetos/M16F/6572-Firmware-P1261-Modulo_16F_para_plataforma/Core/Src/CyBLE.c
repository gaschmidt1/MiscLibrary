/*
 * CyBLE.c
 *
 *  Created on: 8 de fev de 2019
 *      Author: giovani
 */



#include "Application_x.h"
#include "gpio.h"
#include "CyBLE.h"
#include "usart.h"
#include "NetCommands.h"

osPoolDef (CyBLE_DataPool, 1, ring_buffer_typedef);
void CyBLE_ProtocolTask(void const * argument);
void CyBLE_Receive_Byte(uint8_t rcvd_byte);
//static void RingBuffer_VerifyHead(void);
//static void RingBuffer_VerifyTail(void);
static uint8_t protocol_received_command = 0;
CyBLE_Protocol_State_Typedef Cyble_State_Machine;


uint8_t dummy_params[5] = {'A','B','C','D','E'};
static uint8_t received_parameters[40];
uint8_t parameteres_index = 0;
static uint8_t first_byte_checksum_rcvd = 0;

void CyBLE_Init(void)
{
  osThreadDef(CyBLE_ProtocolTask, CyBLE_ProtocolTask, osPriorityNormal, 0, 256);
  CyBLE_ProtocolThreadId = osThreadCreate(osThread(CyBLE_ProtocolTask), NULL);

  CyBLE_DataPool_Id = osPoolCreate (osPool(CyBLE_DataPool));
  CyBLE_RingBuffer = (ring_buffer_typedef *)osPoolCAlloc (CyBLE_DataPool_Id);

  CyBLE_RingBuffer->head_index = 0;
  CyBLE_RingBuffer->tail_index = 0;
  CyBLE_RingBuffer->buffer[0] = 0;
  CyBLE_RingBuffer->overwriten = 0;
  USART8_Register_RX_Callback(&CyBLE_Receive_Byte);
  Cyble_State_Machine = START_FRAME;
  MX_USART8_UART_Init();
  USART8_Start_Reception();
}


void CyBLE_Receive_Byte(uint8_t rcvd_byte)
{
  RingBuffer_Queue_Byte(CyBLE_RingBuffer,rcvd_byte);
}


void CyBLE_ProtocolTask(void const * argument)
{
  uint8_t checksum_received = 0;
  uint8_t checksum_calculated = 0;
  uint32_t task_delay = NO_DATA_DELAY;
  uint8_t byte_received = 0;
  for(;;)
    {
      byte_received = RingBuffer_Dequeue_Byte(CyBLE_RingBuffer);

      if(byte_received != 0)
	{
	  task_delay = READ_DATA_DELAY;

	  switch(Cyble_State_Machine)
	  {
	    case START_FRAME:
	      if(byte_received == STX)
		{
		  checksum_calculated = 0;
		  Cyble_State_Machine = CHECK_DEV_ADDR;
		}
	      break;

	    case CHECK_DEV_ADDR:
	      if(byte_received == ADDR_DEV)
		{
		  checksum_calculated ^= byte_received;
		  Cyble_State_Machine = CHECK_BRO_ADDR;
		}
	      else
		{
		  Cyble_State_Machine = PROTOCOL_ERROR;
		}
	      break;

	    case CHECK_BRO_ADDR:
	      if(byte_received == ADDR_BRO)
		{
		  checksum_calculated ^= byte_received;
		  Cyble_State_Machine = GET_COMMAND;
		}
	      else
		{
		  Cyble_State_Machine = PROTOCOL_ERROR;
		}
	      break;

	    case GET_COMMAND:
	      protocol_received_command = byte_received;
	      checksum_received = 0;
	      first_byte_checksum_rcvd = 0;
	      checksum_calculated ^= byte_received;
	      parameteres_index = 0;
	      Cyble_State_Machine = VERIFY_PARAMETER;

	      break;

	    case VERIFY_PARAMETER:
	      if(byte_received == '[')
		{
		  checksum_calculated ^= byte_received;
		  Cyble_State_Machine = RECEIVE_PARAMETERS;
		}
	      else // no parameter detected, catch first checksum byte and move to checksum stage
		{
		  first_byte_checksum_rcvd = 1;
		  checksum_received = (Hex_To_U8(byte_received)<<4);
		  Cyble_State_Machine = CHECKSUM;
		}
	      break;
	    case CHECKSUM:
	      if(!first_byte_checksum_rcvd)
		{
		  checksum_received = (Hex_To_U8(byte_received)<<4);
		  first_byte_checksum_rcvd= 1;
		}
	      else
		{
		  checksum_received |= Hex_To_U8(byte_received);
		  if(checksum_received == checksum_calculated)
		    {
		      Cyble_State_Machine = QUEUE_COMMAND;
		    }
		  else
		    {
		      Cyble_State_Machine = PROTOCOL_ERROR;
		    }
		}
	      break;

	    case RECEIVE_PARAMETERS:
	      checksum_calculated^=byte_received;
	      if(byte_received != ']')
		{
		  received_parameters[parameteres_index] = byte_received;
		  parameteres_index++;
		}
	      else
		{
		  Cyble_State_Machine = CHECKSUM;
		}
	      break;

	    case QUEUE_COMMAND:
	      if(byte_received == ETX)
		{
		  NetCommands_Execute(protocol_received_command,received_parameters,parameteres_index);
		  Cyble_State_Machine = START_FRAME;
		}
	      else
		{
		  Cyble_State_Machine = PROTOCOL_ERROR;
		}
	      break;
	    default:
	      break;
	  }
	}
      else
	{
	  task_delay = NO_DATA_DELAY;
	  Cyble_State_Machine = START_FRAME;
	}
      osDelay(task_delay);
    }
}

//
//void CyBLE_Queue_Byte(uint8_t data_received)
//{
//	if(CyBLE_RingBuffer->overwriten)
//	{
//		CyBLE_RingBuffer->tail_index++;
//		RingBuffer_VerifyTail();
//	}
//	CyBLE_RingBuffer->buffer[CyBLE_RingBuffer->head_index] = data_received;
//	CyBLE_RingBuffer->head_index++;
//	RingBuffer_VerifyHead();
//}
//
//uint8_t CyBLE_Dequeue_Byte(void)
//{
//	uint8_t return_byte;
//	if(CyBLE_RingBuffer->tail_index == CyBLE_RingBuffer->head_index)
//	{
//		return_byte =  0;
//	}
//	else
//	{
//		return_byte = CyBLE_RingBuffer->buffer[CyBLE_RingBuffer->tail_index];
//		CyBLE_RingBuffer->tail_index++;
//		RingBuffer_VerifyTail();
//
//	}
//	return return_byte;
//}
//
//static void RingBuffer_VerifyTail(void)
//{
//	if(CyBLE_RingBuffer->tail_index > (RING_BUFFER_SIZE - 1))
//	{
//		CyBLE_RingBuffer->tail_index = 0;
//		if(CyBLE_RingBuffer->tail_index == CyBLE_RingBuffer->head_index)
//		{
//			CyBLE_RingBuffer->buffer[CyBLE_RingBuffer->head_index] = 0;
//		}
//		else if((CyBLE_RingBuffer->tail_index < CyBLE_RingBuffer->head_index) && CyBLE_RingBuffer->overwriten)
//		{
//			CyBLE_RingBuffer->overwriten = 0;
//		}
//	}
//}
//
//static void RingBuffer_VerifyHead(void)
//{
//	if(CyBLE_RingBuffer->head_index > (RING_BUFFER_SIZE - 1))
//	{
//		CyBLE_RingBuffer->head_index = 0;
//		if(CyBLE_RingBuffer->head_index == CyBLE_RingBuffer->tail_index)
//		{
//			CyBLE_RingBuffer->overwriten = 1;
//			CyBLE_RingBuffer->tail_index++;
//		}
//	}
//}



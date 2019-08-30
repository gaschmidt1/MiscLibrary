/*
 * RingBuffer.c
 *
 *  Created on: 12 de fev de 2019
 *      Author: giovani
 */

#include "RingBuffer.h"

static void RingBuffer_VerifyTail(ring_buffer_typedef *ptr_buffer);
static void RingBuffer_VerifyHead(ring_buffer_typedef *ptr_buffer);


void RingBuffer_Queue_Byte(ring_buffer_typedef *ptr_buffer , uint8_t data_received)
{
	if(ptr_buffer->overwriten)
	{
		ptr_buffer->tail_index++;
		RingBuffer_VerifyTail(ptr_buffer);
	}
	ptr_buffer->buffer[ptr_buffer->head_index] = data_received;
	ptr_buffer->head_index++;
	RingBuffer_VerifyHead(ptr_buffer);
}

uint8_t RingBuffer_Dequeue_Byte(ring_buffer_typedef *ptr_buffer)
{
	uint8_t return_byte;
	if(ptr_buffer->tail_index == ptr_buffer->head_index)
	{
		return_byte =  0;
	}
	else
	{
		return_byte = ptr_buffer->buffer[ptr_buffer->tail_index];
		ptr_buffer->tail_index++;
		RingBuffer_VerifyTail(ptr_buffer);

	}
	return return_byte;
}

static void RingBuffer_VerifyTail(ring_buffer_typedef *ptr_buffer)
{
	if(ptr_buffer->tail_index > (RING_BUFFER_SIZE - 1))
	{
		ptr_buffer->tail_index = 0;
		if(ptr_buffer->tail_index == ptr_buffer->head_index)
		{
			ptr_buffer->buffer[ptr_buffer->head_index] = 0;
		}
		else if((ptr_buffer->tail_index < ptr_buffer->head_index) && ptr_buffer->overwriten)
		{
			ptr_buffer->overwriten = 0;
		}
	}
}

static void RingBuffer_VerifyHead(ring_buffer_typedef *ptr_buffer)
{
	if(ptr_buffer->head_index > (RING_BUFFER_SIZE - 1))
	{
		ptr_buffer->head_index = 0;
		if(ptr_buffer->head_index == ptr_buffer->tail_index)
		{
			ptr_buffer->overwriten = 1;
			ptr_buffer->tail_index++;
		}
	}
}

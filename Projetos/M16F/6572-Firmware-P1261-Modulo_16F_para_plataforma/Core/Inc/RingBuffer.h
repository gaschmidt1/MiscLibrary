/*
 * RingBuffer.h
 *
 *  Created on: 12 de fev de 2019
 *      Author: giovani
 */

#ifndef INC_RINGBUFFER_H_
#define INC_RINGBUFFER_H_
#include <stdint.h>


#define RING_BUFFER_SIZE 256


typedef struct {

  char buffer[RING_BUFFER_SIZE];

  uint16_t tail_index;

  uint16_t head_index;
  uint8_t overwriten;
}ring_buffer_typedef;

void RingBuffer_Queue_Byte(ring_buffer_typedef *ptr_buffer , uint8_t data_received);
uint8_t RingBuffer_Dequeue_Byte(ring_buffer_typedef *ptr_buffer);

#endif /* INC_RINGBUFFER_H_ */

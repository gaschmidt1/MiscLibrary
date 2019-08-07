/******************************************************************************/
/**
 * @file    Queue.h
 * @author  gaschmidt1@gmail.com
 * @section DESCRIPTION
 * A generic byte FIFO implementation.
 */

#ifndef QUEUE_H
#define	QUEUE_H

#ifdef	__cplusplus
extern "C"
{
#endif

  /*******************************************************************************
 * Include Files
 */

#include <stdint.h>

/*******************************************************************************
 * Type Definitions
 */
typedef struct
{
    uint8_t  size;
    uint8_t  v_data[20];
    uint8_t  front;
    uint8_t  back;
    uint8_t  full;
} fifo_t;

/*******************************************************************************
 * Functions
 */
void fifo_init(fifo_t* p_fifo, uint8_t size);
uint8_t fifo_queue(fifo_t* p_fifo, uint8_t p_data);
uint8_t fifo_dequeue(fifo_t* p_fifo, uint8_t* p_data);
uint8_t fifo_peek(fifo_t* p_fifo, uint8_t* p_data);
uint8_t fifo_get_count(const fifo_t* p_fifo);

#ifdef	__cplusplus
}
#endif

#endif	/* QUEUE_H */


/******************************************************************************/
/**
 * @file    fifo.c
 * @author  gaschmidt1@gmail.com
 * @section DESCRIPTION
 * A generic byte FIFO implementation.
 */

/*******************************************************************************
 * Include Files
 */
//#include <stm32l1xx.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"


/******************************************************************************/
/**
 * @brief Initialize the FIFO.
 *
 * @param  p_fifo  A pointer to a structure to maintain FIFO data.
 */
void fifo_init(fifo_t* p_fifo, uint8_t size)
{
	if (p_fifo)
	{
		p_fifo->v_data[0]=0;
		p_fifo->size = size;
		p_fifo->full = 0;
		p_fifo->front = 0;
		p_fifo->back  = 0;
	}
}

/******************************************************************************/
/**
 * @brief Queue a byte at the back of the FIFO.
 *
 * @param  p_fifo  A pointer to the FIFO structure to queue data to.
 * @param  data  The data byte to add to the FIFO.
 */
uint8_t fifo_queue(fifo_t* p_fifo, uint8_t p_data)
{
	__disable_irq();
	uint8_t result = 0;

	if(p_fifo->full == 0)
	{
		p_fifo->v_data[p_fifo->back] = p_data;
		p_fifo->back++;

		if(p_fifo->back == p_fifo->size)
		{
			p_fifo->back = 0;
		}
		if(p_fifo->back == p_fifo->front)
		{
			p_fifo->full = 1;
		}
		result = 1;
	}
	__enable_irq();
	return(result);
}

/******************************************************************************/
/**
 * @brief Dequeue and return a pointer the next byte the front of the FIFO.
 *
 * @param  p_fifo  A pointer to the FIFO structure to dequeue data from.
 *
 * @return A pointer to the dequeued data, else 0 if none.
 */
uint8_t fifo_dequeue(fifo_t* p_fifo, uint8_t* p_data)
{
	//__disable_irq();
	uint8_t result = 0;

	if(!(p_fifo->back == p_fifo->front) && (p_fifo->full == 0))
	{
		if(p_fifo->full == 1)
		{
			p_fifo->full = 0;
		}
		*p_data = p_fifo->v_data[p_fifo->front];
		p_fifo->front++;


		if(p_fifo->front == (p_fifo->size))
		{
			p_fifo->front = 0;
		}
		result = 1;
	}
	//__enable_irq();
	return(result);
}

/******************************************************************************/
/**
 * @brief Dequeue and return a pointer the next byte the front of the FIFO.
 *
 * @param  p_fifo  A pointer to the FIFO structure to dequeue data from.
 *
 * @return A pointer to the dequeued data, else 0 if none.
 */
uint8_t fifo_peek(fifo_t* p_fifo, uint8_t* p_data)
{
	//__disable_irq();
	uint8_t result = 0;

	if((p_fifo->back == p_fifo->front) && (p_fifo->full == 0))
	{
		*p_data = p_fifo->v_data[p_fifo->front];
		result = 1;
	}
	// __enable_irq();
	return(result);
}

/******************************************************************************/
/**
 * @brief Get the count of bytes remaining in the FIFO.
 *
 * @param  p_fifo  A pointer to the FIFO structure to get the size of.
 *
 * @return The count of bytes remaining in the FIFO.
 */
uint8_t fifo_get_count(const fifo_t* p_fifo)
{
	uint8_t count;

	if((p_fifo->back == p_fifo->front) && (p_fifo->full == 0))
	{
		count = 0;
	}
	else if(p_fifo->full == 1)
	{
		count = p_fifo->size;
	}
	else if(p_fifo->back > p_fifo->front)
	{
		count = p_fifo->back - p_fifo->front;
	}
	else
	{
		count = p_fifo->size - p_fifo->back;
		if(p_fifo->back > 0)
		{
			count += p_fifo->back - 1;
		}
	}
	return(count);
}

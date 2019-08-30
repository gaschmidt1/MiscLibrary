/*
 * fifo.h
 *
 *  Created on: 12 de ago de 2019
 *      Author: gerry
 */

/******************************************************************************/
/**
 * @file    fifo.h
 * @author  gaschmidt1@gmail.com
 * @section DESCRIPTION
 * A generic byte FIFO implementation.
 */

#ifndef __FIFO_H__
#define __FIFO_H__

/*******************************************************************************
 * Include Files
 */
#include "stm32f0xx_hal.h"
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

#endif


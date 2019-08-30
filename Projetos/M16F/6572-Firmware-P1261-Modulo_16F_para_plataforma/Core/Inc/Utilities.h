/*
 * Utilities.h
 *
 *  Created on: 13 de fev de 2019
 *      Author: giovani
 */

#ifndef INC_UTILITIES_H_
#define INC_UTILITIES_H_

#include <stdint.h>
uint8_t U8_To_Hex(uint8_t int_number);
uint8_t Hex_To_U8(uint8_t hex_value);
uint8_t Argument_To_Int (uint8_t *ptr_buff,uint8_t size_of_buff, uint8_t argument_nr );

#endif /* INC_UTILITIES_H_ */

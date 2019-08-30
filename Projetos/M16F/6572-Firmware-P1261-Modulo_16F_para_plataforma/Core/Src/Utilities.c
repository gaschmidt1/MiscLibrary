/*
 * Utilities.c
 *
 *  Created on: 13 de fev de 2019
 *      Author: giovani
 */


#include "Utilities.h"

const char HexTable[17]={"0123456789ABCDEF"};
uint8_t U8_To_Hex(uint8_t int_number)
{
	return HexTable[int_number & 15];
}



uint8_t Hex_To_U8(uint8_t hex_value)
{
	uint8_t return_value = 0;
	uint8_t i;

	for(i = 0 ; i < 16 ; i++)
	{
		if(hex_value == HexTable[i])
		{
			return_value = i;
			break;
		}
	}
	return return_value;
}


uint8_t Argument_To_Int (uint8_t *ptr_buff,uint8_t size_of_buff, uint8_t argument_nr )
{
	uint8_t buffer_index = 0;
	uint8_t argument_found = 0;
	uint8_t argument_counter = 1;
	//uint8_t *argument_init_position = 0;
	uint8_t return_value = 0;
	uint8_t convertion_done = 0;
	uint8_t tmp_value;
	uint8_t multiplier = 1;

	while(!argument_found && buffer_index < size_of_buff)
	{
		if(argument_counter == argument_nr)
		{
			argument_found = 1;
//			argument_init_position = &ptr_buff[buffer_index];
		}
		else
		{
			if(ptr_buff[buffer_index] == ',')
			{
				argument_counter++;
			}
			buffer_index++;
		}
	}
	while(!convertion_done && buffer_index < size_of_buff && argument_found)
	{
		if(ptr_buff[buffer_index]!=',' )
		{
			return_value *= multiplier;
			tmp_value = ptr_buff[buffer_index] - 0x30;
			return_value += tmp_value ;
			multiplier = 10;
			buffer_index++;
		}
		else
		{
			convertion_done = 1;
		}

	}
	return return_value;
}

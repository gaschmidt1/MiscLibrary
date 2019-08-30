/*
 * NetCommands.h
 *
 *  Created on: 12 de fev de 2019
 *      Author: giovani
 */

#ifndef INC_NETCOMMANDS_H_
#define INC_NETCOMMANDS_H_

#include <stdint.h>
#include "cmsis_os.h"

#define MAX_COMMANDS 20


typedef void (Command_Callback)(uint8_t* args_buffer, uint16_t size_of_buffer);


typedef struct
{
	char Command[MAX_COMMANDS];
	Command_Callback *Command_Function[MAX_COMMANDS];

}Commands_Struct_Typedef;

Commands_Struct_Typedef Commands_List;

void NetCommands_Init(void);
void NetCommands_Execute(uint8_t command , uint8_t* params, uint16_t size_of_params);

#endif /* INC_NETCOMMANDS_H_ */

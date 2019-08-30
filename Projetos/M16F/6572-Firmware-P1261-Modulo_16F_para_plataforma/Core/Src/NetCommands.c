/*
 * NetCommands.c
 *
 *  Created on: 12 de fev de 2019
 *      Author: giovani
 */

#include <main.h>
#include <NetCommands.h>
#include <P1178_Commands.h>
#include <sys/_stdint.h>


static void NetCommands_Register(uint8_t command ,Command_Callback command_callback );

static uint16_t command_index = 0;

void NetCommands_Init(void)
{
	NetCommands_Register('A', RecebeParamatrosRoscaDoTubo);
	NetCommands_Register('B', RecebeParametrosRoscaDeElevacao);
	NetCommands_Register('C', RecebeParametrosRoscaInferior);
	NetCommands_Register('D', RecebeParametrosTubo);
	NetCommands_Register('E', RecebeParametrosOutros);

	NetCommands_Register('F',LeParametrosRoscaDoTubo);
	NetCommands_Register('G',LeParametrosRoscaDeElevacao);
	NetCommands_Register('H',LeParametrosRoscaInferior);
	NetCommands_Register('I',LeParametrosTubo);
	NetCommands_Register('J',LeParametrosOutros);
}


void NetCommands_Execute(uint8_t command , uint8_t* params, uint16_t size_of_params)
{
	uint16_t i;
	for(i = 0; i <=command_index; i++)
	{
		if(Commands_List.Command[i] == command)
		{
			Commands_List.Command_Function[i](params,size_of_params);
			break;
		}
	}
}


static void NetCommands_Register(uint8_t command ,Command_Callback command_callback )
{

	if(command_index >= MAX_COMMANDS)
	{
		Error_Handler();
	}
	Commands_List.Command[command_index] = command;
	Commands_List.Command_Function[command_index] = command_callback;
	command_index++;

}

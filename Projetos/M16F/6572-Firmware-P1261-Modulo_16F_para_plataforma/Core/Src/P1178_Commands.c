/*
 * P1178_Commands.c
 *
 *  Created on: 12 de fev de 2019
 *      Author: giovani
 */

#include "Application_x.h"
#include "P1178_Commands.h"
#include "CyBLE.h"
#include "usart.h"

static void Dispara_Evento_Flash(void);

void EnviaTresParametros(uint8_t comando, uint8_t param1, uint8_t param2,uint8_t param3);
void EnviaQuatroParametros(uint8_t comando, uint8_t param1, uint8_t param2,uint8_t param3,uint8_t param4);
void EnviaDoisParametros(uint8_t comando, uint8_t param1, uint8_t param2);

static uint8_t Buffer_Transmissao[40];
static uint8_t checksum_calculado = 0;
static uint16_t buffer_index = 0;


void RecebeParamatrosRoscaDoTubo(uint8_t *params, uint16_t size_of_params)
{


	uint8_t arg1 = Argument_To_Int(params, size_of_params, 1);
	uint8_t arg2 = Argument_To_Int(params, size_of_params, 2);
	uint8_t arg3 = Argument_To_Int(params, size_of_params, 3);

	P1178_Variaveis->Variaveis.RoscaTuboDesligada = arg1;
	P1178_Variaveis->Variaveis.RoscaTuboLigada = arg2;
	P1178_Variaveis->Variaveis.RoscaTuboRampa = arg3;

	Dispara_Evento_Flash();

	EnviaTresParametros('A',arg1,arg2,arg3);
}

void RecebeParametrosRoscaDeElevacao(uint8_t *params, uint16_t size_of_params)
{
	uint8_t arg1 = Argument_To_Int(params,size_of_params,1);
	uint8_t arg2 = Argument_To_Int(params,size_of_params,2);
	uint8_t arg3 = Argument_To_Int(params,size_of_params,3);

	P1178_Variaveis->Variaveis.RoscaElevacaoDesligada = arg1;
	P1178_Variaveis->Variaveis.RoscaElevacaoLigada = arg2;
	P1178_Variaveis->Variaveis.RoscaElevacaoRampa = arg3;

	Dispara_Evento_Flash();

	EnviaTresParametros('B',arg1,arg2,arg3);
}

void RecebeParametrosRoscaInferior(uint8_t *params, uint16_t size_of_params)
{
	uint8_t arg1 = Argument_To_Int(params,size_of_params,1);
	uint8_t arg2 = Argument_To_Int(params,size_of_params,2);
	uint8_t arg3 = Argument_To_Int(params,size_of_params,3);

	P1178_Variaveis->Variaveis.RoscaInferiorDesligada = arg1;
	P1178_Variaveis->Variaveis.RoscaInferiorLigada = arg2;
	P1178_Variaveis->Variaveis.RoscaInferiorRampa = arg3;

	Dispara_Evento_Flash();

	EnviaTresParametros('C',arg1,arg2,arg3);
}

void RecebeParametrosTubo(uint8_t *params, uint16_t size_of_params)
{
	uint8_t arg1 = Argument_To_Int(params,size_of_params,1);
	uint8_t arg2 = Argument_To_Int(params,size_of_params,2);
	uint8_t arg3 = Argument_To_Int(params,size_of_params,3);
	uint8_t arg4 = Argument_To_Int(params,size_of_params,4);

	P1178_Variaveis->Variaveis.TuboHorario = arg1;
	P1178_Variaveis->Variaveis.TuboAntiHorario = arg2;
	P1178_Variaveis->Variaveis.TuboParado = arg3;
	P1178_Variaveis->Variaveis.TuboRampa = arg4;

	Dispara_Evento_Flash();

	EnviaQuatroParametros('D',arg1,arg2,arg3,arg4);
}

void RecebeParametrosOutros(uint8_t *params, uint16_t size_of_params)
{
	uint8_t arg1 = Argument_To_Int(params,size_of_params,1);
	uint8_t arg2 = Argument_To_Int(params,size_of_params,2);

	P1178_Variaveis->Variaveis.OutrosTempoIgnicao = arg1;
	P1178_Variaveis->Variaveis.OutrosTempoMovimentoComportas = arg2;

	Dispara_Evento_Flash();

	EnviaDoisParametros('E',arg1,arg2);
}

void LeParametrosRoscaDoTubo(uint8_t *params, uint16_t size_of_params)
{
	uint8_t arg1 = P1178_Variaveis->Variaveis.RoscaTuboDesligada;
	uint8_t arg2 = P1178_Variaveis->Variaveis.RoscaTuboLigada;
	uint8_t arg3 = P1178_Variaveis->Variaveis.RoscaTuboRampa;
	EnviaTresParametros('F',arg1,arg2,arg3);
}

void LeParametrosRoscaDeElevacao(uint8_t *params, uint16_t size_of_params)
{

	uint8_t arg1 = P1178_Variaveis->Variaveis.RoscaElevacaoDesligada;
	uint8_t arg2 = P1178_Variaveis->Variaveis.RoscaElevacaoLigada;
	uint8_t arg3 = P1178_Variaveis->Variaveis.RoscaElevacaoRampa;

	EnviaTresParametros('G',arg1,arg2,arg3);
}

void LeParametrosRoscaInferior(uint8_t *params, uint16_t size_of_params)
{
	uint8_t arg1 = P1178_Variaveis->Variaveis.RoscaInferiorDesligada;
	uint8_t arg2 = P1178_Variaveis->Variaveis.RoscaInferiorLigada;
	uint8_t arg3 = P1178_Variaveis->Variaveis.RoscaInferiorRampa;

	EnviaTresParametros('H',arg1,arg2,arg3);
}


void LeParametrosTubo(uint8_t *params, uint16_t size_of_params)
{
	uint8_t arg1 = P1178_Variaveis->Variaveis.TuboHorario;
	uint8_t arg2 = P1178_Variaveis->Variaveis.TuboAntiHorario;
	uint8_t arg3 = P1178_Variaveis->Variaveis.TuboParado;
	uint8_t arg4 = P1178_Variaveis->Variaveis.TuboRampa;

	EnviaQuatroParametros('I',arg1,arg2,arg3,arg4);
}

void LeParametrosOutros(uint8_t *params, uint16_t size_of_params)
{
	uint8_t arg1 = P1178_Variaveis->Variaveis.OutrosTempoIgnicao;
	uint8_t arg2 = P1178_Variaveis->Variaveis.OutrosTempoMovimentoComportas;

	EnviaDoisParametros('J',arg1,arg2);
}


void EnviaDoisParametros(uint8_t comando, uint8_t param1, uint8_t param2)
{
	checksum_calculado = 0;
	buffer_index = 0;

	Buffer_Transmissao[buffer_index] = STX;
	Buffer_Transmissao[++buffer_index] = 'b';
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = 'a';
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = comando;
	checksum_calculado^=Buffer_Transmissao[buffer_index];


	Buffer_Transmissao[++buffer_index] = '[';
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = (uint8_t)(param1/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param1%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param1%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = ',';

	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)(param2/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param2%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param2%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = ']';
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = U8_To_Hex((checksum_calculado & 0xF0)>>4);
	Buffer_Transmissao[++buffer_index] = U8_To_Hex(checksum_calculado &0x0F);
	Buffer_Transmissao[++buffer_index] = ETX;

	USART8_Send_Packet(Buffer_Transmissao,buffer_index+1);
}

void EnviaTresParametros(uint8_t comando, uint8_t param1, uint8_t param2,uint8_t param3)
{
	checksum_calculado = 0;
	buffer_index = 0;

	Buffer_Transmissao[buffer_index] = STX;
	Buffer_Transmissao[++buffer_index] = 'b';
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = 'a';
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = comando;
	checksum_calculado^=Buffer_Transmissao[buffer_index];


	Buffer_Transmissao[++buffer_index] = '[';
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = (uint8_t)(param1/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param1%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param1%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = ',';

	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)(param2/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param2%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param2%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];


	Buffer_Transmissao[++buffer_index] = ',';

	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)(param3/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param3%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param3%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];



	Buffer_Transmissao[++buffer_index] = ']';
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = U8_To_Hex((checksum_calculado & 0xF0)>>4);
	Buffer_Transmissao[++buffer_index] = U8_To_Hex(checksum_calculado &0x0F);
	Buffer_Transmissao[++buffer_index] = ETX;

	USART8_Send_Packet(Buffer_Transmissao,buffer_index+1);

}

void EnviaQuatroParametros(uint8_t comando, uint8_t param1, uint8_t param2,uint8_t param3,uint8_t param4)
{
	checksum_calculado = 0;
	buffer_index = 0;

	Buffer_Transmissao[buffer_index] = STX;
	Buffer_Transmissao[++buffer_index] = 'b';
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = 'a';
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = comando;
	checksum_calculado^=Buffer_Transmissao[buffer_index];


	Buffer_Transmissao[++buffer_index] = '[';
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = (uint8_t)(param1/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param1%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param1%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = ',';

	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)(param2/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param2%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param2%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];


	Buffer_Transmissao[++buffer_index] = ',';

	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)(param3/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param3%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param3%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = ',';

	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)(param4/100)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param4%100)/10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];
	Buffer_Transmissao[++buffer_index] = (uint8_t)((param4%100)%10)+ 0x30;
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = ']';
	checksum_calculado^=Buffer_Transmissao[buffer_index];

	Buffer_Transmissao[++buffer_index] = U8_To_Hex((checksum_calculado & 0xF0)>>4);
	Buffer_Transmissao[++buffer_index] = U8_To_Hex(checksum_calculado &0x0F);
	Buffer_Transmissao[++buffer_index] = ETX;

	USART8_Send_Packet(Buffer_Transmissao,buffer_index+1);

}

static void Dispara_Evento_Flash(void)
{
	osSignalSet(appThreadId,APP_FLASH_VERIFY);
}




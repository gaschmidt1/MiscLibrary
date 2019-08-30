/*
 * NRF905.h
 *
 *  Created on: 24 de jan de 2019
 *      Author: giovani
 */

#ifndef INC_NRF905_H_
#define INC_NRF905_H_

#include<stdint.h>
#include "NRF905_Defines.h"
#include "cmsis_os.h"

#define SPI_TX_COMPLETED 0x01
#define SPI_RX_COMPLETED 0x02
#define SPI_ERROR 0x04
#define SPI_ANY_SIGNAL 0x00
#define NORDIC_ANY_SIGNAL SPI_ANY_SIGNAL
#define NORDIC_DR_SIGNAL 0x08


#define USE_NRF905 1

#define NRF905_GERAL_ADDR 0xFFFF

#define NRF905_DEFAULT_TX_SIZE 4
#define NRF905_DEFAULT_RX_SIZE 4
#define NRF905_DEFAULT_OFFSET 0x8000
#define NRF905_DEFAULT_TX_ADDR (NRF905_DEFAULT_RX_ADDR + NRF905_DEFAULT_OFFSET)
#define NRF905_DEFAULT_RX_ADDR 0x0482

osThreadId NRF905ThreadId;
osPoolId   NRF905DataPool_Id;


typedef enum {
	INITIAL_VALUE_OPERATING_MODE = 0,
	POWER_DOWN_AND_SPI_PROGRAMMING,
	STANDBY_AND_SPI_PROGRAMMING,
	READ_DATA_FROM_RX_REGISTER,
	RADIO_ENABLED_SHOCKBURST_RX,
	RADIO_ENABLED_SHOCKBURST_TX
} NRF905_OperationMode;


typedef struct
{
	uint32_t RX_addr;
	uint32_t TX_addr;
	uint16_t size_of_tx;
	uint16_t size_of_rx;
}NRF905_Configuration_Structure_Typedef;

typedef enum
{
	Set_Tx_Size,
	Check_Tx_Size,
	Waiting,
}NRF905_Commands_Typedef;

typedef struct
{
	NRF905_Commands_Typedef Command;
	NRF905_Configuration_Structure_Typedef App_Configuration_Data;
	uint8_t received_rx_payload[20];
	uint8_t received_size;
	uint8_t new_payload;
}NRF905_Control_Struct_Typedef;

NRF905_Control_Struct_Typedef *NRF905_Control;

typedef enum
{
	Configure,
	Check_Configuration,
	Set_TX_Size,
	Check_TX_Size,
	Set_RX_Size,
	Check_RX_Size,
	Set_TX_Addr,
	Check_TX_Addr,
	Set_RX_Addr,
	Check_RX_Addr
}NRF905_Config_States_Typedef;

typedef enum
{
	Wait_Data = 0,
	Transmit_Ack,
	Remote_Control_Start_Register,
	Send_Register_Payload,
	Idle,
}NRF905_States_Typedef;

void NRF905_Init(void);
void NRF905_Config(void);
#endif /* INC_NRF905_H_ */

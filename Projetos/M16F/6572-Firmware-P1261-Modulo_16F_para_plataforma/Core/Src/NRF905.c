/*
 * NRF905.c
 *
 *  Created on: 24 de jan de 2019
 *      Author: giovani
 */


#include "Application_x.h"
#include "NRF905.h"
#include "gpio.h"
#include "spi.h"
#include "Flash.h"

#include "stm32f0xx_ll_utils.h"

#define SIZE_OF_CONFIGURATION_PAYLOAD 10
#define SIZE_OF_TRANSMISSION_BUFFER 20
#define SIZE_OF_RECEIVE_BUFFER 20


osPoolDef (NRF905DataPool, 1, NRF905_Control_Struct_Typedef);

NRF905_States_Typedef NRF905_State_Machine;
NRF905_OperationMode Old_Operation_Mode = STANDBY_AND_SPI_PROGRAMMING;

SPI_Communication_Typedef NR905_SPI_Properties;
uint8_t data_buffer[10] = {0};

uint16_t NRF905_Get_Rx_Size(void);
uint8_t NRF905_Set_Rx_Size(uint16_t rx_size);
uint8_t NRF905_Set_Tx_Size(uint16_t tx_size);
uint16_t NRF905_Get_Tx_Size(void);
void NRF905_Select_Chip(void);
void NRF905_Deselect_Chip(void);
uint8_t NRF905_Send_Configuration(void);
uint8_t NRF905_Check_Configuration(void);
uint8_t NRF905_Set_Tx_Addr(uint32_t tx_addr);
uint32_t NRF905_Get_Tx_Addr(void);
uint32_t NRF905_Get_Rx_Addr(void);
uint8_t NRF905_Set_Rx_Addr(uint32_t rx_addr);
void NRF905_Send_Tx_Payload(uint8_t *buffer_to_send);
static uint8_t* Addr_to_Buffer(uint32_t addr);
static void Wait_For_Transmission(void);
static void Wait_Reception(void);
void NRF905_Get_Rx_Payload(void);

void NRF905Task(void const * argument);

void NRF905_Set_Operation_Mode(NRF905_OperationMode operation_mode);

void NRF905_Config(void);


const uint8_t NRF905_Configuration_Payload[SIZE_OF_CONFIGURATION_PAYLOAD] =
{
		NRF905_CH_NO_FREQ_433_2MHz & 0xFF,
		NRF905_PA_PWR_PLUS_10dBm|NRF905_HFREQ_PLL_433MHzBand|(NRF905_CH_NO_FREQ_433_0MHz>>8),
		NRF905_TX_AFW_4_BYTES|NRF905_RX_AFW_4_BYTES,
		NRF905_RX_PW_4_BYTES,
		NRF905_TX_PW_4_BYTES,
		0x00,
		0x00,
		0x00,
		0x00,
		NRF905_CRC_MODE_16_BITS|NRF905_XOF_4MHz,
};



void NRF905_Init(void)
{
	GPIO_Configure_NRF905_IO();
	NRF905_Deselect_Chip();

	osThreadDef(NRF905Task, NRF905Task, osPriorityAboveNormal, 0, 512);
	NRF905ThreadId = osThreadCreate(osThread(NRF905Task), NULL);

	NR905_SPI_Properties.SPI_Handler = NORDIC_HSPI;
	NR905_SPI_Properties.peripheral_name = NRF905;
	NR905_SPI_Properties.chip_select_func = NRF905_Select_Chip;
	NR905_SPI_Properties.chip_deselect_func = NRF905_Deselect_Chip;

	NRF905DataPool_Id = osPoolCreate (osPool(NRF905DataPool));
	NRF905_Control = (NRF905_Control_Struct_Typedef *)osPoolCAlloc (NRF905DataPool_Id);
}



void NRF905Task(void const * argument)
{
	NRF905_Config();
	uint16_t register_timeout_count = 0;
	NRF905_State_Machine = Remote_Control_Start_Register;

	for(;;)
	{
		switch(NRF905_State_Machine)
		{
		case Wait_Data:

			NRF905_Set_Operation_Mode(RADIO_ENABLED_SHOCKBURST_RX);
			Wait_Reception();
			//GPIO_Change_Pin_State(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
			GPIO_Toggle_Pin(LED_VD_GPIO_Port, LED_VD_Pin);
			NRF905_Get_Rx_Payload();
			NRF905_State_Machine = Transmit_Ack;
			break;

		case Transmit_Ack:
			data_buffer[0] = 'O';
			data_buffer[1] = 'K';
			data_buffer[2] = 'O';
			data_buffer[3] = 'K';
			NRF905_Send_Tx_Payload(data_buffer);
			Wait_For_Transmission();
			GPIO_Change_Pin_State(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
			NRF905_State_Machine = Wait_Data;
			break;

		case Remote_Control_Start_Register:
			NRF905_Set_Tx_Addr(NRF905_GERAL_ADDR);
			NRF905_Set_Rx_Addr(NRF905_GERAL_ADDR);
			NRF905_Set_Operation_Mode(RADIO_ENABLED_SHOCKBURST_RX);
			NRF905_State_Machine = Send_Register_Payload;
			register_timeout_count = 0;
			break;

		case Send_Register_Payload:
			if(register_timeout_count >= 500)
			{
				NRF905_Set_Tx_Addr(NRF905_Control->App_Configuration_Data.TX_addr);
				NRF905_Set_Rx_Addr(NRF905_Control->App_Configuration_Data.RX_addr);
				NRF905_State_Machine = Wait_Data;
			}
			else
			{
				register_timeout_count++;

				NRF905_Send_Tx_Payload(Addr_to_Buffer(NRF905_Control->App_Configuration_Data.RX_addr));
				Wait_For_Transmission();
			}
			break;
		default:
			break;
		}

		osDelay(1);
	}

}

uint32_t UuIddata_value1;
uint32_t UuIddata_value2;
uint32_t UuIddata_value3;

void NRF905_Config(void)
{

	NRF905_Config_States_Typedef NRF905_Config_States = Configure;
	uint8_t configuration_done = 0;
	uint16_t tmp_value = 0;
	uint32_t tmp_addr = 0;



	UuIddata_value1 = LL_GetUID_Word0();
	UuIddata_value2 = LL_GetUID_Word1();
	UuIddata_value3 = LL_GetUID_Word2();

	NRF905_Control->App_Configuration_Data.size_of_tx = NRF905_DEFAULT_TX_SIZE;
	NRF905_Control->App_Configuration_Data.size_of_rx = NRF905_DEFAULT_RX_SIZE;
	//NRF905_Control->App_Configuration_Data.RX_addr = Flash_Read_Uint32(APP_DEFAULT_VALUES_LOCATION + NRF905_ADDRESS_OFFSET);
	NRF905_Control->App_Configuration_Data.RX_addr = UuIddata_value1;
	NRF905_Control->App_Configuration_Data.TX_addr = (NRF905_Control->App_Configuration_Data.RX_addr  + NRF905_DEFAULT_OFFSET);

	while(!configuration_done)
	{
		switch(NRF905_Config_States)
		{
		case Configure:
			if(NRF905_Send_Configuration())
			{
				NRF905_Config_States = Check_Configuration;
			}
			break;

		case Check_Configuration:
			if(NRF905_Check_Configuration())
			{
				NRF905_Config_States =	Set_TX_Size;
			}
			else
			{
				NRF905_Config_States = Configure;
			}
			break;

		case Set_TX_Size:
			if(NRF905_Set_Tx_Size(NRF905_Control->App_Configuration_Data.size_of_tx))
			{
				NRF905_Config_States = Check_TX_Size;
			}
			break;

		case Check_TX_Size:
			tmp_value = NRF905_Get_Tx_Size();
			if(tmp_value == NRF905_Control->App_Configuration_Data.size_of_tx)
			{
				NRF905_Config_States =	Set_RX_Size;

			}
			else
			{
				NRF905_Config_States =	Set_TX_Size;
			}
			break;

		case Set_RX_Size:
			if(NRF905_Set_Rx_Size(NRF905_Control->App_Configuration_Data.size_of_rx))
			{
				NRF905_Config_States = Check_RX_Size;
			}
			break;

		case Check_RX_Size:
			tmp_value = NRF905_Get_Rx_Size();
			if(tmp_value == NRF905_Control->App_Configuration_Data.size_of_rx)
			{
				NRF905_Config_States = Set_TX_Addr;
			}
			else
			{
				NRF905_Config_States = Set_RX_Size;
			}
			break;

		case Set_TX_Addr:
			if(NRF905_Set_Tx_Addr(NRF905_Control->App_Configuration_Data.TX_addr))
			{
				NRF905_Config_States = Check_TX_Addr;
			}
			break;

		case Check_TX_Addr:
			tmp_addr = NRF905_Get_Tx_Addr();
			if(tmp_addr == NRF905_Control->App_Configuration_Data.TX_addr)
			{
				NRF905_Config_States = Set_RX_Addr;
			}
			break;

		case Set_RX_Addr:
			if(NRF905_Set_Rx_Addr(NRF905_Control->App_Configuration_Data.RX_addr))
			{
				NRF905_Config_States = Check_RX_Addr;
			}
			break;

		case Check_RX_Addr:
			tmp_addr = NRF905_Get_Rx_Addr();
			if(tmp_addr == NRF905_Control->App_Configuration_Data.RX_addr)
			{
				configuration_done = 1;
				osSignalSet(appThreadId,NRF905_Signal_Ready);
			}
			break;

		default:
			break;
		}
		osDelay(1);
	}

}

void NRF905_Send_Tx_Payload(uint8_t *buffer_to_send)
{
	osEvent evt;
	uint8_t i;
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};

	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_WTP;

	for(i = 0 ; i <  NRF905_Control->App_Configuration_Data.size_of_tx; i++)
	{
		transmission_buffer[i+1] = *buffer_to_send;
		buffer_to_send++;
	}

	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.size_of_transmission = NRF905_Control->App_Configuration_Data.size_of_tx + 1;
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	SPI_Write_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED,100);
	evt = evt;
	SPI_Release_Bus(&NR905_SPI_Properties);
	NRF905_Set_Operation_Mode(RADIO_ENABLED_SHOCKBURST_RX);

	while(GPIO_Get_Pin_State(NORDIC_CD_GPIO_Port,NORDIC_CD_Pin))
	{
		osDelay(10);
	}
	NRF905_Set_Operation_Mode(RADIO_ENABLED_SHOCKBURST_TX);

}

void NRF905_Get_Rx_Payload(void)
{
	uint8_t i;
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	uint8_t receive_buffer[SIZE_OF_RECEIVE_BUFFER] = {0};
	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);

	transmission_buffer[0] = NRF905_RRP;
	transmission_buffer[1] = 0;
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.size_of_transmission = 1 ;
	NR905_SPI_Properties.ptr_receive_buffer = receive_buffer;
	NR905_SPI_Properties.size_of_receive = NRF905_Control->App_Configuration_Data.size_of_rx + 1;
	SPI_Transmit_Receive_Data(&NR905_SPI_Properties);
	osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	for(i = 0; i <  NRF905_Control->App_Configuration_Data.size_of_rx; i++)
	{
		NRF905_Control->received_rx_payload[i] = receive_buffer[i + 1];
	}
	NRF905_Control->received_size =  NRF905_Control->App_Configuration_Data.size_of_rx;
	NRF905_Control->new_payload = 1; // set new payload
}

uint8_t NRF905_Set_Rx_Addr(uint32_t rx_addr)
{
	osEvent evt;
	uint8_t state = 0;
	uint8_t i ;
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_W_RA;

	for(i = 0; i < 4; i++)
	{
		transmission_buffer[i+1] = (rx_addr>>24);
		rx_addr<<=8;
	}

	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.size_of_transmission = 5 ;
	SPI_Write_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status == osEventTimeout)
	{
		state =  0;
	}
	else
	{
		state = 1;
	}
	return state;
}

uint8_t NRF905_Set_Tx_Addr(uint32_t tx_addr)
{
	osEvent evt;
	uint8_t state = 0;
	uint8_t i ;
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_WTA;

	for(i = 0; i < 4; i++)
	{
		transmission_buffer[i+1] = (tx_addr>>24);
		tx_addr<<=8;
	}

	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.size_of_transmission = 5 ;
	SPI_Write_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status == osEventTimeout)
	{
		state =  0;
	}
	else
	{
		state = 1;
	}
	return state;
}

uint8_t NRF905_Set_Tx_Size(uint16_t tx_size)
{
	osEvent evt;
	uint8_t state = 0;
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	if(tx_size > 32)
	{
		return state;
	}
	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_W_WTP;
	transmission_buffer[1] =  tx_size;
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.size_of_transmission = 2 ;
	SPI_Write_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status == osEventTimeout)
	{
		state =  0;
	}
	else
	{
		state = 1;
	}
	return state;
}


uint8_t NRF905_Set_Rx_Size(uint16_t rx_size)
{
	osEvent evt;
	uint8_t state = 0;
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	if(rx_size > 32)
	{
		return state;
	}
	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_W_WRP;
	transmission_buffer[1] =  rx_size;
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.size_of_transmission = 2 ;
	SPI_Write_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status == osEventTimeout)
	{
		state =  0;
	}
	else
	{
		state = 1;
	}
	return state;
}


uint16_t NRF905_Get_Tx_Size(void)
{
	uint16_t tx_size = 0;
	osEvent evt;
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	uint8_t receive_buffer[SIZE_OF_RECEIVE_BUFFER] = {0};

	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_R_WTP;
	transmission_buffer[1] =  0;
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.size_of_transmission = 1 ;
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.ptr_receive_buffer = receive_buffer;
	NR905_SPI_Properties.size_of_receive = 2;
	SPI_Transmit_Receive_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status != osEventTimeout)
	{
		tx_size = receive_buffer[1];
	}
	return tx_size;

}


uint16_t NRF905_Get_Rx_Size(void)
{
	uint16_t rx_size = 0;
	osEvent evt;
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	uint8_t receive_buffer[SIZE_OF_RECEIVE_BUFFER] = {0};

	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_R_WRP;
	transmission_buffer[1] =  0;
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.size_of_transmission = 1 ;
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.ptr_receive_buffer = receive_buffer;
	NR905_SPI_Properties.size_of_receive = 2;
	SPI_Transmit_Receive_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status != osEventTimeout)
	{
		rx_size = receive_buffer[1];
	}
	return rx_size;

}

uint32_t NRF905_Get_Tx_Addr(void)
{
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	uint8_t receive_buffer[SIZE_OF_RECEIVE_BUFFER] = {0};
	uint32_t tx_addr = 0;
	osEvent evt;
	uint8_t i;
	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_RTA;
	transmission_buffer[1] =  0;
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.size_of_transmission = 1 ;
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.ptr_receive_buffer = receive_buffer;
	NR905_SPI_Properties.size_of_receive = 5;
	SPI_Transmit_Receive_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status != osEventTimeout)
	{
		for(i = 0 ; i < 4; i++)
		{
			tx_addr <<=8;
			tx_addr |= receive_buffer[i+1];
		}
	}
	return tx_addr;
}

uint32_t NRF905_Get_Rx_Addr(void)
{

	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	uint8_t receive_buffer[SIZE_OF_RECEIVE_BUFFER] = {0};
	uint32_t rx_addr = 0;
	osEvent evt;
	uint8_t i;

	NRF905_Set_Operation_Mode(STANDBY_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_R_RA;
	transmission_buffer[1] =  0;
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.size_of_transmission = 1 ;
	NR905_SPI_Properties.ptr_receive_buffer = receive_buffer;
	NR905_SPI_Properties.size_of_receive = 5;
	SPI_Transmit_Receive_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status != osEventTimeout)
	{
		for(i = 0 ; i < 4; i++)
		{
			rx_addr <<=8;
			rx_addr |= receive_buffer[i+1];
		}
	}
	return rx_addr;
}

void NRF905_Set_Operation_Mode(NRF905_OperationMode operation_mode)
{
	switch(operation_mode)
	{
	case STANDBY_AND_SPI_PROGRAMMING:
		GPIO_Change_Pin_State(NORDIC_PWR_UP_GPIO_Port, NORDIC_PWR_UP_Pin, GPIO_PIN_SET);
		GPIO_Change_Pin_State(NORDIC_TRX_CE_GPIO_Port,NORDIC_TRX_CE_Pin , GPIO_PIN_RESET);
		break;

	case READ_DATA_FROM_RX_REGISTER:
		GPIO_Change_Pin_State(NORDIC_PWR_UP_GPIO_Port, NORDIC_PWR_UP_Pin, GPIO_PIN_SET);
		GPIO_Change_Pin_State(NORDIC_TX_EN_GPIO_Port, NORDIC_TX_EN_Pin, GPIO_PIN_RESET);
		break;

	case RADIO_ENABLED_SHOCKBURST_RX:
		GPIO_Change_Pin_State(NORDIC_PWR_UP_GPIO_Port, NORDIC_PWR_UP_Pin, GPIO_PIN_SET);
		GPIO_Change_Pin_State(NORDIC_TRX_CE_GPIO_Port,NORDIC_TRX_CE_Pin, GPIO_PIN_SET);
		GPIO_Change_Pin_State(NORDIC_TX_EN_GPIO_Port, NORDIC_TX_EN_Pin, GPIO_PIN_RESET);
		break;

	case RADIO_ENABLED_SHOCKBURST_TX:
		GPIO_Change_Pin_State(NORDIC_PWR_UP_GPIO_Port, NORDIC_PWR_UP_Pin, GPIO_PIN_SET);
		GPIO_Change_Pin_State(NORDIC_TRX_CE_GPIO_Port,NORDIC_TRX_CE_Pin, GPIO_PIN_SET);
		GPIO_Change_Pin_State(NORDIC_TX_EN_GPIO_Port, NORDIC_TX_EN_Pin, GPIO_PIN_SET);
		break;

	case POWER_DOWN_AND_SPI_PROGRAMMING:
	default:
		GPIO_Change_Pin_State(NORDIC_PWR_UP_GPIO_Port, NORDIC_PWR_UP_Pin, GPIO_PIN_RESET);
		GPIO_Change_Pin_State(NORDIC_TX_EN_GPIO_Port, NORDIC_TX_EN_Pin, GPIO_PIN_RESET);
		GPIO_Change_Pin_State(NORDIC_TX_EN_GPIO_Port, NORDIC_TX_EN_Pin, GPIO_PIN_RESET);
		break;
	}
	osDelay(1);
	if(Old_Operation_Mode == POWER_DOWN_AND_SPI_PROGRAMMING)
	{
		osDelay(3);
	}
	Old_Operation_Mode = operation_mode;
}


uint8_t NRF905_Check_Configuration(void)
{
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};
	uint8_t receive_buffer[SIZE_OF_RECEIVE_BUFFER] = {0};
	osEvent evt;
	uint8_t i ;
	uint8_t state = 0;
	uint8_t buffer_ok_count = 0;
	NRF905_Set_Operation_Mode(POWER_DOWN_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_RC;
	for(i = 0 ; i < SIZE_OF_CONFIGURATION_PAYLOAD+1; i++)
	{
		transmission_buffer[i+1] = 0;
	}
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.size_of_transmission = 1 ;
	NR905_SPI_Properties.ptr_receive_buffer = receive_buffer;
	NR905_SPI_Properties.size_of_receive = SIZE_OF_CONFIGURATION_PAYLOAD + 1;
	SPI_Transmit_Receive_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED|SPI_RX_COMPLETED,100);
	SPI_Release_Bus(&NR905_SPI_Properties);
	if(evt.status == osEventTimeout)
	{
		state =  0;
	}
	else
	{
		for(i = 0; i <SIZE_OF_CONFIGURATION_PAYLOAD; i++)
		{
			if(receive_buffer[i+1] == NRF905_Configuration_Payload[i])
			{
				buffer_ok_count++;
			}
		}
		if(buffer_ok_count == SIZE_OF_CONFIGURATION_PAYLOAD)
		{
			state = 1;
		}
	}
	return state;
}

uint8_t NRF905_Send_Configuration(void)
{
	osEvent evt;
	uint8_t i ;
	uint8_t state = 0;

	GPIO_Change_Pin_State(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_SET);
	uint8_t transmission_buffer[SIZE_OF_TRANSMISSION_BUFFER] = {0};

	NRF905_Set_Operation_Mode(POWER_DOWN_AND_SPI_PROGRAMMING);
	transmission_buffer[0] = NRF905_WC;
	for(i = 0; i <SIZE_OF_CONFIGURATION_PAYLOAD; i ++)
	{
		transmission_buffer[i + 1] = NRF905_Configuration_Payload[i];
	}
	SPI_Get_Bus(&NR905_SPI_Properties);
	NR905_SPI_Properties.ptr_transmit_buffer = transmission_buffer;
	NR905_SPI_Properties.size_of_transmission = SIZE_OF_CONFIGURATION_PAYLOAD + 1;
	SPI_Write_Data(&NR905_SPI_Properties);
	evt = osSignalWait(SPI_TX_COMPLETED,100);
	if(evt.status == osEventTimeout)
	{
		state =  0;
	}
	else
	{
		state =  1;
	}
	SPI_Release_Bus(&NR905_SPI_Properties);
	GPIO_Change_Pin_State(LED_VD_GPIO_Port, LED_VD_Pin, GPIO_PIN_RESET);
	return state;
}




void NRF905_Select_Chip(void)
{
	GPIO_Change_Pin_State(NORDIC_CS_GPIO_Port, NORDIC_CS_Pin, GPIO_PIN_RESET);
}

void NRF905_Deselect_Chip(void)
{
	GPIO_Change_Pin_State(NORDIC_CS_GPIO_Port, NORDIC_CS_Pin, GPIO_PIN_SET);
}

static void Wait_For_Transmission(void)
{
	GPIO_EnableIRQ(NORDIC_DR_Pin);
	osSignalWait(NORDIC_DR_SIGNAL,osWaitForever);
	GPIO_DisableIRQ(NORDIC_DR_Pin);
}

static void Wait_Reception(void)
{
	GPIO_EnableIRQ(NORDIC_DR_Pin);
	osSignalWait(NORDIC_DR_SIGNAL,osWaitForever);
	GPIO_DisableIRQ(NORDIC_DR_Pin);
}

static uint8_t* Addr_to_Buffer(uint32_t addr)
{
	int8_t i;
	for(i =3; i >= 0; i--)
	{
		data_buffer[i] = (addr>>24);
		addr<<=8;
	}
	return data_buffer;
}

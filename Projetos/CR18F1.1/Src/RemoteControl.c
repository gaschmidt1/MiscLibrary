/*
 * RemoteControl.c
 *
 *  Created on: Aug 27, 2019
 *      Author: gerry
 */

#include "main.h"
#include "NRF905.h"
#include "MyTypes.h"
#include "RemoteControl.h"

//uint32_t AddressEndian(uint32_t addr)
//{
//	int8_t i;
//	u32t ret;
//
//	for(i =3; i >= 0; i--)
//	{
//		ret.u8v[i] = (addr>>24);
//		addr<<=8;
//	}
//	return(ret.u32v);
//}

void RemoteControlInit(void)
{
	u32t Address;

	if (IsInputsInConfigMode() == 1)
	{
		nRf905SetTxAddr(nRfAddressConfig);
		nRf905SetRxAddr(nRfAddressConfig);
	}
	else
	{
		Address.u32v = FlashReadU32(kRemoteControlTxAdress);
		nRf905SetTxAddr(Address.u32v);

		Address.u32v = FlashReadU32(kRemoteControlRxAdress);
		nRf905SetRxAddr(Address.u32v);
	}

	nRf905SetTxBufferLenght(4);
	nRf905SetRxBufferLenght(4);

	while (IsInputsInConfigMode() == 1)
	{
		Nrf905SetMode(eReadDataFromRxMode);//(eReceiveShockBurstMode);

		//HAL_GPIO_TogglePin(McuLed1_GPIO_Port, McuLed1_Pin);
		//HAL_GPIO_WritePin(McuLed2_GPIO_Port, McuLed2_Pin, GPIO_PIN_RESET);

		if (Nrf905GetDr() == 1)
		{
			nRf905ReceivePacket(Address.u8v, 4);

			nRf905SetTxAddr(Address.u32v | nRfAddressRxOffset);
			FlashWriteU32(kRemoteControlTxAdress, Address.u32v | nRfAddressRxOffset);

			nRf905SetRxAddr(Address.u32v);
			FlashWriteU32(kRemoteControlRxAdress, Address.u32v);
			break;
		}

		HAL_Delay(25);
	}
}

void RemoteControlConfigCallback(uint8_t Index, InputNameType Input, uint32_t KeyValue)
{
	RemoteControlVector[Index].Input = Input;
	RemoteControlVector[Index].KeyValue = KeyValue;
}

void RemoteControlConfigProcessRF(void)
{
	RemoteControlConfigCallback(0, In01, kSw01);
	RemoteControlConfigCallback(1, In02, kSw02);
	RemoteControlConfigCallback(2, In03, kSw03);
	RemoteControlConfigCallback(3, In04, kSw04);

	RemoteControlConfigCallback(4, In05, kSw05);
	RemoteControlConfigCallback(5, In06, kSw06);
	RemoteControlConfigCallback(6, In07, kSw07);
	RemoteControlConfigCallback(7, In08, kSw08);

	RemoteControlConfigCallback(8, In09, kSw09);
	RemoteControlConfigCallback(9, In10, kSw10);
	RemoteControlConfigCallback(10, In11, kSw11);
	RemoteControlConfigCallback(11, In12, kSw12);

	RemoteControlConfigCallback(12, In13, kSw13);
	RemoteControlConfigCallback(13, In14, kSw14);
	RemoteControlConfigCallback(14, In15, kSw15);
	RemoteControlConfigCallback(15, In16, kSw16);

	RemoteControlConfigCallback(16, In17, kSw17);
	RemoteControlConfigCallback(17, In18, kSw18);
}

void RemoteControlPeriodic(InputNameType Input)
{
	uint8_t i = 0;
	u32t Slice;
	Slice.u32v = RemoteControlVector[i].KeyValue;

	for (i = 0; i < kRemoteControlCommands; i++)
	{
		if (RemoteControlVector[i].Input == Input)
		{
			nRf905SendPacket(Slice.u8v, 4);
			break;
		}
	}
}


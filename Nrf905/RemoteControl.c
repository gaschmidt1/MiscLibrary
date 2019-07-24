/*
 * RemoteControl.c
 *
 *  Created on: 4 de jun de 2019
 *      Author: gerry
 */

#include "stm32f0xx_ll_utils.h"
#include "cmsis_os.h"
#include "RemoteControl.h"
#include "MyTypes.h"
#include "fifo.h"

/******************************************************************************/
/**
 * @brief Simple routine for init and preconnfigure a nRf905
 *
 */
void RemoteControlInit(void)
{
	u32t RemoteControlRxAddress, RemoteControlTxAddress;

	nRf905SetConfig();
	RemoteControlTxAddress.u32v = LL_GetUID_Word0();
	RemoteControlRxAddress.u32v = LL_GetUID_Word0();
	nRf905SetTxAddr(RemoteControlTxAddress.u32v + 0x8000U);
	nRf905SetRxAddr(RemoteControlRxAddress.u32v);
	nrf905SetTxBufferLenght(nRf905TxBufferlenght);
	nrf905SetRxBufferLenght(nRf905RxBufferlenght);
}

/******************************************************************************/
/**
 * @brief Simple routine for a pair two nRf905
 *
 */
void RemoteControlConfigAddress(void)
{
	int32_t xAttWakeTime = osKernelSysTick();
	int32_t xLastWakeTime = (xAttWakeTime + nRf905TimeToConnect);
	u32t RemoteControlRxAddress, RemoteControlTxAddress;

	RemoteControlTxAddress.u32v = nRf905AddressConfig;
	RemoteControlRxAddress.u32v = LL_GetUID_Word0();

	nRf905SetConfig();
	nRf905SetTxAddr(RemoteControlTxAddress.u32v);
	nRf905SetRxAddr(RemoteControlRxAddress.u32v);

	nrf905SetTxBufferLenght(nRf905TxBufferlenght);
	nrf905SetRxBufferLenght(nRf905RxBufferlenght);

	while((Nrf905GetDr() == 0U) || (xLastWakeTime > xAttWakeTime))
	{
		xAttWakeTime = osKernelSysTick();
		nRf905SendPacket(RemoteControlRxAddress.u8v, nRf905TxBufferlenght);
		osDelay(25);
	}

	if(Nrf905GetDr() == 1U)
	{
		nRf905SetTxAddr(RemoteControlRxAddress.u32v + 0x8000u);
		nRf905SetRxAddr(RemoteControlRxAddress.u32v);
		//nrf905SetTxBufferLenght(nRf905TxBufferlenght);
		//nrf905SetRxBufferLenght(nRf905RxBufferlenght);
	}

	nrf905SetTxBufferLenght(nRf905TxBufferlenght);
	nrf905SetRxBufferLenght(nRf905RxBufferlenght);
}

/******************************************************************************/
/**
 * @brief Simple routine for control a nrf905 data read pin off a nRf905 in polling mode
 *
 */
void RemoteControlPeriodic(void)
{
	uint8_t RemoteControlRxBuffer[nRf905RxBufferlenght], i;

	if(Nrf905GetDr() == 1)
	{
		nRf905ReceivePacket(RemoteControlRxBuffer, nRf905RxBufferlenght);

		for(i = 0; i < 4; i++)
		{
			fifo_queue(&RemoteControlQueue, RemoteControlRxBuffer[i]);
		}
	}
}

/******************************************************************************/
/**
 * @brief Simple routine for control a nrf905 data read pin off a nRf905 external interrupt mode
 *
 */
void RemoteControlDrCallBack(void)
{
	uint8_t RemoteControlRxBuffer[nRf905RxBufferlenght], i;

	nRf905ReceivePacket(RemoteControlRxBuffer, nRf905RxBufferlenght);

	for(i = 0; i < 4; i++)
	{
		fifo_queue(&RemoteControlQueue, RemoteControlRxBuffer[i]);
	}
}

/******************************************************************************/
/**
 * @brief Simple routine for Callback
 *
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	UNUSED(hspi);
}

/******************************************************************************/
/**
 * @brief Simple routine for Callback
 *
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(hspi == &hspi1)
	{

	}
}

/******************************************************************************/
/**
 * @brief Simple routine for Callback
 *
 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	UNUSED(hspi);
}



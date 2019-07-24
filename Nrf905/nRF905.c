/*
 * nRF905.c
 *
 *  Created on: 3 de jun de 2019
 *      Author: gerry
 */

#include <stdio.h>
#include <stdlib.h>
#include "cmsis_os.h"
#include "MyTypes.h"
#include "Nrf905.h"


uint8_t nRF905Config[10] = {

		nRfAt433_2MHz, //Byte0 CH_NO[7:0]
		PA_PWR_10dBm | HFREQ_PLL_433MHz | nRfAt433_2MHz >> 8, //Byte1 bit[7:6] not used, AUTO_RETRAN[], RX_RED_PWR[], PA_PWR[1:0], HFREQ_PLL, CH_NO[8]
		TX_AFW_4BYTE | RX_AFW_4BYTE, //Byte2 bit[7] not used, TX_AFW[2:0], bit[3] not used, RX_AFW[2:0]
		RX_PW_4BYTE, //Byte3 bit[7:6] not used, RX_PW[5:0]
		TX_PW_4BYTE, //Byte4 bit[7:6] not used, TX_PW[5:0]
		0x00, //Byte5 RX_ADDRESS byte 0
		0x00, //Byte6 RX_ADDRESS byte 1
		0x00, //Byte7 RX_ADDRESS byte 2
		0x00, //Byte8 RX_ADDRESS byte 3
		CRC16_EN | XOF_4MHz
};

HAL_StatusTypeDef nRf905WriteSpi(uint8_t* TxSpiBuffer, uint32_t Size);
HAL_StatusTypeDef nRf905ReadSpi(uint8_t* RxSpiBuffer, uint32_t Size);
HAL_StatusTypeDef nRf905Exchange(uint8_t* TxSpiBuffer, uint8_t* RxSpiBuffer, uint32_t Size);
void Nrf905SetMode(nRF905ModeType nRF905ModeMode);

/******************************************************************************/
/**
 * @brief Simple function for write in SPI
 *
 * @param  TxSpiBuffer				A pointer to vector write
 * @param  Size						A size of a vector
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905WriteSpi(uint8_t* TxSpiBuffer, uint32_t Size)
{
	HAL_StatusTypeDef RetValue = HAL_ERROR;
	if(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
	{
		RetValue = HAL_SPI_Transmit(&hspi1, TxSpiBuffer, Size, 10);
	}
	return(RetValue);
}

/******************************************************************************/
/**
 * @brief Simple function for read in SPI
 *
 * @param  RxSpiBuffer				A pointer to vector write
 * @param  Size						A size of a vector
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905ReadSpi(uint8_t* RxSpiBuffer, uint32_t Size)
{
	HAL_StatusTypeDef RetValue = HAL_ERROR;
	if(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
	{
		RetValue = HAL_SPI_Receive(&hspi1, RxSpiBuffer, Size, 10);
	}
	return(RetValue);
}

/******************************************************************************/
/**
 * @brief Simple function for read and write in SPI
 *
 * @param  TxSpiBuffer				A pointer to vector write
 * @param  RxSpiBuffer				A pointer to vector write
 * @param  Size						A size of a vector
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905Exchange(uint8_t* TxSpiBuffer, uint8_t* RxSpiBuffer, uint32_t Size)
{
	HAL_StatusTypeDef RetValue = HAL_ERROR;
	if(HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_READY)
	{
		RetValue = HAL_SPI_TransmitReceive(&hspi1, TxSpiBuffer, RxSpiBuffer, Size, 10);
	}
	return(RetValue);
}

/******************************************************************************/
/**
 * @brief Simple function to control a power state off a nFR905
 * @param  nRF905ModeMode			A enumeration status
 */
void Nrf905SetMode(nRF905ModeType nRF905ModeMode)
{
	switch(nRF905ModeMode)
	{
	case ePdMode:
		Nrf905ResetPwrUp();
		Nrf905ResetTxEn();
		Nrf905ResetTRxCe();
		break;
	case ePuMode:
		Nrf905SetPwrUp();
		Nrf905ResetTxEn();
		Nrf905ResetTRxCe();
		break;
	case eSbMode:
		Nrf905SetPwrUp();
		Nrf905ResetTxEn();
		Nrf905ResetTRxCe();
		break;
	case eRxMode:
		Nrf905SetPwrUp();
		Nrf905SetTxEn();
		Nrf905ResetTRxCe();
		break;
	case eTxMode:
		Nrf905SetPwrUp();
		Nrf905SetTxEn();
		Nrf905SetTRxCe();
		break;
	default:
		Nrf905ResetPwrUp();
		Nrf905ResetTxEn();
		Nrf905ResetTRxCe();
		break;
	}
	osDelay(5);
}

/******************************************************************************/
/**
 * @brief Simple function for write a vector nRFconfig in a device
 *
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905SetConfig(void)
{
	Nrf905SetCs();
	Nrf905SetMode(eSbMode);
	osDelay(3);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eWcRegister, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905WriteSpi(nRF905Config, 10) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for read a config from the device
 *
 * @param  aSpiBuffer			    A pointer to vector configuration storage
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905GetConfig(uint8_t* aSpiBuffer)
{
	uint8_t i;

	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eRcRegister, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905ReadSpi(aSpiBuffer, 10)  != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();

	for(i = 0; i < 10; i++)
	{
		if(aSpiBuffer[i] != nRF905Config[i])
		{
			return(HAL_ERROR);
		}
	}
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for write in payload and TX
 *
 * @param  aSpiBuffer				A pointer to vector to tx
 * @param  Size						A size of a vector
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905SendPacket(uint8_t* aSpiBuffer, uint8_t Size)
{
	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eWtpRegister, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905WriteSpi(aSpiBuffer, Size) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	while(Nrf905GetCd() == 1)
	{
		osDelay(rand() % 16);
	}
	Nrf905SetMode(eTxMode);
	while(Nrf905GetCd() == 0)
	{
		osDelay(1);
	}
	Nrf905SetMode(eRxMode);
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for read payload of device
 *
 * @param  aSpiBuffer				A pointer to vector to rx
 * @param  Size						A size of a vector
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905ReceivePacket(uint8_t* aSpiBuffer, uint8_t Size)
{
	Nrf905SetMode(eRxMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eRrpRegister, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905ReadSpi(aSpiBuffer, Size) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for write a transmission address
 *
 * @param  nRf905Address			A 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905SetTxAddr(uint32_t nRf905Address)
{
	u32t nRf905Slice;

	nRf905Slice.u32v = nRf905Address;
	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eWtaRegister, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905WriteSpi( nRf905Slice.u8v, 4) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for write a transmission address
 *
 * @param  nRf905Address			A 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905GetTxAddr(uint32_t* nRf905Address)
{
	u32t nRf905Slice;

	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eRtaRegister, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905ReadSpi(nRf905Slice.u8v, 4) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	*nRf905Address = nRf905Slice.u32v;
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for write a receive address
 *
 * @param  nRf905Address			A 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905SetRxAddr(uint32_t nRf905Address)
{
	u32t nRf905Slice;

	nRf905Slice.u32v = nRf905Address;
	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eWcRegister5, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905WriteSpi(nRf905Slice.u8v, 4) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for read a receive address
 *
 * @param  nRf905Address			A pointer to read of 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905GetRxAddr(uint32_t* nRf905Address)
{
	u32t nRf905Slice;

	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eRcRegister5, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905ReadSpi(nRf905Slice.u8v, 4) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	*nRf905Address = nRf905Slice.u32v;
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for read a receive address
 *
 * @param  nRf905Address			A pointer to read of 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nrf905SetTxBufferLenght(uint8_t nrF905Lenght)
{
	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eWcRegister4, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905WriteSpi(&nrF905Lenght, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for read a Lenght of tx
 *
 * @param  nRf905Address			A pointer to read of 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905GetTxBufferLenght(uint8_t* nRf905Lenght)
{
	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eRcRegister4, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905ReadSpi(nRf905Lenght, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	*nRf905Lenght &= 0x3F;
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function for Set a Lenght of rx
 *
 * @param  nRf905Address			A pointer to read of 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nrf905SetRxBufferLenght(uint8_t nrF905Lenght)
{
	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eWcRegister3, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905WriteSpi(&nrF905Lenght, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	return(HAL_OK);
}


/******************************************************************************/
/**
 * @brief Simple function to get a Lenght of rx
 *
 * @param  nRf905Address			A pointer to read of 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905GetRxBufferLenght(uint8_t* nRf905Lenght)
{
	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905WriteSpi((uint8_t*)eRcRegister3, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	if(nRf905ReadSpi(nRf905Lenght, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	*nRf905Lenght &= 0x3F;
	return(HAL_OK);
}

/******************************************************************************/
/**
 * @brief Simple function to read a status
 *
 * @param  nRf905Address			A pointer to read a status
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905GetStatusRegister(uint8_t* nRf905Status)
{
	uint8_t RetValue;

	Nrf905SetMode(eSbMode);
	Nrf905ResetCs();
	if(nRf905Exchange((uint8_t*)eRcRegister, &RetValue, 1) != HAL_OK)
	{
		return(HAL_ERROR);
	}
	Nrf905SetCs();
	return(HAL_OK);
}



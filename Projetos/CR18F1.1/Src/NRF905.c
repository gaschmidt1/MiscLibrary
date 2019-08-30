/*
 * nRF905.c
 *
 *  Created on: 3 de jun de 2019
 *      Author: gerry
 */

#include <stdio.h>
#include <stdlib.h>
#include "MyTypes.h"
#include "Nrf905.h"

/******************************************************************************/
/**
 * @brief Simple function to control a power state off a nFR905
 * @param  nRF905ModeMode			A enumeration status
 */
void Nrf905SetMode(nRF905ModeType nRF905ModeMode)
{
	switch (nRF905ModeMode)
	{
	case ePowerDownAndProgramingMode:
		Nrf905ResetPwrUp();
		Nrf905ResetTRxCe();
		Nrf905ResetTxEn();
		break;
	case eReadDataFromRxMode:
		Nrf905SetPwrUp();
		Nrf905ResetTRxCe();
		Nrf905ResetTxEn();
		break;
	case eStandByAndProgramingMode:
		Nrf905SetPwrUp();
		Nrf905ResetTRxCe();
		Nrf905ResetTxEn();
		break;
	case eReceiveShockBurstMode:
		Nrf905SetPwrUp();
		Nrf905SetTRxCe();
		Nrf905ResetTxEn();
		break;
	case eTrasmitShockBurstMode:
		Nrf905SetPwrUp();
		Nrf905SetTRxCe();
		Nrf905SetTxEn();
		break;
	default:
		Nrf905ResetPwrUp();
		Nrf905ResetTRxCe();
		Nrf905ResetTxEn();
		break;
	}
	HAL_Delay(5);
}

/******************************************************************************/
/**
 * @brief Simple function for write a vector nRFconfig in a device
 *
 * @return RetValue 				A status error
 */

HAL_StatusTypeDef nRf905SetConfig(void)
{
	nRF905Cfg_t nRF905Config;
	nRF905Cfg_t nRF905Check;

	uint8_t i;

	nRF905Config.Fields.Command = eWriteConfigRegister;

	nRF905Config.Fields.CH_NO0 = (uint8_t) (nRfAt433_2MHz & 0x0FF);

	nRF905Config.Fields.UNUSED1 = 0;
	nRF905Config.Fields.AUTO_RETRANS = AUTO_RETRAN_DIS;
	nRF905Config.Fields.RX_RED_PWR = RX_NORM_PWR;
	nRF905Config.Fields.PA_PWR = PA_PWR_10PdBm;
	nRF905Config.Fields.HFREQ_PLL = HFREQ_PLL_433MHz;
	nRF905Config.Fields.CH_NO1 = (uint8_t) ((nRfAt433_2MHz & 0x100) >> 8);

	nRF905Config.Fields.UNUSED2 = 0;
	nRF905Config.Fields.TX_AFW = 4;

	nRF905Config.Fields.UNUSED3 = 0;
	nRF905Config.Fields.RX_AFW = 4;

	nRF905Config.Fields.UNUSED4 = 0;
	nRF905Config.Fields.RX_PW = 4;

	nRF905Config.Fields.UNUSED5 = 0;
	nRF905Config.Fields.TX_PW = 4;

	nRF905Config.Fields.RX_ADDRESS0 = 0xFF;
	nRF905Config.Fields.RX_ADDRESS1 = 0xFF;
	nRF905Config.Fields.RX_ADDRESS2 = 0xFF;
	nRF905Config.Fields.RX_ADDRESS3 = 0xFF;

	nRF905Config.Fields.CRC_MODE = CRC_MODE_16BIT;
	nRF905Config.Fields.CRC_ENA = CRC_ENABLE;
	nRF905Config.Fields.XOF = XOF_4MHz;
	nRF905Config.Fields.UP_CLK_ENA = UP_CLK_DIS;
	nRF905Config.Fields.UP_CLK_FREQ = UP_CLK_FREQ_1MHz;

	HAL_StatusTypeDef ret = HAL_OK;

	/* select power down mode */
	Nrf905SetMode(ePowerDownAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	/* send a command and configuration packet*/
	if (HAL_SPI_Transmit(&hspi1, nRF905Config.u8v, 11, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	Nrf905SetCs();
	HAL_Delay(5);
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);

	/* test if configuration is successful */
	if (ret == HAL_OK)
	{
		/* read info set up */
		nRF905Check.Fields.Command = eReadConfigRegister;

		Nrf905SetMode(ePowerDownAndProgramingMode);
		HAL_Delay(5);
		Nrf905ResetCs();
		HAL_Delay(5);

		if (HAL_SPI_Transmit(&hspi1, nRF905Check.u8v, 1, 1000) != HAL_OK)
		{
			ret = HAL_ERROR;
		}

		else if (HAL_SPI_Receive(&hspi1, nRF905Check.u8v, 10, 1000) != HAL_OK)
		{
			ret = HAL_ERROR;
		}

		/* select stand by mode */
		Nrf905SetCs();
		HAL_Delay(5);
		Nrf905SetMode(eStandByAndProgramingMode);
		HAL_Delay(5);
	}
	/* test if read is successful */
	if (ret == HAL_OK)
	{
		/* test is nRF905 is correct set up */
		for (i = 0; i < 10; i++)
		{
			if (nRF905Config.Bytes.Check[i] != nRF905Check.u8v[i])
			{
				ret = HAL_ERROR;
			}
		}
	}
	return (ret);
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
	nRF905Address_t nRF905Buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	/* tx address write mode */
	nRF905Buffer.Command = eWriteTxAddressRegister;
	nRF905Buffer.Address.u32v = nRf905Address;

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	/* write a address */
	if (HAL_SPI_Transmit(&hspi1, nRF905Buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	if (HAL_SPI_Transmit(&hspi1, nRF905Buffer.Address.u8v, 4, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();
	return (ret);
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
	nRF905Address_t nRF905Buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	/* tx address read mode */
	nRF905Buffer.Command = eReadTxAddressRegister;

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	if (HAL_SPI_Transmit(&hspi1, nRF905Buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	/* read a address */
	else if (HAL_SPI_Receive(&hspi1, nRF905Buffer.Address.u8v, 4, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();

	/* transfer to buffer output */
	*nRf905Address = nRF905Buffer.Address.u32v;
	return (ret);
}

/******************************************************************************/
/**
 * @brief Simple function for write a receiver address
 *
 * @param  nRf905Address			A 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905SetRxAddr(uint32_t nRf905Address)
{
	nRF905Address_t nRF905Buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	/* rx address write mode */
	nRF905Buffer.Command = eWriteConfigRegister5;
	nRF905Buffer.Address.u32v = nRf905Address;

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	/* write a address */
	if (HAL_SPI_Transmit(&hspi1, nRF905Buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	if (HAL_SPI_Transmit(&hspi1, nRF905Buffer.Address.u8v, 4, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();
	return (ret);
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
	nRF905Address_t nRF905Buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	/* rx address read mode */
	nRF905Buffer.Command = eReadConfigRegister5;

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	if (HAL_SPI_Transmit(&hspi1, nRF905Buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	/* read a address */
	else if (HAL_SPI_Receive(&hspi1, nRF905Buffer.Address.u8v, 4, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();

	/* transfer to buffer output */
	*nRf905Address = nRF905Buffer.Address.u32v;
	return (ret);
}

/******************************************************************************/
/**
 * @brief Simple function for read a receive address
 *
 * @param  nRf905Address		 a 8 bit Lenght
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905SetTxBufferLenght(uint8_t nrF905Lenght)
{
	nRF905Lenght_t nRF905buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	/* write lenght of tx buffer */
	nRF905buffer.Command = eWriteConfigRegister4;
	nRF905buffer.Lenght.u8v = nrF905Lenght;

	if (HAL_SPI_Transmit(&hspi1, nRF905buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	if (HAL_SPI_Transmit(&hspi1, &nRF905buffer.Lenght.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();
	return (ret);
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
	nRF905Lenght_t nRF905buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	/* read lenght of tx buffer */
	nRF905buffer.Command = eReadConfigRegister4;

	if (HAL_SPI_Transmit(&hspi1, nRF905buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	else if (HAL_SPI_Receive(&hspi1, &nRF905buffer.Lenght.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();

	/* transfer to buffer output */
	*nRf905Lenght = nRF905buffer.Lenght.u8v;

	return (ret);
}

/******************************************************************************/
/**
 * @brief Simple function for Set a Lenght of rx
 *
 * @param  nRf905Address			A pointer to read of 32 bit address
 * @return RetValue 				A status error
 */
HAL_StatusTypeDef nRf905SetRxBufferLenght(uint8_t nrF905Lenght)
{
	nRF905Lenght_t nRF905buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	/* write lenght of rx buffer */
	nRF905buffer.Command = eWriteConfigRegister3;
	nRF905buffer.Lenght.u8v = nrF905Lenght;

	if (HAL_SPI_Transmit(&hspi1, nRF905buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	if (HAL_SPI_Transmit(&hspi1, &nRF905buffer.Lenght.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();
	return (ret);
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
	nRF905Lenght_t nRF905buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	/* read lenght of rx buffer */
	nRF905buffer.Command = eReadConfigRegister3;

	if (HAL_SPI_Transmit(&hspi1, nRF905buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	else if (HAL_SPI_Receive(&hspi1, &nRF905buffer.Lenght.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* select stand by mode */
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();

	/* transfer to buffer output */
	*nRf905Lenght = nRF905buffer.Lenght.u8v;

	return (ret);
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
	nRF905Payload_t nRF905buffer;

	HAL_StatusTypeDef ret = HAL_OK;

	uint8_t i;

	if (Size > 32)
	{
		return (HAL_ERROR);
	}

	/* load the tx buffer */
	nRF905buffer.Payload.Command = eWriteTxPayloadRegister;

	for (i = 0; i < Size; i++)
	{
		nRF905buffer.Payload.Data[i] = *aSpiBuffer++;
	}

	/* select stand by mode */
	Nrf905SetCs();
	HAL_Delay(5);
	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905ResetCs();

	/* load the nRF905 payload */
	if (HAL_SPI_Transmit(&hspi1, nRF905buffer.u8v, (Size + 1), 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* wait the payload transfer */
	while (Nrf905GetCd() == 1)
	{
		HAL_Delay(rand() % 8);
	}

	Nrf905SetMode(eTrasmitShockBurstMode);

	//HAL_Delay(100);

	/* wait the RF transfer */
	while (Nrf905GetDr() == 0)
	{
		HAL_Delay(5);
	}

	Nrf905SetMode(eStandByAndProgramingMode);

	return (ret);
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

	if (Size > 32)
	{
		return (HAL_ERROR);
	}

	nRF905Payload_t nRF905buffer;

	/* read a rx payload */
	Nrf905SetMode(eReceiveShockBurstMode);
	HAL_Delay(5);
	Nrf905ResetCs();
	HAL_Delay(5);

	nRF905buffer.Payload.Command = eReadRxPayloadRegister;

	HAL_StatusTypeDef ret = HAL_OK;

	uint8_t i;

	if (HAL_SPI_Transmit(&hspi1, nRF905buffer.u8v, 1, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	/* get a payload */
	else if (HAL_SPI_Receive(&hspi1, nRF905buffer.Payload.Data, Size, 1000) != HAL_OK)
	{
		ret = HAL_ERROR;
	}

	Nrf905SetMode(eStandByAndProgramingMode);
	HAL_Delay(5);
	Nrf905SetCs();

	/* transfer do buffer output */
	for (i = 0; i < Size; i++)
	{
		*aSpiBuffer++ = nRF905buffer.Payload.Data[i];
	}

	return (ret);
}


/*
 * nRf905.h
 *
 *  Created on: 3 de jun de 2019
 *      Author: gerry
 */

#ifndef INC_NRF905_H_
#define INC_NRF905_H_

#include "spi.h"
#include "main.h"
#include "MyTypes.h"

#define nRfAt430_0MHz  		0b001001100
#define nRfAt433_1MHz  		0b001101011
#define nRfAt433_2MHz  		0b001101100
#define nRfAt434_7MHz  		0b001111011

#define nRfAt862_0MHz  		0b001111011
#define nRfAt868_2MHz  		0b001110101
#define nRfAt868_4MHz  		0b001110110
#define nRfAt869_8MHz  		0b001111101

#define nRfAt902_2MHz  		0b100011111
#define nRfAt902_4MHz  		0b100100000
#define nRfAt927_8MHz  		0b110011111

#define HFREQ_PLL_433MHz    0b0
#define HFREQ_PLL_868MHz    0b1
#define HFREQ_PLL_915MHz    0b1

#define XOF_20MHz           0b100
#define XOF_16MHz           0b011
#define XOF_12MHz           0b010
#define XOF_8MHz            0b001
#define XOF_4MHz            0b000

#define RX_NORM_PWR  0x0
#define RX_ED_PWR          0x1

#define CRC_DISABLE 		0b0
#define CRC_ENABLE		0b1

#define CRC_MODE_16BIT      0b1
#define CRC_MODE_8BIT       0b0

#define PA_PWR_10MdBm       0b00
#define PA_PWR_2MdBm        0b01
#define PA_PWR_6PdBm        0b10
#define PA_PWR_10PdBm       0b11

#define AUTO_RETRAN_EN      0b0
#define AUTO_RETRAN_DIS     0b1

#define UP_CLK_DIS           0b0
#define UP_CLK_EN            0b1

#define UP_CLK_FREQ_500kHz   0b11
#define UP_CLK_FREQ_1MHz     0b10
#define UP_CLK_FREQ_2MHz     0x01
#define UP_CLK_FREQ_4MHz     0x00

#define Nrf905SetCs()		HAL_GPIO_WritePin(McuNordicCs_GPIO_Port, McuNordicCs_Pin, GPIO_PIN_SET)
#define Nrf905ResetCs()		HAL_GPIO_WritePin(McuNordicCs_GPIO_Port, McuNordicCs_Pin, GPIO_PIN_RESET)

#define Nrf905SetPwrUp()	HAL_GPIO_WritePin(McuNordicPwrUp_GPIO_Port, McuNordicPwrUp_Pin, GPIO_PIN_SET)
#define Nrf905ResetPwrUp()	HAL_GPIO_WritePin(McuNordicPwrUp_GPIO_Port, McuNordicPwrUp_Pin, GPIO_PIN_RESET)

#define Nrf905SetTxEn()		HAL_GPIO_WritePin(McuNordicTxEn_GPIO_Port, McuNordicTxEn_Pin, GPIO_PIN_SET)
#define Nrf905ResetTxEn()	HAL_GPIO_WritePin(McuNordicTxEn_GPIO_Port, McuNordicTxEn_Pin, GPIO_PIN_RESET)

#define Nrf905SetTRxCe()	HAL_GPIO_WritePin(McuNordicTrxCe_GPIO_Port, McuNordicTrxCe_Pin, GPIO_PIN_SET)
#define Nrf905ResetTRxCe()	HAL_GPIO_WritePin(McuNordicTrxCe_GPIO_Port, McuNordicTrxCe_Pin, GPIO_PIN_RESET)

#define Nrf905GetCd()		HAL_GPIO_ReadPin(McuNordicCd_GPIO_Port, McuNordicCd_Pin)

#define Nrf905GetDr()		HAL_GPIO_ReadPin(McuNordicDr_GPIO_Port, McuNordicDr_Pin)

typedef enum
{
	ePowerDownAndProgramingMode = 0x00, /*used for low power and config */
	eReadDataFromRxMode, /*used for normal config mode */
	eStandByAndProgramingMode, /*used */
	eReceiveShockBurstMode, /*used */
	eTrasmitShockBurstMode
} nRF905ModeType;

typedef enum
{
	eWriteConfigRegister = 0x00, /*Write Configuration Registers*/
	eWriteConfigRegister3 = 0x03, /*Write Configuration Registers*/
	eWriteConfigRegister4 = 0x04, /*Write Configuration Registers*/
	eWriteConfigRegister5 = 0x05, /*Write Configuration Registers*/

	eReadConfigRegister = 0x10, /*Read Configuration Registers*/
	eReadConfigRegister3 = 0x13, /*Read Configuration Registers*/
	eReadConfigRegister4 = 0x14, /*Read Configuration Registers*/
	eReadConfigRegister5 = 0x15, /*Read Configuration Registers*/

	eWriteTxPayloadRegister = 0x20, /*Write TX Payload*/
	eReadTxPayloadRegister = 0x21, /*Read TX Payload*/

	eWriteTxAddressRegister = 0x22, /*Write TX Address*/
	eReadTxAddressRegister = 0x23, /*Read TX Address*/

	eReadRxPayloadRegister = 0x24, /*Read RX Payload*/
//eCnlRegister = 0x80 /*Channel config cc*/
} nRF905CommandsType;

typedef union
{
	uint8_t u8v[11];

	struct
	{
		nRF905CommandsType Command;
		uint32_t CH_NO0 :8;
		uint32_t CH_NO1 :1;
		uint32_t HFREQ_PLL :1;
		uint32_t PA_PWR :2;
		uint32_t RX_RED_PWR :1;
		uint32_t AUTO_RETRANS :1;
		uint32_t UNUSED1 :2;
		uint32_t RX_AFW :3;
		uint32_t UNUSED3 :1;
		uint32_t TX_AFW :3;
		uint32_t UNUSED2 :1;
		uint32_t RX_PW :6;
		uint32_t UNUSED4 :2;
		uint32_t TX_PW :6;
		uint32_t UNUSED5 :2;
		uint32_t RX_ADDRESS0 :8;
		uint32_t RX_ADDRESS1 :8;
		uint32_t RX_ADDRESS2 :8;
		uint32_t RX_ADDRESS3 :8;
		uint8_t UP_CLK_FREQ :2;
		uint8_t UP_CLK_ENA :1;
		uint8_t XOF :3;
		uint8_t CRC_ENA :1;
		uint8_t CRC_MODE :1;
	} Fields;

	struct
	{
		nRF905CommandsType Command;
		uint8_t Check[10];
	} Bytes;
} nRF905Cfg_t;

typedef union
{
	nRF905CommandsType u8v[33];
	struct
	{
		uint8_t Command;
		uint8_t Data[32];
	} Payload;
} nRF905Payload_t;

typedef union
{
	uint8_t u8v[5];
	struct
	{
		nRF905CommandsType Command;
		u32t Address;
	};
} nRF905Address_t;

typedef union
{
	uint8_t u8v[2];
	struct
	{
		nRF905CommandsType Command;
		u8t Lenght;
	};
} nRF905Lenght_t;

//	uint8_t test[12] = {0x00, 0x6c, 0x0c, 0x44, 0x04, 0x04, 0x00, 0x12, 0x80, 0x21, 0xc0, 0x00};

void Nrf905SetMode(nRF905ModeType nRF905ModeMode);

HAL_StatusTypeDef nRf905SetConfig(void);

HAL_StatusTypeDef nRf905SendPacket(uint8_t* aSpiBuffer, uint8_t Size);
HAL_StatusTypeDef nRf905ReceivePacket(uint8_t* aSpiBuffer, uint8_t Size);

HAL_StatusTypeDef nRf905SetTxAddr(uint32_t nRf905Address);
HAL_StatusTypeDef nRf905GetTxAddr(uint32_t* nRf905Address);

HAL_StatusTypeDef nRf905SetRxAddr(uint32_t nRf905Address);
HAL_StatusTypeDef nRf905GetRxAddr(uint32_t* nRf905Address);

HAL_StatusTypeDef nRf905SetTxBufferLenght(uint8_t nRf905Lenght);
HAL_StatusTypeDef nRf905GetTxBufferLenght(uint8_t* nRf905Lenght);

HAL_StatusTypeDef nRf905SetRxBufferLenght(uint8_t nRf905Lenght);
HAL_StatusTypeDef nRf905GetRxBufferLenght(uint8_t* nRf905Lenght);

#endif /* INC_NRF905_H_ */

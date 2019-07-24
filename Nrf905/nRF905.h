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

#define nRfAddressConfig 65535

#define nRfAt422_4MHz  0x000
#define nRfAt422_5MHz  0x001
#define nRfAt425_0MHz  0x01A
#define nRfAt427_5MHz  0x033

#define nRfAt430_0MHz  0x04C
#define nRfAt433_0MHz  0x06A
#define nRfAt433_1MHz  0x06B
#define nRfAt433_2MHz  0x06C
#define nRfAt434_7MHz  0x07B
#define nRfAt473_5MHz  0x1FF

#define nRfAt844_8MHz  0x000

#define nRfAt862_0MHz  0x056
#define nRfAt868_0MHz  0x074
#define nRfAt868_2MHz  0x075
#define nRfAt868_4MHz  0x076
#define nRfAt869_8MHz  0x07d
#define nRfAt895_8MHz  0x0FF
#define nRfAt896_0MHz  0x100
#define nRfAt900_0MHz  0x114
#define nRfAt902_2MHz  0x11F
#define nRfAt902_4MHz  0x120
#define nRfAt915_0MHz  0x15F
#define nRfAt927_8MHz  0x19F

#define nRfAt947_0MHz  0x1FF

#define AUTO_RETRAN          0x20                      //            Byte1.5     0
#define RX_RED_PWR           0x10                      //g           Byte1.4     0
#define PA_PWR_10dBm         0x00                      //-10dBm      Byte1.3~2   00
#define PA_PWR_2dBm          0x04                      //+2dBm       Byte1.3~2
#define PA_PWR_6dBm          0x08                      //+6dBm       Byte1.3~2
//#define PA_PWR_10dBm         0x0C                      //+10dBm      Byte1.3~2
#define HFREQ_PLL_433MHz     0x00                      //433MHz      Byte1.1     0
#define HFREQ_PLL_868MHz     0x02                      //868MHz      Byte1.1
#define HFREQ_PLL_915MHz     0x02                      //915MHz      Byte1.1

#define TX_AFW_1BYTE         0x01*16                      //1        Byte2.7~4
#define TX_AFW_2BYTE         0x02*16                      //2        Byte2.7~4
#define TX_AFW_3BYTE         0x03*16                      //3        Byte2.7~4
#define TX_AFW_4BYTE         0x04*16                      //4        Byte2.7~4   100
#define RX_AFW_1BYTE         0x01                      //1           Byte2.3~0
#define RX_AFW_2BYTE         0x02                      //2           Byte2.3~0
#define RX_AFW_3BYTE         0x03                      //3           Byte2.3~0
#define RX_AFW_4BYTE         0x04                      //4           Byte2.3~0   100

#define RX_PW_4BYTE           4
#define TX_PW_4BYTE           4
#define RX_PW_32BYTE         32
#define TX_PW_32BYTE         32

#define CRC_MODE_16BIT       0x80                      //CRC16g            Byte9.7     1
#define CRC_MODE_8BIT        0x00                      //CRC8g             Byte9.7
#define CRC_EN               0x40                      //CRC'               Byte9.6     1
#define CRC16_EN             0xC0                      //CRC16g?'       Byte9.7~6   11
#define CRC8_EN              0x40                      //CRC8g?'         Byte9.7~6
#define XOF_20MHz            0x20                      //20MHz Byte9.5~3
#define XOF_16MHz            0x18                      //16MHz Byte9.5~3   100
#define XOF_12MHz            0x10                      //12MHz Byte9.5~3
#define XOF_8MHz             0x08                      //8MHz  Byte9.5~3
#define XOF_4MHz             0x00                      //4MHz  Byte9.5~3
#define UP_CLK_EN            0x40                      //        Byte9.2     1
#define UP_CLK_FREQ_500kHz   0x03                      //500kHz  Byte9.1~0   11
#define UP_CLK_FREQ_1MHz     0x02                      //1MHz    Byte9.1~0
#define UP_CLK_FREQ_2MHz     0x01                      //2MHz    Byte9.1~0
#define UP_CLK_FREQ_4MHz     0x00                      //4MHz    Byte9.1~0

#define UP_CLK_EN_500kHz     0x43                      //500kHz  Byte9.2~0   111
#define UP_CLK_EN_1MHz       0x42                      //1MHz    Byte9.2~0
#define UP_CLK_EN_2MHz       0x41                      //2MHz    Byte9.2~0
#define UP_CLK_EN_4MHz       0x40                      //4MHz    Byte9.2~0

#define Nrf905SetCs()		HAL_GPIO_WritePin(PinMcuNordicCs_GPIO_Port, PinMcuNordicCs_Pin, GPIO_PIN_SET)
#define Nrf905ResetCs()		HAL_GPIO_WritePin(PinMcuNordicCs_GPIO_Port, PinMcuNordicCs_Pin, GPIO_PIN_RESET)

#define Nrf905SetPwrUp()	HAL_GPIO_WritePin(PinMcuNordicPwrUp_GPIO_Port, PinMcuNordicPwrUp_Pin, GPIO_PIN_SET)
#define Nrf905ResetPwrUp()	HAL_GPIO_WritePin(PinMcuNordicPwrUp_GPIO_Port, PinMcuNordicPwrUp_Pin, GPIO_PIN_RESET)

#define Nrf905SetTxEn()		HAL_GPIO_WritePin(PinMcuRs485TxEn_GPIO_Port, PinMcuRs485TxEn_Pin, GPIO_PIN_SET)
#define Nrf905ResetTxEn()	HAL_GPIO_WritePin(PinMcuRs485TxEn_GPIO_Port, PinMcuRs485TxEn_Pin, GPIO_PIN_RESET)

#define Nrf905SetTRxCe()	HAL_GPIO_WritePin(PinMcuNordicTRxCe_GPIO_Port, PinMcuNordicTRxCe_Pin, GPIO_PIN_SET)
#define Nrf905ResetTRxCe()	HAL_GPIO_WritePin(PinMcuNordicTRxCe_GPIO_Port, PinMcuNordicTRxCe_Pin, GPIO_PIN_RESET)

#define Nrf905GetCd()		HAL_GPIO_ReadPin(PinMcuNordicCd_GPIO_Port, PinMcuNordicCd_Pin)

#define Nrf905GetDr()		HAL_GPIO_ReadPin(PinMcuNordicDr_GPIO_Port, PinMcuNordicDr_Pin)

typedef enum
{
	ePdMode = 0x00,
	ePuMode,
	eSbMode,
	eRxMode,
	eTxMode
}nRF905ModeType;

typedef enum
{
	eWcRegister  = 0x00,
	eWcRegister3 = 0x03,
	eWcRegister4 = 0x04,
	eWcRegister5 = 0x05,
	eRcRegister  = 0x10,
	eRcRegister3 = 0x13,
	eRcRegister4 = 0x14,
	eRcRegister5 = 0x15,
	eWtpRegister = 0x20,
	eRtpRegister = 0x21,
	eWtaRegister = 0x22,
	eRtaRegister = 0x23,
	eRrpRegister = 0x24,
	eCnlRegister = 0x80
}nRF905CommandsType;


HAL_StatusTypeDef nRf905SetConfig(void);
HAL_StatusTypeDef nRf905GetConfig(uint8_t* aSpiBuffer);
HAL_StatusTypeDef nRf905SendPacket(uint8_t* aSpiBuffer, uint8_t Size);
HAL_StatusTypeDef nRf905ReceivePacket(uint8_t* aSpiBuffer, uint8_t Size);
HAL_StatusTypeDef nRf905SetTxAddr(uint32_t nRf905Address);
HAL_StatusTypeDef nRf905GetTxAddr(uint32_t* nRf905Address);
HAL_StatusTypeDef nRf905SetRxAddr(uint32_t nRf905Address);
HAL_StatusTypeDef nRf905GetRxAddr(uint32_t* nRf905Address);
HAL_StatusTypeDef nrf905SetTxBufferLenght(uint8_t nRf905Lenght);
HAL_StatusTypeDef nRf905GetTxBufferLenght(uint8_t* nRf905Lenght);
HAL_StatusTypeDef nrf905SetRxBufferLenght(uint8_t nRf905Lenght);
HAL_StatusTypeDef nRf905GetRxBufferLenght(uint8_t* nRf905Lenght);
HAL_StatusTypeDef nRf905GetStatusRegister(uint8_t* nRf905Status);

#endif /* INC_NRF905_H_ */

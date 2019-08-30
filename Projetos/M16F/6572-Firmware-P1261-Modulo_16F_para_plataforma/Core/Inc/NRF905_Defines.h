/*
 * NRF905_Defines.h
 *
 *  Created on: 24 de jan de 2019
 *      Author: giovani
 */

#ifndef INC_NRF905_DEFINES_H_
#define INC_NRF905_DEFINES_H_



 #define NRF905_GENERAL_CONFIGURED_NUMBER   ((uint32_t) 0xFFFF0000)
    /*========================================================================*/

	/*========= DEFINITION OF INSTRUCTION SET COMMANDS TO SEND BY SPI ========*/
    #define NRF905_WC				((uint8_t) 0x00)	// Command to write configuration register starting from 0x00
	/*------------------------------------------------------------------------*/
    #define NRF905_W_WRP			((uint8_t) 0x03)	// Command to write width of the RX (PAYLOAD)
    #define NRF905_W_WTP			((uint8_t) 0x04)	// Command to write width of the TX (PAYLOAD)
    #define NRF905_W_RA				((uint8_t) 0x05)	// Command to write address of RX (ADDRESS)
	/*------------------------------------------------------------------------*/
    #define NRF905_RC				((uint8_t) 0x10)	// Command to read configuration register starting from 0x00
	/*------------------------------------------------------------------------*/
    #define NRF905_R_WRP			((uint8_t) 0x13)	// Command to read width of the RX (PAYLOAD)
    #define NRF905_R_WTP			((uint8_t) 0x14)	// Command to read width of the TX (PAYLOAD)
    #define NRF905_R_RA				((uint8_t) 0x15)	// Command to read address of RX (ADDRESS)
	/*------------------------------------------------------------------------*/
    #define NRF905_WTP				((uint8_t) 0x20)	// Command to write TX (PAYLOAD): 1 – 32 bytes. A write operation always starts at byte 0
    #define NRF905_RTP				((uint8_t) 0x21)	// Command to read TX (PAYLOAD): 1 – 32 bytes. A read operation always starts at byte 0
    #define NRF905_WTA				((uint8_t) 0x22)	// Command to write TX (ADDRESS): 1 – 4 bytes. A write operation always starts at byte 0
    #define NRF905_RTA				((uint8_t) 0x23)	// Command to read TX (ADDRESS): 1 – 4 bytes. A read operation always starst at byte 0
    #define NRF905_RRP				((uint8_t) 0x24)	// Command to read RX (PAYLOAD): 1 – 32 bytes. A read operation always starts at byte 0
    /*------------------------------------------------------------------------*/
    // Special command for fast setting of PA_PWR = pp (2 bits), HFREQ_PLL = h (1 bit) and CH_NO = ccccccccc (9 bits) in the CONFIGURATION REGISTER (1000pphc cccccccc)
    #define NRF905_CC				((uint16_t) 0x8C6A)	// PA_PWR = 0x03 (+10 dBm), HFREQ_PLL = 0 (433 MHz band) e CH_NO = 0x6A (433,0 MHz)
    /*========================================================================*/

    /*= DEFINITION OF THE CALCULATION OF CHANNEL ACCORDING REQUEST FREQUENCY =*/
    #define NRF905_CALC_CHANNEL(Frequency, HFREQ_PLL)	((uint16_t) (((((uint32_t) Frequency) / (1 + HFREQ_PLL)) - 422400000) / 100000))	// Calculating channel of the operation frequency = ((422,4 + (CH_NO / 10)) * (1 + HFREQ_PLL)) MHz
    /*========================================================================*/

	/*======== DEFINITION OF THE PLL MODE IN 433 OR 868 / 915MHz BAND ========*/
    #define NRF905_HFREQ_PLL_433MHzBand		((uint8_t) 0x00)	// Command to configure the NRF905 to operate in the band of 433 MHz (DEFAULT)
    #define NRF905_HFREQ_PLL_868_915MHzBand	((uint8_t) 0x01)	// Command to configure the NRF905 to operate in the band of 868 / 915 MHz
	/*========================================================================*/

	/*##### DEFINITION OF THE CHANNEL FOR RUNNING IN FREQUENCY REQUESTED #####*/
	/*====== DEFINITION OF FREQUENCY MAXIMUM AND MINIMUM OF 433MHz BAND ======*/
    #define NRF905_MINIMUM_FREQUENCY_HFREQ_PLL_0   ((uint32_t) 422400000)	// Minimum frequency in the band of 433MHz = 422,4 MHz (HFREQ_PLL = 0)
    #define NRF905_MAXIMUM_FREQUENCY_HFREQ_PLL_0   ((uint32_t) 473500000)	// Maximum frequency in the band of 433MHz = 473,5 MHz (HFREQ_PLL = 0)
    /*========================================================================*/

	/*====== DEFINITION CHANNEL FOR RUNNING IN THE FREQUENCY 433MHz BAND =====*/
    #define NRF905_CH_NO_422_4MHz	(NRF905_CALC_CHANNEL(NRF905_MINIMUM_FREQUENCY_HFREQ_PLL_0, NRF905_HFREQ_PLL_433MHzBand))	// Command to configure the frequency of operation to = 422,4 MHz (HFREQ_PLL = 0)
	/*------------------------------------------------------------------------*/
	#define NRF905_CH_NO_FREQ_433_0MHz 0x06A//433.0MHz (433MHz banda de freq��ncia base)
	#define NRF905_CH_NO_FREQ_433_1MHz 0x06B//433.1MHz
	#define NRF905_CH_NO_FREQ_433_2MHz 0x06C//433.2MHz
	/*------------------------------------------------------------------------*/
    #define NRF905_CH_NO_473_5MHz  (NRF905_CALC_CHANNEL(NRF905_MAXIMUM_FREQUENCY_HFREQ_PLL_0, NRF905_HFREQ_PLL_433MHzBand))	// Command to configure the frequency of operation to = 473,5 MHz (HFREQ_PLL = 0)
    /*========================================================================*/

	/*=== DEFINITION OF FREQUENCY MAXIMUM AND MINIMUM OF 868 / 915MHz BAND ===*/
    #define NRF905_MINIMUM_FREQUENCY_HFREQ_PLL_1	((uint32_t) 844800000)	// Minimum frequency in the band of 868 / 915MHz = 422.4 MHz (HFREQ_PLL = 1)
    #define NRF905_MAXIMUM_FREQUENCY_HFREQ_PLL_1	((uint32_t) 947000000)	// Maximum frequency in the band of 868 / 915MHz = 473,5 MHz (HFREQ_PLL = 1)
    /*========================================================================*/



	/*==================== DEFINITION OF (RF) OUTPUT POWER ===================*/
    #define NRF905_PA_PWR_MINUS_10dBm	((uint8_t) 0x00)	// Command to configure the NRF905 to operate in the power of -10dBm (DEFAULT)
    #define NRF905_PA_PWR_MINUS_2dBm	((uint8_t) 0x02)	// Command to configure the NRF905 to operate in the power of -2dBm
    #define NRF905_PA_PWR_PLUS_6dBm		((uint8_t) 0x08)	// Command to configure the NRF905 to operate in the power of +6dBm
    #define NRF905_PA_PWR_PLUS_10dBm	((uint8_t) 0x0C)	// Command to configure the NRF905 to operate in the power of +10dBm
    /*========================================================================*/

    /*=============== DEFINITION OF REDUCES CURRENT IN RX MODE ===============*/
    #define NRF905_RX_NORM_PWR	((uint8_t) 0x00)	// Command to configure the NRF905 to operate at normal power increasing sensitivity in reception (DEFAULT)
    #define NRF905_RX_RED_PWR	((uint8_t) 0x01)	// Command to configure the NRF905 to operate with reduced power lowering the sensitivity in reception
    /*========================================================================*/

    /*===================== DEFINITION OF RETRANSMISSION =====================*/
	#define NRF905_AUTO_RETRAN_DISABLED	((uint8_t) 0x00)	// Command to configure the NRF905 to disable retransmission of the data packet (DEFAULT)
	#define NRF905_AUTO_RETRAN_ENABLED	((uint8_t) 0x01)	// Command to configure the NRF905 to enable retransmission of the data packet
	/*========================================================================*/

	/*==================== DEFINITION OF RX-ADDRESS WIDTH ====================*/
	#define NRF905_RX_AFW_1_BYTE	((uint8_t) 0x01)	// Command to configure size of packet to 1 byte RX (ADDRESS) of the NRF905
	#define NRF905_RX_AFW_2_BYTES	((uint8_t) 0x02)	// Command to configure size of packet to 2 bytes RX (ADDRESS) of the NRF905
	#define NRF905_RX_AFW_3_BYTES	((uint8_t) 0x03)	// Command to configure size of packet to 2 bytes RX (ADDRESS) of the NRF905
	#define NRF905_RX_AFW_4_BYTES	((uint8_t) 0x04)	// Command to configure size of packet to 2 bytes RX (ADDRESS) of the NRF905 (DEFAULT)
	/*========================================================================*/

	/*==================== DEFINITION OF TX-ADDRESS WIDTH ====================*/
	#define NRF905_TX_AFW_1_BYTE	((uint8_t) 0x01)	// Command to configure size of packet to 1 byte TX (ADDRESS) of the NRF905
	#define NRF905_TX_AFW_2_BYTES	((uint8_t) 0x02)	// Command to configure size of packet to 2 bytes TX (ADDRESS) of the NRF905
	#define NRF905_TX_AFW_3_BYTES	((uint8_t) 0x03)	// Command to configure size of packet to 3 bytes TX (ADDRESS) of the NRF905
	#define NRF905_TX_AFW_4_BYTES	((uint8_t) (0x04 * 16))	// Command to configure size of packet to 4 bytes TX (ADDRESS) of the NRF905 (DEFAULT)
	/*========================================================================*/

	/*==================== DEFINITION OF RX-PAYLOAD WIDTH ====================*/
	#define NRF905_RX_PW_1_BYTE		((uint8_t) 0x01)	// Command to configure size of packet to 1 byte RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_2_BYTES	((uint8_t) 0x02)	// Command to configure size of packet to 2 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_3_BYTES	((uint8_t) 0x03)	// Command to configure size of packet to 3 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_4_BYTES	((uint8_t) 0x04)	// Command to configure size of packet to 4 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_5_BYTES	((uint8_t) 0x05)	// Command to configure size of packet to 5 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_6_BYTES	((uint8_t) 0x06)	// Command to configure size of packet to 6 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_7_BYTES	((uint8_t) 0x07)	// Command to configure size of packet to 7 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_8_BYTES	((uint8_t) 0x08)	// Command to configure size of packet to 8 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_9_BYTES	((uint8_t) 0x09)	// Command to configure size of packet to 9 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_10_BYTES	((uint8_t) 0x0A)	// Command to configure size of packet to 10 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_11_BYTES	((uint8_t) 0x0B)	// Command to configure size of packet to 11 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_12_BYTES	((uint8_t) 0x0C)	// Command to configure size of packet to 12 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_13_BYTES	((uint8_t) 0x0D)	// Command to configure size of packet to 13 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_14_BYTES	((uint8_t) 0x0E)	// Command to configure size of packet to 14 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_15_BYTES	((uint8_t) 0x0F)	// Command to configure size of packet to 15 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_16_BYTES	((uint8_t) 0x10)	// Command to configure size of packet to 16 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_17_BYTES	((uint8_t) 0x11)	// Command to configure size of packet to 17 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_18_BYTES	((uint8_t) 0x12)	// Command to configure size of packet to 18 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_19_BYTES	((uint8_t) 0x13)	// Command to configure size of packet to 19 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_20_BYTES	((uint8_t) 0x14)	// Command to configure size of packet to 20 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_21_BYTES	((uint8_t) 0x15)	// Command to configure size of packet to 21 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_22_BYTES	((uint8_t) 0x16)	// Command to configure size of packet to 22 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_23_BYTES	((uint8_t) 0x17)	// Command to configure size of packet to 23 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_24_BYTES	((uint8_t) 0x18)	// Command to configure size of packet to 24 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_25_BYTES	((uint8_t) 0x19)	// Command to configure size of packet to 25 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_26_BYTES	((uint8_t) 0x1A)	// Command to configure size of packet to 26 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_27_BYTES	((uint8_t) 0x1B)	// Command to configure size of packet to 27 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_28_BYTES	((uint8_t) 0x1C)	// Command to configure size of packet to 28 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_29_BYTES	((uint8_t) 0x1D)	// Command to configure size of packet to 29 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_30_BYTES	((uint8_t) 0x1E)	// Command to configure size of packet to 30 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_31_BYTES	((uint8_t) 0x1F)	// Command to configure size of packet to 31 bytes RX (PAYLOAD) of the NRF905
	#define NRF905_RX_PW_32_BYTES	((uint8_t) 0x20)	// Command to configure size of packet to 32 bytes RX (PAYLOAD) of the NRF905 (DEFAULT)
	/*========================================================================*/

	/*==================== DEFINITION OF TX-PAYLOAD WIDTH ====================*/
	#define NRF905_TX_PW_1_BYTE		((uint8_t) 0x01)	// Command to configure size of packet to 1 byte TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_2_BYTES	((uint8_t) 0x02)	// Command to configure size of packet to 2 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_3_BYTES	((uint8_t) 0x03)	// Command to configure size of packet to 3 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_4_BYTES	((uint8_t) 0x04)	// Command to configure size of packet to 4 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_5_BYTES	((uint8_t) 0x05)	// Command to configure size of packet to 5 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_6_BYTES	((uint8_t) 0x06)	// Command to configure size of packet to 6 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_7_BYTES	((uint8_t) 0x07)	// Command to configure size of packet to 7 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_8_BYTES	((uint8_t) 0x08)	// Command to configure size of packet to 8 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_9_BYTES	((uint8_t) 0x09)	// Command to configure size of packet to 9 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_10_BYTES	((uint8_t) 0x0A)	// Command to configure size of packet to 10 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_11_BYTES	((uint8_t) 0x0B)	// Command to configure size of packet to 11 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_12_BYTES	((uint8_t) 0x0C)	// Command to configure size of packet to 12 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_13_BYTES	((uint8_t) 0x0D)	// Command to configure size of packet to 13 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_14_BYTES	((uint8_t) 0x0E)	// Command to configure size of packet to 14 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_15_BYTES	((uint8_t) 0x0F)	// Command to configure size of packet to 15 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_16_BYTES	((uint8_t) 0x10)	// Command to configure size of packet to 16 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_17_BYTES	((uint8_t) 0x11)	// Command to configure size of packet to 17 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_18_BYTES	((uint8_t) 0x12)	// Command to configure size of packet to 18 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_19_BYTES	((uint8_t) 0x13)	// Command to configure size of packet to 19 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_20_BYTES	((uint8_t) 0x14)	// Command to configure size of packet to 20 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_21_BYTES	((uint8_t) 0x15)	// Command to configure size of packet to 21 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_22_BYTES	((uint8_t) 0x16)	// Command to configure size of packet to 22 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_23_BYTES	((uint8_t) 0x17)	// Command to configure size of packet to 23 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_24_BYTES	((uint8_t) 0x18)	// Command to configure size of packet to 24 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_25_BYTES	((uint8_t) 0x19)	// Command to configure size of packet to 25 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_26_BYTES	((uint8_t) 0x1A)	// Command to configure size of packet to 26 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_27_BYTES	((uint8_t) 0x1B)	// Command to configure size of packet to 27 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_28_BYTES	((uint8_t) 0x1C)	// Command to configure size of packet to 28 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_29_BYTES	((uint8_t) 0x1D)	// Command to configure size of packet to 29 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_30_BYTES	((uint8_t) 0x1E)	// Command to configure size of packet to 30 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_31_BYTES	((uint8_t) 0x1F)	// Command to configure size of packet to 31 bytes TX (PAYLOAD) of the NRF905
	#define NRF905_TX_PW_32_BYTES	((uint8_t) 0x20)	// Command to configure size of packet to 32 bytes TX (PAYLOAD) of the NRF905 (DEFAULT)
	/*========================================================================*/

	/*=================== DEFINITION OF RX ADDRESS IDENTITY ==================*/
	#define NRF905_DEFAULT_ADDRESS	((uint32_t) 0xE7E7E7E7)	// Command to set the address NRF905 to factory default (DEFAULT)
	/*========================================================================*/

	/*================= DEFINITION OF OUTPUT CLOCK FREQUENCY =================*/
	#define NRF905_UP_CLK_FREQ_4MHz		((uint8_t) 0x00)	// Command to set the output clock of the NRF905 to 4 MHz
	#define NRF905_UP_CLK_FREQ_2MHz		((uint8_t) 0x01)	// Command to set the output clock of the NRF905 to 2 MHz
	#define NRF905_UP_CLK_FREQ_1MHz		((uint8_t) 0x02)	// Command to set the output clock of the NRF905 to 1 MHz
	#define NRF905_UP_CLK_FREQ_500kHz	((uint8_t) 0x03)	// Command to set the output clock of the NRF905 to 500 kHz (DEFAULT)
	/*========================================================================*/

	/*====================== DEFINITION OF OUTPUT CLOCK ======================*/
	#define NRF905_UP_CLK_DISABLE	((uint8_t) 0x00)	// Command to disable clock output configured by (UP_CLK_FREQ) of NRF905
	#define NRF905_UP_CLK_ENABLE	((uint8_t) 0x01)	// Command to enable clock output configured by (UP_CLK_FREQ) of NRF905 (DEFAULT)
	/*========================================================================*/

	/*============== DEFINITION OF CRYSTAL OSCILLATOR FREQUENCY ==============*/
	#define NRF905_XOF_4MHz		((uint8_t) 0x00)	// Command to configure the external crystal NRF905 to 4 MHz
	#define NRF905_XOF_8MHz		((uint8_t) 0x01)	// Command to configure the external crystal NRF905 to 8 MHz
	#define NRF905_XOF_12MHz	((uint8_t) 0x02)	// Command to configure the external crystal NRF905 to 12 MHz
	#define NRF905_XOF_16MHz	((uint8_t) 0x03)	// Command to configure the external crystal NRF905 to 16 MHz
	#define NRF905_XOF_20MHz	((uint8_t) 0x04)	// Command to configure the external crystal NRF905 to 20 MHz (DEFAULT)
	/*========================================================================*/

	/*==================== DEFINITION OF CRC CHECK ENABLE ====================*/
	#define NRF905_CRC_DISABLE	((uint8_t) 0x00)	// Command to disable the CRC of the NRF905
	#define NRF905_CRC_ENABLE	((uint8_t) 0x01)	// Command to enable the CRC of the NRF905 (DEFAULT)
	/*========================================================================*/

	/*======================== DEFINITION OF CRC MODE ========================*/
	#define NRF905_CRC_MODE_8_BITS	((uint8_t) 0x00)	// Command to set the CRC NRF905 for 8 bits
	#define NRF905_CRC_MODE_16_BITS	((uint8_t) 0xC0)	// Command to set the CRC NRF905 for 16 bits (DEFAULT)

#endif /* INC_NRF905_DEFINES_H_ */

#ifndef __sht21_h__
#define __sht21_h__

#include "main.h"

/* Register addresses */
#define SHT21_TEMPERATURE_HM				0xE3
#define SHT21_HUMIDITY_HM 					0xE5

#define SHT21_TEMPERATURE_POLL				0xF3
#define SHT21_HUMIDITY_POLL 				0xF5

#define SHT21_USER_REG_W 					0xE6
#define SHT21_USER_REG_R 					0xE7
#define SHT21_SOFT_RESET 					0xFE

#define SHT21_SERIAL_ID1					0xFA
#define SHT21_SERIAL_ID2					0xFC
#define SHT21_SERIAL_ID3					0xFD

#define SHT21_RES_12_14BIT  				0x00
#define SHT21_RES_8_12BIT 					0x01
#define SHT21_RES_10_13BIT 					0x80
#define SHT21_RES_11_11BIT 					0x81
#define SHT21_RES_MASK 						0x81

#define SHT21_EOB_ON 						0x40
#define SHT21_EOB_MASK 						0x40

#define SHT21_HEATER_ON 					0x04
#define SHT21_HEATER_OFF 					0x00
#define SHT21_HEATER_MASK 					0x04

HAL_StatusTypeDef sht21_CheckCrc(uint8_t data[], uint8_t nbrOfBytes,
		uint8_t checksum);
HAL_StatusTypeDef sht21_read_reg(I2C_HandleTypeDef *hi2c, uint16_t delay,
		uint8_t reg, uint16_t *val, uint8_t len);
HAL_StatusTypeDef sht21_write_reg(I2C_HandleTypeDef *hi2c, uint8_t reg,
		uint16_t *val, uint8_t len);
HAL_StatusTypeDef sht21_measure(I2C_HandleTypeDef *hi2c, uint8_t res,
		uint8_t heater, uint8_t *bat_stat, float *temperature, float *humidity);

#endif

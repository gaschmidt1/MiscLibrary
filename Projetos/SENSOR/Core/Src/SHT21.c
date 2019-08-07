/*
 ******************************************************************************
 * File Name          : sht21.c
 * Description        : sht21 driver
 ******************************************************************************
 *
 * COPYRIGHT(c) 2019 gaschmidt1
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *
 ******************************************************************************

 The sht21 communicates with the host controller over a digital I2C interface.

 The 7-bit base slave address is 0x40

 Adaptado de https://github.com/s54mtb/MS5637_HDC1080/blob/master/inc/hdc1080.h para sensor SHT21

 */

#include "stm32f0xx_hal.h"
#include "sht21.h"
#include <string.h>

/*
 * Configure a I2C Address SHT21_ADDR
 * Set a time to wait conversion complete SHT21_TIME_HM
 */

#define SHT21_ADDR	(0x40)
#define SHT21_TIME_HM	(500U)

#define SHT21_ADDR_R	((SHT21_ADDR << 1) + 1)
#define SHT21_ADDR_W	((SHT21_ADDR << 1) + 0)

/*
 //HAL_I2C_IsDeviceReady()
 */

const uint16_t POLYNOMIAL = 0x131;

/*
 * sht21_CheckCrc() - Calculate a CRC.
 * @data:  Pointer to data for Check.
 * @nbrOfBytes: Number of bytes to check.
 * @checksum: Value to compare.
 * Returns HAL status or HAL_ERROR for invalid parameters.
 */

HAL_StatusTypeDef sht21_CheckCrc(uint8_t *data, uint8_t nbrOfBytes,
		uint8_t checksum) {

	uint8_t crc = 0;
	uint8_t byteCtr;
	uint8_t bit;

	/* Calculates 8-Bit checksum with given polynomial */
	for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr) {
		crc ^= (data[byteCtr]);

		for (bit = 8; bit > 0; --bit) {
			if (crc & 0x80) {
				crc = (crc << 1) ^ POLYNOMIAL;
			} else {
				crc = (crc << 1);
			}
		}
	}

	if (crc != checksum) {
		return (HAL_ERROR);
	} else {
		/* Success */
		return (HAL_OK);
	}
}

/*
 * sht21_read_reg() - Read User register
 * @hi2c:  handle to I2C interface
 * @delay: Delay before read
 * @reg: Register address
 * @val: 16-bit register value from the sht21
 * Returns HAL status or HAL_ERROR for invalid parameters.
 * Use delay 100ms to SHT21_TEMPERATURE_HM or SHT21_HUMIDITY_HM
 */
HAL_StatusTypeDef sht21_read_reg(I2C_HandleTypeDef *hi2c, uint16_t delay,
		uint8_t reg, uint16_t *val, uint8_t len) {
	uint8_t buf[4];
	uint8_t crc = 0;
	HAL_StatusTypeDef error;

	//HAL_I2C_IsDeviceReady(hi2c, DevAddress, Trials, Timeout);
	//HAL_I2C_GetState(hi2c);
	//HAL_I2C_ListenCpltCallback(;)

	/* Check arguments */
	if ((reg != SHT21_TEMPERATURE_HM) & (reg != SHT21_HUMIDITY_HM)
			& (reg != SHT21_USER_REG_R)) {
		return (HAL_ERROR);
	}

	/* Read register */
	/* Send the read followed by address */
	buf[0] = reg;
	error = HAL_I2C_Master_Transmit(hi2c, SHT21_ADDR_W, buf, 1, 1000);
	if (error != HAL_OK) {
		return (HAL_ERROR);
	}

	/* Wait convertion */
	HAL_Delay(delay);

	/* Receive a byte result */
	error = HAL_I2C_Master_Receive(hi2c, SHT21_ADDR_R, buf, len, 1000);
	if (error != HAL_OK) {
		return (HAL_ERROR);
	}

	/* Receive a CRC */
	error = HAL_I2C_Master_Receive(hi2c, SHT21_ADDR_R, &crc, 1, 1000);
	if (error != HAL_OK) {
		return (HAL_ERROR);
	}

	/* Compute a CRC */
	error = sht21_CheckCrc(buf, 1, crc);
//  if(error != HAL_OK)
//    {
//      return(HAL_ERROR);
//    }

	/* Result */
	if (len == 1) {
		*val = buf[0];
	} else if (len == 2) {
		*val = buf[0] * 256 + buf[1];
	} else {
		*val = 0;
		return (HAL_ERROR);
	}
	/* Success */
	return (HAL_OK);
}

/*
 * sht21__write_reg() - Write register
 * @hi2c:  handle to I2C interface
 * @reg: Register address
 * @val: 8-bit register pointer from the data
 * Returns HAL status or HAL_ERROR for invalid arguments.
 */
HAL_StatusTypeDef sht21_write_reg(I2C_HandleTypeDef *hi2c, uint8_t reg,
		uint16_t *val, uint8_t len) {
	uint8_t i;
	uint8_t buf[5];
	HAL_StatusTypeDef error;

	/* Check arguments */
	if ((reg != SHT21_USER_REG_W) & (reg != SHT21_SOFT_RESET)
			& (reg != SHT21_TEMPERATURE_HM) & (reg != SHT21_HUMIDITY_HM)) {
		return (HAL_ERROR);
	}

	/* Process buffer tx */
	buf[0] = reg;

	for (i = 1; i <= len; i++) {
		buf[i] = *val;
		val++;
	}

	/* Send the  data */
	error = HAL_I2C_Master_Transmit(hi2c, SHT21_ADDR_W, buf, (len + 1), 100);
	if (error != HAL_OK) {
		return (HAL_ERROR);
	}
	return (HAL_OK); /* Success */
}

/*
 * sht21_measure() - measure humididty and temperature:
 1. Configure the acquisition parameters in config register.
 2. Trigger the measurements by writing I2C read reg. address with adr = SHT21_TEMPERATURE_HM.
 3. Wait for the measurements to complete, based on the conversion time SHT21_TIME_HM.
 4. Read the output data:
 Read the temperature data from register address SHT21_TEMPERATURE_HM, followed by the humidity
 data from register address SHT21_HUMIDITY_HM in a single transaction. A read operation will
 return a NACK if the contents of the registers have not been updated.

 * @hi2c:  handle to I2C interface
 * @res         :  measurement resolution:
 *					- SHT21_RES_12_14BIT or
 *					- SHT21_RES_8_12BIT or
 *					- SHT21_RES_10_13BIT or
 *					- SHT21_RES_11_11BIT
 * @heater      :  heater enable (0 = disabled or 1 = enabled)
 * @bat_stat    :  supply voltage
 *                  - 0 when Ucc > 2,8V
 *					- 1 when Ucc < 2,8V
 * @temperature :  floating point temperature result, unit is �C
 * @humidity    :  floating point humidity result, unit is RH%
 * Returns HAL status.
 */
HAL_StatusTypeDef sht21_measure(I2C_HandleTypeDef *hi2c, uint8_t res,
		uint8_t heater, uint8_t *bat_stat, float *temperature, float *humidity) {

	HAL_StatusTypeDef error;
	uint16_t r;
	float tmp;

	// read config
	error = sht21_read_reg(hi2c, 5, SHT21_USER_REG_R, &r, 1);
	if (error != HAL_OK) {
		return (HAL_ERROR);
	}

	// HAL_Delay(5);

	*bat_stat = (r & SHT21_EOB_MASK) >> 2;

	r = 0;
	r |= (res & SHT21_RES_MASK);
	r |= (heater & SHT21_HEATER_MASK);

	// write config
	error = sht21_write_reg(hi2c, SHT21_USER_REG_W, &r, 1);
	if (error != HAL_OK) {
		return (HAL_ERROR);
	}

	//HAL_Delay(5);

	// read temperature
	error = sht21_read_reg(hi2c, SHT21_TIME_HM, SHT21_TEMPERATURE_HM, &r, 2);
	if (error != HAL_OK) {
		return (HAL_ERROR);
	}

	// convert temperature
	r &= ~0x0003;
	tmp = (float) r;
	tmp = -46.85f + 175.72f / 65535.0f * (float) tmp;
	if (tmp > 100.0f) {
		tmp = 100.0f;
	}
	if (tmp < -20.0f) {
		tmp = -20.0f;
	}
	*temperature = tmp;  // �C
	//HAL_Delay(5);
	// read humidity
	error = sht21_read_reg(hi2c, SHT21_TIME_HM, SHT21_HUMIDITY_HM, &r, 2);

	if (error != HAL_OK) {
		return (HAL_ERROR);
	}

	// convert humidity
	r &= ~0x0003;
	tmp = (float) r;
	tmp = -6.0f + 125.0f / 65535.0f * (float) tmp;
	if (tmp > 100.0f) {
		tmp = 100.0f;
	}
	if (tmp < 0.0f) {
		tmp = 0.0f;
	}
	*humidity = tmp;  // RH%
	//HAL_Delay(5);
	// reset sensor
	r = 0;
	error = sht21_write_reg(hi2c, SHT21_SOFT_RESET, &r, 1);
	if (error != HAL_OK) {
		return (HAL_ERROR);
	}
	//HAL_Delay(5);
	return (HAL_OK);
}


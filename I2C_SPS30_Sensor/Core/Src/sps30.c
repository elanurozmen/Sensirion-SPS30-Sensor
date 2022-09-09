/*
 * sps30.c
 *
 *  Created on: 23 Ağu 2022
 *      Author: Elanur
 */
#include "sps30.h"
#include "i2c.h"
//extern I2C_HandleTypeDef hi2c1;

uint8_t cmd[2], rx_buf[30], dataReadyFlag[3];
particleData pd;

uint8_t CalcCrc(uint8_t d[2]) {
	uint8_t crc = 0xFF;
	for (int i = 0; i < 2; i++) {
		crc ^= d[i];
		for (uint8_t bit = 8; bit > 0; --bit) {
			if (crc & 0x80) {
				crc = (crc << 1) ^ 0x31u;
			} else {
				crc = (crc << 1);
			}
		}
	}
	return crc;
}
void startMeasurement(void) {
	cmd[0] = 0x05;
	cmd[1] = 0x00;
	uint8_t command[5] = { SPS30_START_MEASUREMENT_BYTE1,
	SPS30_START_MEASUREMENT_BYTE2, 0x05, 0x00, CalcCrc(cmd) };
	HAL_I2C_Master_Transmit(&hi2c1, SPS30_I2C_ADDRESS, command, sizeof(command),
			500);
}
void stopMeasurement(void) {
	cmd[0] = SPS30_STOP_MEASUREMENT_BYTE1;
	cmd[1] = SPS30_STOP_MEASUREMENT_BYTE2;
	HAL_I2C_Master_Transmit(&hi2c1, SPS30_I2C_ADDRESS, cmd, sizeof(cmd), 500);
}
void readDataReadyFlag(void) {
	cmd[0] = SPS30_READ_DATA_READY_FLAG_BYTE1;
	cmd[1] = SPS30_READ_DATA_READY_FLAG_BYTE2;
	HAL_I2C_Master_Transmit(&hi2c1, SPS30_I2C_ADDRESS, cmd, sizeof(cmd), 500);
	HAL_I2C_Master_Receive(&hi2c1, SPS30_I2C_ADDRESS, dataReadyFlag,
			sizeof(dataReadyFlag), 500);
}
void readMeasuredValues(void) {
	cmd[0] = SPS30_READ_MEASUREMENT_BYTE1;
	cmd[1] = SPS30_READ_MEASUREMENT_BYTE2;
	HAL_I2C_Master_Transmit(&hi2c1, SPS30_I2C_ADDRESS, cmd, sizeof(cmd), 500);
	HAL_I2C_Master_Receive(&hi2c1, SPS30_I2C_ADDRESS, rx_buf, sizeof(rx_buf),
			500);
	pd.massConcentration1_0 = ((rx_buf[0] << 8) | (rx_buf[1]));
	pd.massConcentration2_5 = ((rx_buf[3] << 8) | (rx_buf[4]));
	pd.massConcentration4_0 = ((rx_buf[6] << 8) | (rx_buf[7]));
	pd.massConcentration10 = ((rx_buf[9] << 8) | (rx_buf[10]));
	pd.numberConcentration0_5 = ((rx_buf[12] << 8) | (rx_buf[13]));
	pd.numberConcentration1_0 = ((rx_buf[15] << 8) | (rx_buf[16]));
	pd.numberConcentration2_5 = ((rx_buf[18] << 8) | (rx_buf[19]));
	pd.numberConcentration4_0 = ((rx_buf[21] << 8) | (rx_buf[22]));
	pd.numberConcentration10 = ((rx_buf[24] << 8) | (rx_buf[25]));
	pd.particleSize = ((rx_buf[27] << 8) | (rx_buf[28]));
}
void startFanCleaning(void) {
	cmd[0] = SPS30_START_FAN_CLEANING_BYTE1;
	cmd[1] = SPS30_START_FAN_CLEANING_BYTE2;
	HAL_I2C_Master_Transmit(&hi2c1, SPS30_I2C_ADDRESS, cmd, sizeof(cmd), 500);
}



#ifndef __SPS30_H
#define __SPS30_H

#include <stdint.h>
#define SPS30_I2C_ADDRESS						(0x69 << 1)
#define SPS30_START_MEASUREMENT_BYTE1			0x00
#define SPS30_START_MEASUREMENT_BYTE2			0x10
#define SPS30_STOP_MEASUREMENT_BYTE1			0x01
#define SPS30_STOP_MEASUREMENT_BYTE2			0x04
#define SPS30_START_FAN_CLEANING_BYTE1			0x56
#define SPS30_START_FAN_CLEANING_BYTE2			0x07
#define SPS30_READ_MEASUREMENT_BYTE1			0x03
#define SPS30_READ_MEASUREMENT_BYTE2			0x00
#define SPS30_READ_DATA_READY_FLAG_BYTE1		0x02
#define SPS30_READ_DATA_READY_FLAG_BYTE2		0x02


typedef struct Data {
	uint16_t massConcentration1_0;
	uint16_t massConcentration2_5;
	uint16_t massConcentration4_0;
	uint16_t massConcentration10;
	uint16_t numberConcentration0_5;
	uint16_t numberConcentration1_0;
	uint16_t numberConcentration2_5;
	uint16_t numberConcentration4_0;
	uint16_t numberConcentration10;
	uint16_t particleSize;
} particleData;

uint8_t CalcCrc(uint8_t d[2]);
void startMeasurement(void);
void stopMeasurement(void);
void readDataReadyFlag(void);
void readMeasuredValues(void);
void startFanCleaning(void);

#endif
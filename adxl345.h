#ifndef ADXL345_H
#define ADXL345_H
#include <SPI.h>


#define ADXL_CS 10  // ADXL_CS pin goes to D10 on Arduino Uno R3

// ADXL345 Registers
const char ADXL_POWER_CTL = 0x2D;
const char ADXL_DATA_FORMAT = 0x31;
const char ADXL_DATAX0 = 0x32;  // X-Axis Data 0
const char ADXL_DATAX1 = 0x33;  // X-Axis Data 1
const char ADXL_DATAY0 = 0x34;  // Y-Axis Data 0
const char ADXL_DATAY1 = 0x35;  // Y-Axis Data 1
const char ADXL_DATAZ0 = 0x36;  // Z-Axis Data 0
const char ADXL_DATAZ1 = 0x37;  // Z-Axis Data 1


SPISettings SPI_settings(100000, MSBFIRST, SPI_MODE3);

void writeRegister(char registerAdress, char value);
void readRegister(char registerAdress, int numBytes, unsigned char* values);

#endif  // ADXL345_H

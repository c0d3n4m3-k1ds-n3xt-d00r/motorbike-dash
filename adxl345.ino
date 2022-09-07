#include <SPI.h>
#include "adxl345.h"


void writeRegister(char registerAdress, char value) {
  // Chip select LOW to write to chip
  digitalWrite(ADXL_CS, LOW);
  SPI.transfer(registerAdress);
  SPI.transfer(value);
  digitalWrite(ADXL_CS, HIGH);
}

void readRegister(char registerAdress, int numBytes, unsigned char* values) {
  char adress = 0x80 | registerAdress;  // Set write mode
  if (numBytes > 1) adress = adress | 0x40;  // Set bit 6 for multi-byte read

  digitalWrite(ADXL_CS, LOW);
  SPI.transfer(adress);

  for (int i = 0; i < numBytes; i++) {
    values[i] = SPI.transfer(0x00);
  }

  digitalWrite(ADXL_CS, HIGH);
}
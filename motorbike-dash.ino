#include <SoftwareSerial.h>
#include "adxl345.h"
#include "gps.h"


SoftwareSerial EspSerial(2, 3);  // RX, TX

// Gyroscope/accelerometer SPI read buffer
unsigned char adxl_buffer[10];

// Gyroscope/accelerometer values
int gyro_x, gyro_y, gyro_z;


void setup() {
  Serial.begin(9600);
  EspSerial.begin(9600);


  /***============================
    Gyroscope/accelerometer config
  ==============================***/
  pinMode(ADXL_CS, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPI_settings);
  digitalWrite(ADXL_CS, HIGH);

  writeRegister(ADXL_DATA_FORMAT, 0x01);  // Set 4G range
  writeRegister(ADXL_POWER_CTL, 0x08);  // Measurement mode
  /* End of Gyroscope/accelerometer config */


  /***========
    GPS config
  ==========***/
  ss.begin(GPSBaud);
  /* End of GPS config */


  /***====
    Header
  ======***/
  Serial.println();
  Serial.println(F("Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Speed Chars Sentences Checksum Gyro and"));
  Serial.println(F("           (deg)      (deg)       Age                      Age  (m)    km/h  RX    RX        Fail     Accelerometer"));
  Serial.println(F("-------------------------------------------------------------------------------------------------------------------"));
}


void loop() {
  // Read gyroscope/accelerometer data
  readRegister(ADXL_DATAX0, 6, adxl_buffer);
  gyro_x = (int) word(adxl_buffer[1], adxl_buffer[0]);
  gyro_y = (int) word(adxl_buffer[3], adxl_buffer[2]);
  gyro_z = (int) word(adxl_buffer[5], adxl_buffer[4]);


  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printInt(gps.location.age(), gps.location.isValid(), 5);
  printDateTime(gps.date, gps.time);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  printInt(gps.charsProcessed(), true, 6);
  printInt(gps.sentencesWithFix(), true, 10);
  printInt(gps.failedChecksum(), true, 9);
  Serial.print(gyro_x, DEC);
  Serial.print(", ");
  Serial.print(gyro_y, DEC);
  Serial.print(", ");
  Serial.println(gyro_z, DEC);
  auto data_str = String(gyro_x) + ", " + String(gyro_y) + ", " + String(gyro_z);
  EspSerial.println(data_str);


  gpsDelay(200);
  if (millis() > 1000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

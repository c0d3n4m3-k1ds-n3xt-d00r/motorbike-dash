#define BLYNK_TEMPLATE_ID "TMPLUzhS6tBZ"
#define BLYNK_DEVICE_NAME "Light test"
#define BLYNK_AUTH_TOKEN "MS1KhkU9rXbcbCyGfWPGIpgZIC5B8FI2"
#define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include "adxl345.h"
#include "gps.h"


// Blynk
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Starwalker's Plane";  // You can replace the wifi name to your wifi 
char pass[] = "Maple123";   // Type password of your wifi.
SoftwareSerial EspSerial(2, 3);  // RX, TX
ESP8266 wifi(&EspSerial);

// Gyroscope/accelerometer SPI read buffer
unsigned char adxl_buffer[10];

// Gyroscope/accelerometer values
int gyro_x, gyro_y, gyro_z;


void setup() {
  Serial.begin(9600);

  /***==========
    Blynk config
  ============***/
  EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, wifi, ssid, pass);

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
  Blynk.run();

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


  gpsDelay(200);
  if (millis() > 1000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

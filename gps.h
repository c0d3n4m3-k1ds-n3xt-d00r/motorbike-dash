#ifndef GPS_H
#define GPS_H
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>


const int GPS_RXPin = 4, GPS_TXPin = 3;
const uint32_t GPSBaud = 9600;


TinyGPSPlus gps;  // The TinyGPSPlus object
SoftwareSerial ss(GPS_RXPin, GPS_TXPin);  // The serial connection to the GPS device

void gpsDelay(unsigned long ms);  // This custom version of delay() ensures that the gps object is being "fed"
void printFloat(float val, bool valid, int len, int prec);
void printInt(unsigned long val, bool valid, int len);
void printDateTime(TinyGPSDate &d, TinyGPSTime &t);
void printStr(const char *str, int len);

#endif  // GPS_H

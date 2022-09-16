// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLUzhS6tBZ"
#define BLYNK_DEVICE_NAME "Light test"
#define BLYNK_AUTH_TOKEN "MS1KhkU9rXbcbCyGfWPGIpgZIC5B8FI2"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Starwalker's Plane";
char pass[] = "Maple123";

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);
  
  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  timer.setInterval(1000L, sendsensor);
}
void sendsensor(){
  Blynk.virtualWrite(V15, (int) Serial.read());
  Serial.println("");
  delay(500);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  sendsensor();
  timer.run();
}

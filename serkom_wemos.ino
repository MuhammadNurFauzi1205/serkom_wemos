
//SoftwareSerial SerialWe(D1, D3);
#include <AntaresCerts.h>
#include <AntaresESPHTTP.h>
#include <ArduinoJson.h>

#define ACCESSKEY "57897c4e056ef599:2b9b2e2854d375ef" // Replace with your Antares account access key
#define WIFISSID "FAUZI" // Replace with your Wi-Fi SSID
#define PASSWORD "12345678" // Replace with your Wi-Fi password

#define projectName "iotzb"   // Antares project name
#define deviceName "iotzb" // Name of the device 

const unsigned long interval = 10000;  // 10 s interval to send message
unsigned long previousMillis = 0;      // will store last time message sent

#include <SoftwareSerial.h>

SoftwareSerial SerialWe (D6, D7);
SoftwareSerial SerialOne (D6, D7);

AntaresESPHTTP antares(ACCESSKEY); // Initialize AntaresESP32HTTP with the access key

float c;
float b;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialWe.begin(9600);
  SerialOne.begin(9600);
  
  antares.setDebug(true);    // Enable Antares library debug mode
  antares.wifiConnection(WIFISSID, PASSWORD);  // Connect to WiFi using provided SSID and password
//  WiFi.begin(WIFISSID, PASSWORD);
//  while(WiFi.status() != WL_CONNECTED)
//  {
//    Serial.println("nggak konek");
//    delay(500);
//  }
}

void loop() {
// SerialWe.write("SerialWe");
  if (millis() - previousMillis > interval) {
   previousMillis = millis();
   SerialWe.available();
   c = SerialWe.read();
   Serial.println(c);
   SerialOne.available();
   b = SerialOne.read();
   Serial.println(b);
   delay(10000);
   antares.add("analog", c);
   antares.add("biasa", b);
  
      // Send the data from the storage buffer to Antares
   antares.send(projectName, deviceName);
   }
 
}

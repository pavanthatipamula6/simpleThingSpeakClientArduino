#ifndef THINGSPEAK_ESP01_H
#define THINGSPEAK_ESP01_H

#include <SoftwareSerial.h>

#define esprxPin 2
#define esptxPin 3
#define espBaud 115200
#define DEBUG true

extern String esp01SSID;
extern String esp01PWD;
extern String esp01WriteAPI;
extern String esp01HOST;
extern String esp01PORT;

extern SoftwareSerial espSerial;  // only declared, not defined here

void initEsp01();
void sendThingSpeak(int fieldNumber = 0, String data = "test");
String espData(String command, const int timeout, bool debug);

#endif

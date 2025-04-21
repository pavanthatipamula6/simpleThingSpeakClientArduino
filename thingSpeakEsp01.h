#ifndef ESP01_H
#define ESP01_H

#include <SoftwareSerial.h>

#define esprxPin 2
#define esptxPin 3
#define espBaud 115200
#define DEBUG true

extern String mySSID;
extern String myPWD;
extern String myAPI;
extern String myHOST;
extern String myPORT;

extern SoftwareSerial espSerial;

void initEsp01();
void sendThingSpeak(int fieldNumber = 0, String data = "test");
// String espData(String command, const int timeout, boolean debug);
String espData(String command, const int timeout, bool debug);

#endif

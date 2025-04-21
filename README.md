# simpleThingSpeakClientArduino

// Define these BEFORE including esp01.h
String mySSID = "SSID";
String myPWD = "PASSWORD";
String myAPI = "writeApi";
String myHOST = "api.thingspeak.com";
String myPORT = "80";

#include "thingSpeakEsp01.h"


then use 
initEsp01(); 
in setup function and 

to send data use 
sendThingSpeak("FieldNumber","DATA in STRING");

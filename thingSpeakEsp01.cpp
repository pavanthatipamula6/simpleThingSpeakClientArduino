#include "esp01.h"
#include <Arduino.h>

// These will be defined in the main .ino
extern String mySSID;
extern String myPWD;
extern String myAPI;
extern String myHOST;
extern String myPORT;

SoftwareSerial espSerial(esprxPin, esptxPin);

void initEsp01() {
  espSerial.begin(espBaud);
  delay(250);
  espData("AT+RST", 1000, DEBUG);                                         //Reset the ESP8266 module
  espData("AT+CWMODE=1", 1000, DEBUG);                                    //Set the ESP mode as station mode
  espData("AT+CWJAP=\"" + mySSID + "\",\"" + myPWD + "\"", 1000, DEBUG);  //Connect to WiFi network
}

void sendThingSpeak(int fieldNumber, String data) {
  String sendData = "GET /update?api_key=" + myAPI + "&field" + String(fieldNumber) + "=" + data;
  espData("AT+CIPMUX=1", 1000, DEBUG);  //Allow multiple connections
  espData("AT+CIPSTART=0,\"TCP\",\"" + myHOST + "\"," + myPORT, 1000, DEBUG);
  espData("AT+CIPSEND=0," + String(sendData.length() + 4), 1000, DEBUG);
  espSerial.find(">");
  espSerial.println(sendData);
  Serial.print("Value to be sent: ");
  Serial.println(data);

  espData("AT+CIPCLOSE=0", 1000, DEBUG);
}

String espData(String command, const int timeout, bool debug) {
  Serial.print("AT Command ==> ");
  Serial.print(command);
  Serial.println("     ");

  String response = "";
  espSerial.println(command);
  long int time = millis();
  while ((time + timeout) > millis()) {
    while (espSerial.available()) {
      char c = espSerial.read();
      response += c;
    }
  }
  if (debug) {
    Serial.print(response);
  }
  return response;
}
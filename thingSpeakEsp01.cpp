#include "thingSpeakEsp01.h"
#include <Arduino.h>

// Global variables declared in main .ino
extern String esp01SSID;
extern String esp01PWD;
extern String esp01WriteAPI;
extern String esp01HOST;
extern String esp01PORT;

// ✅ Define espSerial only once
SoftwareSerial espSerial(esprxPin, esptxPin);

// rest of your functions...


void initEsp01() {
  espSerial.begin(espBaud);
  delay(250);
  espData("AT+RST", 1000, DEBUG);
  espData("AT+CWMODE=1", 1000, DEBUG);
  espData("AT+CWJAP=\"" + esp01SSID + "\",\"" + esp01PWD + "\"", 3000, DEBUG);
}

void sendThingSpeak(int fieldNumber, String data) {
  String sendData = "GET /update?api_key=" + esp01WriteAPI + "&field" + String(fieldNumber) + "=" + data;
  espData("AT+CIPMUX=1", 1000, DEBUG);
  espData("AT+CIPSTART=0,\"TCP\",\"" + esp01HOST + "\"," + esp01PORT, 1000, DEBUG);
  espData("AT+CIPSEND=0," + String(sendData.length() + 4), 1000, DEBUG);
  espSerial.find(">");
  espSerial.println(sendData);
  Serial.println("Value sent: " + data);
  espData("AT+CIPCLOSE=0", 1000, DEBUG);
}

String espData(String command, const int timeout, bool debug) {
  Serial.print("AT Command ==> ");
  Serial.println(command);

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

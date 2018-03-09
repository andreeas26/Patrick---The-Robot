/*
    Patrick - The Robot
    Version: 1.0
    Author: Alex Bordei
    http://alexbordei.com/patrick-the-robot
*/
//Constants
#define BAUD_RATE 115200

//Including libraries
#include <SoftwareSerial.h>

SoftwareSerial ESP8266(10, 11);

void setup() {

  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  ESP8266.begin(BAUD_RATE);

}
//wifi.setmode(wifi.STATION)
//wifi.sta.config("Alex Bordei", "nimicMaigreu")
//print(wifi.sta.getip())

//Available commands
/*
  setWireless
  getIp
  hold
*/

String ESPCommand = "getIp";

void loop() {
  delay(2000);


  if (ESPCommand == "setWireless") {
    ESP8266.println("wifi.sta.config(\"[SSID]\", \"[PASSWORD]\")");
  //  ESPCommand = "hold";
ESP8266.println("print(wifi.sta.getip())");
  if (ESP8266.available() > 0) {
      Serial.println(ESP8266.readString());
    }
  }
  else if(ESPCommand == "getIp"){
    
    ESP8266.println("print(wifi.sta.getip())");

    if (ESP8266.available() > 0) {
      Serial.println(ESP8266.readString());
    }
  }
}

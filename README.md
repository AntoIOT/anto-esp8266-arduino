# Anto client library for ESP8266-Arduino
ESP8266-AntoIO provides common and easy way to connect your ESP8266 to Anto.io IoT platform service.

## Stable version
0.7.3

## Quick start
<https://antoiot.gitbooks.io/th-doc/content/index.html>

## Port
Make sure that your network or firewall are allowed to connect following port
* HTTP: 80
* MQTT: 1883

## Installation
* Download and install virtual COM port for hardware connection
> For NodeMCU version 0.9 <http://www.electrodragon.com/w/CH341>
> For NodeMCU Version 1.0 <https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx>
* Download and install Arduino IDE 1.6.9 or above from https://www.arduino.cc/en/Main/Software
* After installation completed, open Arduino IDE and click Preferences
* Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` in Additional Board Manager URLs
* Install ES8266 main library by go to Tools > Boards Manager. Search for  `esp8266` and click install
* Download this library from and extract your file into folder `Documents\Arduino\Libraries`
* Register and login to <https://www.anto.io> and start build your IoT project
* Have fun & Share!

## Quick start usage example - Control 3 LED ##
```c++
#include <AntoIO.h>

const char *ssid = "your access point SSID";
const char *pass = "access point password";
const char *user = "your username";
const char *token = "your token";
const char *thing = "your thing";

// initialize AntoIO instance
AntoIO anto(user, token, thing);

int value = 0;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Anto library version: ");
  Serial.println(anto.getVersion());


  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");

  anto.begin(ssid, pass, messageReceived);
  Serial.println("\nConnected Anto done");

  //Subscript Channels
  anto.sub("LED1");
  anto.sub("LED2");
  anto.sub("LED3");

  //Port output
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
}

void loop() {
  anto.mqtt.loop();
}


// a callback function for arriving data.
void messageReceived(String thing, String channel, String payload) {

    Serial.print("Recieved: ");
    Serial.print(thing);
    Serial.print("/");
    Serial.print(channel);
    Serial.print("-> ");
    Serial.println(payload);

    if(channel.equals("LED1")){
        value = payload.toInt();
        if(value == 1){
            digitalWrite(D1,HIGH);
        }
        else{
            digitalWrite(D1,LOW);
        }

    }
    else if(channel.equals("LED2")){
        value = payload.toInt();
        if(value == 1){
            digitalWrite(D2,HIGH);
        }
        else{
            digitalWrite(D2,LOW);
        }
    }
    else if(channel.equals("LED3")){
        value = payload.toInt();
        if(value == 1){
            digitalWrite(D3,HIGH);
        }
        else{
            digitalWrite(D3,LOW);
        }
    }
}
```
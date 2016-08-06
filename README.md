# Anto client library for ESP8266-Arduino
ESP8266-AntoIO provides common and easy method to connect your chip to Anto.io IoT platform service.

## Stable version
0.5.2

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

// WiFi name and Password of your WiFi access point
const char* wifi_name = "";
const char* wifi_password  = "";

// Username of Anto.io account
const char *username = "";

// Key to access and control your channels, generated on Anto.io control panel
const char* key = "";

// Thing name
const char* thing = "";

// Global variable
AntoIO anto(username, key, thing);

bool bIsConnected = false;

void setup() {
	Serial.begin(115200);
    delay(10);
    anto.showVersion();

    // Connect to your WiFi access point
    if (!anto.begin(wifi_name, wifi_password)) {
        Serial.println("Failed to connect to WiFi!");
        while (1); // Stop everything
    }
    Serial.println("WiFi connected");  
    Serial.println("Connecting to MQTT broker");
	
	// register MQTT callback functions
	anto.on("connected", onConnectedFunc);
	anto.on("disconnected", onDisconnectedFunc);
	anto.on("dataReceived", onDataReceivedFunc);
	anto.connectMQTT(); // Connect to Anto MQTT broker

    //port output
    pinMode(D1,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

/*
* onConnectedFunc(): a callback function called when the connection to the MQTT broker is established.
*/
void onConnectedFunc()
{   
    bIsConnected = true;
    Serial.println("Connected to Anto MQTT Broker");
    
    anto.sub("LED1");
    anto.sub("LED2");
    anto.sub("LED3");
}

/*
* onDisconnectedFunc(): a callback function called when the connection to the MQTT broker is broken.
*/
void onDisconnectedFunc()
{   
    bIsConnected = false;
    Serial.println("Disconnected from Anto MQTT Broker");
}

/*
* onDataReceivedFunc(): a callback function called when received a message from the subscribed channel.
*/
void onDataReceivedFunc(String& thing, String& channel, String& msg)
{
	int value = 0;
	
    if(channel == "LED1"){
		value = msg.toInt();
		if(value == 1){
			digitalWrite(D1,HIGH);
		}else{
			digitalWrite(D1,LOW);
		}
    }else if(channel == "LED2"){
		value = msg.toInt();
		if(value == 1){
			digitalWrite(D2,HIGH);
		}else{
			digitalWrite(D2,LOW);
		}
    }else if(channel == "LED3"){
		value = msg.toInt();
		if(value == 1){
			digitalWrite(D3,HIGH);
		}else{
			digitalWrite(D3,LOW);
		}
    }
}
```
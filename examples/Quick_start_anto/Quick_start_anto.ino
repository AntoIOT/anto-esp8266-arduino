/*
 * This is the example of using Anto.io library to 
 * Control 3 LED from the internet (Use MQTT protocol)
 */
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
/*
 * This is the example of using Anto.io library to 
 * Send DHT sensor value to the internet via Anto
 */
#include <AntoIO.h>
#include <DHT.h>

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
	anto.connectMQTT(); // Connect to Anto MQTT broker

    // start dht sensor
    dht.begin();
}

void loop() {
	// put your main code here, to run repeatedly:
	
	if (bIsConnected) // Check is connected to server ?
	{
		float temp = dht.readTemperature();
		float humid = dht.readHumidity();
		
		Serial.print("TEMP: ");
		Serial.println(temp);
		
		Serial.print("HUMID: ");
		Serial.println(humid);  
		
		if (temp >= 0) {
			anto.pub("Temp", temp); // send temperature value to server
		}
		
		if (humid >= 0) {
			anto.pub("Humid", humid); // send humidity value to server
		}
		
		delay(2000);
	}
}

/*
* onConnectedFunc(): a callback function called when the connection to the MQTT broker is established.
*/
void onConnectedFunc()
{   
    bIsConnected = true;
    Serial.println("Connected to Anto MQTT Broker");
}

/*
* onDisconnectedFunc(): a callback function called when the connection to the MQTT broker is broken.
*/
void onDisconnectedFunc()
{   
    bIsConnected = false;
    Serial.println("Disconnected from Anto MQTT Broker");
}
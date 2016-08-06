/*
 * This is the example of using AntoIO library to 
 * Get digital 'channel' from Anto via HTTP protocol
 * 
 * by Anto.io
 */

#include <AntoIO.h>

/* see NodeMCU v1.0 pinout for more GPIO port details. */
#define LED0 16 // D0
#define LED1 5  // D1
#define LED2 4  // D2
#define LED3 0  // D3

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

    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

void loop() {
    delay(5000);
    ++value;

    bool var = LOW;

    var = anto.digitalGet("smartPlug01");
    digitalWrite(LED0, var);
    Serial.print("LED0: ");
    Serial.println(var);

    var = anto.digitalGet("smartPlug02");
    digitalWrite(LED1, var);
    Serial.print("LED1: ");
    Serial.println(var);

    var = anto.digitalGet("smartPlug03");
    digitalWrite(LED2, var);
    Serial.print("LED2: ");
    Serial.println(var);

    var = anto.digitalGet("smartPlug04");
    digitalWrite(LED3, var);
    Serial.print("LED3: ");
    Serial.println(var);

    Serial.println();
}

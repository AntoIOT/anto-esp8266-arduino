/*
 * This is the example of using AntoIO library to 
 * Update and get channel value via HTTP protocol
 * 
 * by Anto.io
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
}

void loop() {
    delay(5000);
    ++value;

	// Update the channels value
    if (value % 2 == 0) {
        anto.digitalUpdate("input", LOW);
        anto.analogUpdate("analog", 1234);
        anto.stringUpdate("name", "kohpai");
    }
    else {
        anto.digitalUpdate("input", HIGH);
        anto.analogUpdate("analog", 5678);
        anto.stringUpdate("name", "farm");
    }

	// Get the channels value
    Serial.print("Digital: ");
    Serial.println((anto.digitalGet("input")));

    Serial.print("Analog: ");
    Serial.println(anto.analogGet("analog"));

    Serial.print("String: ");
    Serial.println(anto.stringGet("Name"));

    Serial.println();
}

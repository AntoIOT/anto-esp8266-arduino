/*
 * This is the example of using Anto.io library to 
 * Get data service value from Anto
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
    Serial.println("Anto Service Request");
    Serial.println(anto.getDataService("gas.91e10.price"));
    Serial.println();
}

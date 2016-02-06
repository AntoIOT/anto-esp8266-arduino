/*
 * This is the example of using AntoIO library to 
 * send HTTP request to any server.
 * 
 * by Anto.io
 */

#include <AntoIO.h>

// change ssid and password to yours
const char* ssid     = "CE-ESL";
const char* password = "ceeslonly";

// use demo token or change to your token
const char* token = "Y9hHIBjdwPEOZo6c7SafNiz3X0snuJLRTFqgDKrU";
// use demo thing or change to your thing
const char* thing = "weather_station";
const char *user = "WHCWHC78";

int value = 0;
bool bIsConnected = false;

void setup() {
    Serial.begin(115200);
    delay(10);

    // Connect to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    if (!Anto.begin(ssid, password, token, user, thing)) {
        Serial.println("Connection failed!!");

        while (1);
    }

    Serial.println();
    Serial.println("WiFi connected");  
}

void loop() {
    delay(5000);
    ++value;

    Serial.println("Requesting ...");
    Serial.println(Anto.requestHttp("128.199.239.49","/?name=kohpai"));
}

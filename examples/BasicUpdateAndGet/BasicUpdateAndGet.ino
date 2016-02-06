/*
 * This is the example of using AntoIO library to 
 * Update and get digital 'channel' from dev-api.anto.io.
 * 
 * by Anto.io
 */

#include <AntoIO.h>

// change ssid and password to yours
const char* ssid     = "your access point's ssid";
const char* password = "your access point's password";

// use demo token or change to your token
const char* token = "Y9hHIBjdwPEOZo6c7SafNiz3X0snuJLRTFqgDKrU";
// use demo thing or change to your thing
const char* thing = "weather_station";
// use demo username or change to your username
const char *user = "WHCWHC78";

void setup() {
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network

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

int value = 0;

void loop() {
    delay(5000);
    ++value;

// if value is even then change 'input' channel to LOW and 'analog' channel to 1234.
// if value is odd then change 'input' channel to HIGH and 'analog' channel to 5678

    if ((value%2 == 0? Anto.digitalUpdate("input", LOW): Anto.digitalUpdate("input", HIGH))) {
        Serial.println("Digital updating success");
    }
    else Serial.println("Digital updating failed");

    if ((value%2 == 0? Anto.analogUpdate("analog", 1234): Anto.analogUpdate("analog", 5678))) {
        Serial.println("analog updating success");
    }
    else Serial.println("analog updating failed");

    if ((value%2 == 0? Anto.stringUpdate("Name", "kohpai"): Anto.stringUpdate("Name", "farm"))) {
        Serial.println("string updating success");
    }
    else Serial.println("string updating failed");

    Serial.print("Digital: ");

// get 'input' channel
    Serial.println((Anto.digitalGet("input")? "HIGH":"LOW"));
    Serial.print("Analog: ");

// get 'analog' channel
    Serial.println(Anto.analogGet("analog"));
    Serial.print("String: ");

// get 'Name' channel
    Serial.println(Anto.stringGet("Name"));

    Serial.println(value);


}

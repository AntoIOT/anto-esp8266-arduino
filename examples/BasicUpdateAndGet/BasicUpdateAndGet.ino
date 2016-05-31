/*
 * This is the example of using AntoIO library to 
 * Update and get digital 'channel' from dev-api.anto.io.
 * 
 * by Anto.io
 */

#include <AntoIO.h>

// username of anto.io account
const char *user = "WHCWHC78";

// key of permission, generated on control panel anto.io
const char* key = "Y9hHIBjdwPEOZo6c7SafNiz3X0snuJLRTFqgDKrU";

// your default thing.
const char* thing = "weather_station";

// create AntoIO object named anto.
// using constructor AntoIO(user, key, thing)
// or use AntoIO(user, key, thing, clientId)
// to generate client_id yourself.
AntoIO anto(user, key, thing);

int value = 0;

void setup() {
    // SSID and Password of your WiFi access point.
    const char* ssid = "ssid";
    const char* pwd  = "pwd";

    Serial.begin(115200);
    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Anto library version: ");
    Serial.println(anto.getVersion());
    Serial.print("Connecting to ");
    Serial.println(ssid);

    // Connect to your WiFi access point
    if (!anto.begin(ssid, pwd)) {
        Serial.println("Connection failed!!");

        // Stop everything.
        while (1);
    }

    Serial.println();
    Serial.println("WiFi connected");  
}

void loop() {
    delay(5000);
    ++value;

    if (value % 2 == 0) {

        // Update the channels value
        anto.digitalUpdate("input", LOW);
        anto.analogUpdate("analog", 1234);
        anto.stringUpdate("name", "kohpai");
    }
    else {
        anto.digitalUpdate("input", HIGH);
        anto.analogUpdate("analog", 5678);
        anto.stringUpdate("name", "farm");
    }

    Serial.print("Digital: ");

    // Get the channels value
    Serial.println((anto.digitalGet("input")));

    Serial.print("Analog: ");
    Serial.println(anto.analogGet("analog"));

    Serial.print("String: ");
    Serial.println(anto.stringGet("Name"));

    Serial.println(value);


}

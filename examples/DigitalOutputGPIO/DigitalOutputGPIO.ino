/*
 * This is the example of using AntoIO library to 
 * Update and get digital 'channel' from dev-api.anto.io.
 * 
 * by Anto.io
 */

#include <AntoIO.h>

/* see NodeMCU v1.0 pinout for more GPIO port details. */
#define LED0 16 // D0
#define LED1 5  // D1
#define LED2 4  // D2
#define LED3 0  // D3

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


    Serial.println(value);
}

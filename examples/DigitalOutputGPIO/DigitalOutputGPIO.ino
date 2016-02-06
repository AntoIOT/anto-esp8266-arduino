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

// change ssid and password to yours
const char* ssid     = "your access point's ssid";
const char* password = "your access point's password";

// use demo token or change to your token
const char* token = "79HFgUJcpQu2OIGhZeMwXR1arybqv3SAfmnkYjoK";
// use demo thing or change to your thing
const char* thing = "smart_plug";
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

    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

int value = 0;

void loop() {
    ++value;

    bool var = LOW;

/*Get 'out0' channel*/
    var = Anto.digitalGet("out0");
    
    digitalWrite(LED0, var);

    if (var == LOW)
        Serial.println("out0: LOW");
    else
        Serial.println("out0: HIGH");

/*Get 'out1' channel*/
    var = Anto.digitalGet("out1");

    digitalWrite(LED1, var);

    if (var == LOW)
        Serial.println("out1: LOW");
    else
        Serial.println("out1: HIGH");

/*Get 'out2' channel*/
    var = Anto.digitalGet("out2");

    digitalWrite(LED2, var);

    if (var == LOW)
        Serial.println("out2: LOW");
    else
        Serial.println("out2: HIGH");
    
/*Get 'out3' channel*/
    var = Anto.digitalGet("out3");

    digitalWrite(LED3, var);

    if (var == LOW)
        Serial.println("out3: LOW");
    else
        Serial.println("out3: HIGH");

    Serial.println(value);
}

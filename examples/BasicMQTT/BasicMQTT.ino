/*
 * This is the example of using AntoIO library to 
 * Update and get digital 'channel' from service.anto.io using MQTT.
 * 
 * by Anto.io
 */

#include <AntoIO.h>

// change ssid and password to yours
const char* ssid     = "ssid";
const char* password = "ssid password";

// use demo token or change to your token
const char* token = "Y9hHIBjdwPEOZo6c7SafNiz3X0snuJLRTFqgDKrU";
// use demo thing or change to your thing
const char* thing = "weather_station";
// use demo username or change to your username
const char *user = "WHCWHC78";

int value = 0;
bool bIsConnected = false;

void setup() {
    Serial.begin(115200);
    delay(10);

    // register callback functions

    Anto.onConnected(connectedCB);
    Anto.onDisconnected(disconnectedCB);
    Anto.onMsgArrv(msgArrvCB);
    Anto.onPublished(publishedCB);
    
    // Connect to a WiFi network and MQTT broker

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
    Serial.println("Connecting to MQTT broker");
}

void loop() {
    delay(5000);
    ++value;

    if (bIsConnected) { // If the connection is establised, publish the messages.
        Serial.println("test");
        Anto.pub("analog", (value % 2 == 0 ? "1234" : "5678"));
        Anto.pub("Name", (value % 2 == 0 ? "Kohpai" : "Farm"));
        Anto.pub("input", (value % 2 == 0 ? "1" : "0")); 
        
        Serial.println(value);
    }
    else { // If disconnected from server, reconnect.
        Serial.println("failed");
        Anto.connect();
    }
}

/*
* connectedCB(): a callback function called when the connection to the MQTT broker is establised.
*/
void connectedCB()
{   
    // If the connection is establised, subscribe channels.

    bIsConnected = true;
    Serial.println("Connected to MQTT Broker");
    
    Anto.sub("analog");
    Anto.sub("Name");
    Anto.sub("input");
}

/*
* disconnectedCB(): a callback function called when the connection to the MQTT broker is broken.
*/
void disconnectedCB()
{   
    bIsConnected = false;
    Serial.println("Disconnected to MQTT Broker");
}

/*
* msgArrvCB(): a callback function called when there a message from the subscribed channel.
*/
void msgArrvCB(String& topic, String& msg)
{
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(msg);
}

/*
* publishedCB(): a callback function called when the message is published.
*/
void publishedCB(void)
{
    Serial.println("published");
}

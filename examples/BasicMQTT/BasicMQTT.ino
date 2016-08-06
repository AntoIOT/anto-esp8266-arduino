/*
 * This is the example of using Anto.io library to 
 * Use basic function of MQTT protocol
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

bool bIsConnected = false;
int value = 0;

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
	anto.on("dataReceived", onDataReceivedFunc);
	anto.on("published", onPublishedFunc);
    anto.connectMQTT(); // Connect to Anto MQTT broker
}

void loop() {
    // wait for connection of broker
    delay(5000);
    ++value;

    // If the connection is establised, publish the messages.
    if (bIsConnected) {
        // String form of topic: name
        String sname("name");

        // String form of message: kohpai
        String smsg("kohpai");

        // String form of topic: analog
        String sanalog("analog");

        // String form of topic: input
        String sinput("input");
        
        if (value % 2 == 0) {
            // pub(channel, value, QOS, retain)
            // where QOS is 0, 1, or 2
            // and retain is true or false
            anto.pub("analog", "1234", 1, true);

            // publish message in String form
            // default retain is false
            anto.pub(sname, smsg, 2);

            // default QOS is 0
            anto.pub("input", 1, true); 
        }
        else {
            // publish message in integer form.
            // equals to anto.pub("analog", "5678", 0)
            anto.pub(sanalog, 5678, 0);

            // equals to anto.pub("name", "Farm", 2, false)
            anto.pub(sname, "Farm", 2, false);

            // publish message in character form.
            // equals to anto.pub("input", "0", true);
            anto.pub(sinput, '0', true); 
        }
        
        Serial.println(value);
    }
    // If disconnected from server, reconnect.
    else {
        anto.connectMQTT();
    }
}

/*
* onConnectedFunc(): a callback function called when the connection to the MQTT broker is established.
*/
void onConnectedFunc()
{   
    bIsConnected = true;
    Serial.println("Connected to Anto MQTT Broker");
    
    // If the connection is established, subscribe channels
    // by using sub(channel, QOS) 
    // where QOS is 0, 1, or 2
    anto.sub("analog", 1);
    anto.sub("name", 2);

    // default QOS is 0.
    anto.sub("input");
}

/*
* onDisconnectedFunc(): a callback function called when the connection to the MQTT broker is broken.
*/
void onDisconnectedFunc()
{   
    bIsConnected = false;
    Serial.println("Disconnected from Anto MQTT Broker");
}

/*
* onDataReceivedFunc(): a callback function called when received a message from the subscribed channel.
*/
void onDataReceivedFunc(String& thing, String& channel, String& msg)
{
    Serial.println(thing);
    Serial.println(channel);
    Serial.println(msg);
    Serial.println();
}

/*
* onPublishedFunc(): a callback function called when the message is published.
*/
void onPublishedFunc()
{
    Serial.println("Message is published");
}
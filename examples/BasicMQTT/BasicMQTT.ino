/*
 * This is the example of using AntoIO library to 
 * Update and get digital 'channel' from service.anto.io using MQTT.
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
bool bIsConnected = false;

void setup() {
    // SSID and Password of your WiFi access point.
    const char* ssid = "AndroidAP";
    const char* pwd  = "12345678";

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
    Serial.println("Connecting to MQTT broker");
    
    // register callback functions
    anto.mqtt.onConnected(connectedCB);
    anto.mqtt.onDisconnected(disconnectedCB);
    anto.mqtt.onData(dataCB);
    anto.mqtt.onPublished(publishedCB);
    
    // Connect to Anto.io MQTT broker
    anto.mqtt.connect();
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
        Serial.println("failed");
        anto.mqtt.connect();
    }
}

/*
* connectedCB(): a callback function called when the connection to the MQTT broker is establised.
*/
void connectedCB()
{   
    bIsConnected = true;
    Serial.println("Connected to MQTT Broker");
    
    // If the connection is establised, subscribe channels
    // by using sub(channel, QOS) 
    // where QOS is 0, 1, or 2
    anto.sub("analog", 1);
    anto.sub("name", 2);

    // default QOS is 0.
    anto.sub("input");
    anto.service("gas.91e10.price");
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
* dataCB(): a callback function called when there a message from the subscribed channel.
*/
void dataCB(String& topic, String& msg)
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

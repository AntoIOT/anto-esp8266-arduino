#include <AntoIO.h>
#include <DHT.h>

// username of anto.io account
const char *user = "thefarmer";

// key of permission, generated on control panel anto.io
const char* key = "key";

// your default thing.
const char* thing = "Node_DHT";

// create AntoIO object named anto.
// using constructor AntoIO(user, key, thing)
// or use AntoIO(user, key, thing, clientId)
// to generate client_id yourself.
AntoIO anto(user, key, thing);

bool bIsConnected = false;

String Antosend;
char buf[5];

#define DHTPIN 2    //port D4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

void setup() {
    Serial.begin(115200);
    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Anto library version: ");
    Serial.println(anto.getVersion());


    // Connect to your WiFi access point
    anto.smartConfig();

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

    //dht start
    dht.begin();
}


void loop() {
  // put your main code here, to run repeatedly:
   float temp = dht.readTemperature();
   float humid = dht.readHumidity();
   
   Serial.print("TEMP: ");
   Serial.println(temp);

   Serial.print("HUMID: ");
   Serial.println(humid);  
   

   if(temp >= 0){
      anto.pub("Temp",temp);           //ใช้ buf ส่งค่าขึ้นไป
   }

   if(humid >= 0){
      anto.pub("Humid",humid);
   }

  delay(1000);
}

/*
* connectedCB(): a callback function called when the connection to the MQTT broker is establised.
*/
void connectedCB()
{   
    // If the connection is establised, subscribe channels.

    bIsConnected = true;
    Serial.println("Connected to MQTT Broker");
    
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
void dataCB(String& topic, String& msg)
{
    uint8_t index = topic.indexOf('/');

    index = topic.indexOf('/', index + 1);
    index = topic.indexOf('/', index + 1);

    topic.remove(0, index + 1);
   
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






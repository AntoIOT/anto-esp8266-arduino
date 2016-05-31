
#include <AntoIO.h>

// username of anto.io account
const char *user = "user";

// key of permission, generated on control panel anto.io
const char* key = "key";

// your default thing.
const char* thing = "NodeMCU";

// create AntoIO object named anto.
// using constructor AntoIO(user, key, thing)
// or use AntoIO(user, key, thing, clientId)
// to generate client_id yourself.
AntoIO anto(user, key, thing);

bool bIsConnected = false;
int Led1,Led2,Led3 = 0;
int motor = 0;

void setup() {
    // SSID and Password of your WiFi access point.
    const char* ssid = "ssid";
    const char* pwd  = "pwd";

    Serial.begin(115200);
    delay(10);

    Serial.println();
    Serial.println();
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
  
    //port output
    pinMode(D1,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D3,OUTPUT);
}

void loop() {
    // if disconnected from broker, try to reconnect.
    if (!bIsConnected) {
        anto.mqtt.connect();
        delay(5000);
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
    anto.sub("LED1");
    anto.sub("LED2");
    anto.sub("LED3");
}

/*
* disconnectedCB(): a callback function called when the connection to the MQTT broker is broken.
*/
void disconnectedCB()
{   
    bIsConnected = false;
    Serial.println("Disconnected from MQTT Broker");
}

/*
* dataCB(): a callback function called when there a message from the subscribed channel.
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

    if(topic.equals("LED1")){
      motor = msg.toInt();
      if(motor == 1){
        digitalWrite(D1,HIGH);
      }
      else{
        digitalWrite(D1,LOW);
      }
      
    }
    else if(topic.equals("LED2")){
     motor = msg.toInt();
     if(motor == 1){
        digitalWrite(D2,HIGH);
      }
      else{
        digitalWrite(D2,LOW);
      }
    }
    else if(topic.equals("LED3")){
      motor = msg.toInt();
      if(motor == 1){
        digitalWrite(D3,HIGH);
      }
      else{
        digitalWrite(D3,LOW);
      }
    }
}

/*
* publishedCB(): a callback function called when the message is published.
*/
void publishedCB(void)
{
    Serial.println("published");
}






/*
 * This example is meant to be used as a starting point
 * for working with Anto.io services
 *
 * 2017/02/07
 * by Anto.io team
 *
 */

#include <AntoIO.h>

const char *ssid = "your access point SSID";
const char *pass = "access point password";
const char *user = "your username";
const char *token = "your token";
const char *thing = "your thing";

// initialize AntoIO instance
AntoIO anto(user, token, thing);

int Led1 = 0, Led2 = 0, Led3 = 0;
int value = 0;


void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Anto library version: ");
  Serial.println(anto.getVersion());


  Serial.print("\nTrying to connect ");
  Serial.print(ssid);
  Serial.println("...");

  while (!anto.wifi.begin(ssid, pass));
  Serial.println("\nConnected, trying to connect to broker...");

  while (!anto.mqtt.connect(user, token, true));
  Serial.println("\nConnected");

  //port output
  //pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);

  anto.mqtt.sub("LED1");
  anto.mqtt.sub("LED2");
  anto.mqtt.sub("LED3");
}

void loop() {
  anto.mqtt.loop();
  // this delay(10) is for proper functionality
  delay(10);

  if (!anto.mqtt.isConnected())
    Serial.println("Disconnected");
}


// a callback function for arriving data.
void messageReceived(String topic, String payload, char * bytes, unsigned int length)
{
    uint8_t index = topic.indexOf('/');

    index = topic.indexOf('/', index + 1);
    index = topic.indexOf('/', index + 1);

    topic.remove(0, index + 1);

    Serial.print(topic);
    Serial.print(": ");
    Serial.println(payload);

    if(topic.equals("LED1")){
      value = payload.toInt();
      if(value == 1){
        digitalWrite(D1,HIGH);
      }
      else{
        digitalWrite(D1,LOW);
      }

    }
    else if(topic.equals("LED2")){
     value = payload.toInt();
     if(value == 1){
        digitalWrite(D2,HIGH);
      }
      else{
        digitalWrite(D2,LOW);
      }
    }
    else if(topic.equals("LED3")){
      value = payload.toInt();
      if(value == 1){
        digitalWrite(D3,HIGH);
      }
      else{
        digitalWrite(D3,LOW);
      }
    }
}


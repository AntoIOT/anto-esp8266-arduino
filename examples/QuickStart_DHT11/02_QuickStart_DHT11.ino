/*
 * This example is meant to be used as a starting point
 * for working with Anto.io services and DHT sensor module
 *
 * 2017/06/17
 * by Anto.io team
 *
 */

#include <AntoIO.h>
#include <DHT.h>

#define DHTPIN 2    //port D4
#define DHTTYPE DHT11

const char *ssid = "your access point SSID";
const char *pass = "access point password";
const char *user = "your username";
const char *token = "your token";
const char *thing = "your thing";

// initialize AntoIO instance
AntoIO anto(user, token, thing);

//initialize dht instance
DHT dht(DHTPIN,DHTTYPE);

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

  anto.begin(ssid, pass, messageReceived);
  Serial.println("\nConnected Anto done");

  //dht start
  dht.begin();
}


void loop() {
  anto.mqtt.loop();

  if (!anto.mqtt.isConnected())
    Serial.println("Disconnected");

  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  Serial.print("TEMP: ");
  Serial.println(temp);

  Serial.print("HUMID: ");
  Serial.println(humid);

  if(temp >= 0){
     anto.pub("Temp",temp);           
  }

  if(humid >= 0){
     anto.pub("Humid",humid);
  }

  delay(1000);
}

// a callback function for arriving data.
void messageReceived(String thing, String channel, String payload) {
  Serial.print("Recieved: ");
  Serial.print(thing);
  Serial.print("/");
  Serial.print(channel);
  Serial.print("-> ");
  Serial.println(payload);
}


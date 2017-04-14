/*
 * This example is meant to be used as a starting point
 * for working with Anto.io services and DHT sensor module
 *
 * 2017/02/08
 * by Anto.io team
 *
 */

#include <AntoIO.h>
#include <DHT.h>

#define DHTPIN 2    //port D4
#define DHTTYPE DHT11

const char *user = "your username";
const char *token = "your token";
const char *thing = "your thing";

// initialize AntoIO instance
AntoIO anto(user, token, thing);

String Antosend;
char buf[5];

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Anto library version: ");
  Serial.println(anto.getVersion());


  // Connect to your WiFi access point
  anto.wifi.smartConfig();

  Serial.println();
  Serial.println("WiFi connected, trying to connect to broker...");

  while (!anto.mqtt.connect());
  Serial.println("\nConnected");

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
     anto.mqtt.pub("Temp",temp);           //ใช้ buf ส่งค่าขึ้นไป
  }

  if(humid >= 0){
     anto.mqtt.pub("Humid",humid);
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


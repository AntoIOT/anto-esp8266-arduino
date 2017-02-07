/*
 * This example is meant to be used as a starting point
 * for working with MQTT publish and subscribe
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
// for counting how many loop has passed
uint8_t loopCount = 0;

void setup() {
  Serial.begin(9600);

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

  anto.mqtt.sub("channel");
}

void loop() {
  anto.mqtt.loop();
  // this delay(10) is for proper functionality
  delay(10);

  ++loopCount;

  // if this NodeMCU is connected to Anto broker
  // then publish 'value' to 'other_channel'
  if (anto.mqtt.isConnected()) {
    // if 'loopCount' is even number, update 'other_channel' channel to 'other_value'
    // otherwise, update it to 'value'
    anto.mqtt.pub("other_channel", (loopCount % 2 ? "value" : "other_value"));
  } else {
    Serial.println("Disconnected");
  }

  delay(3000);
}

// a callback function for arriving data.
void messageReceived(String topic, String payload, char * bytes, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}

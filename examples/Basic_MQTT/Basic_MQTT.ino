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

AntoIO anto(user, token, thing);

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

  // the last boolean argument is for indicating
  // that you want this connection to be secured
  // by TLS or not.
  //
  // Secured connection will be
  // slower than secured one.
  while (!anto.mqtt.connect(true));
  Serial.println("\nConnected");

  anto.mqtt.onData(messageReceived);
  anto.mqtt.sub("channel");
}

void loop() {
  anto.mqtt.loop();

  ++loopCount;

  anto.mqtt.pub("other_channel", (loopCount % 2 ? "value" : "other_value"));

  delay(3000);
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

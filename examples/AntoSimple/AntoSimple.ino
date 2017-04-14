/*
 * This example is meant to be used for beginner
 *
 * 2017/04/14
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

void setup() {
  Serial.begin(9600);
  anto.begin(ssid, pass, messageReceived);
  anto.sub("channel");
}

void loop() {
  anto.loop();
  anto.pub("other channel", 1);

  delay(3000);
}

void messageReceived(String thing, String channel, String payload) {
  Serial.print("Recieved: ");
  Serial.print(thing);
  Serial.print("/");
  Serial.print(channel);
  Serial.print("-> ");
  Serial.println(payload);
}

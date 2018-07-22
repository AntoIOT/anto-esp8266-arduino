/*
 * This example is meant to be used as a starting point
 * for working with HTTP request
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
  Serial.println("\nConnected");
}

void loop() {
  ++loopCount;

  // test updating digital, analog and string value
  testUpdateDigital(loopCount);
  testUpdateAnalog(loopCount);
  testUpdateString(loopCount);
  delay(3000);

  // test reading digital, analog and string value
  testGetDigital();
  testGetAnalog();
  testGetString();
  delay(3000);

  // test requesting data service
  testService();
  delay(3000);
}

void testService(void)
{
  String str;

  Serial.println("requesting 'gas.95e20.price' data service ...");

  // request for gas.95e20.price data service
  // and store the service value in 'str'
  if (anto.http.request(str, "gas.95e20.price"))
    Serial.println(str);
  else
    Serial.println("Error");
}

void testUpdateDigital(uint8_t i)
{
  Serial.println("Updating 'your_digital_channel' channel ...");

  // if 'loopCount' is even number, update 'your_digital_channel' channel to 0
  // otherwise, update it to 1
  if (anto.http.digitalUpdate("your_digital_channel", (i % 2 ? 0 : 1)))
    Serial.println("Done");
  else
    Serial.println("Error");
}

void testUpdateAnalog(uint8_t i)
{
  Serial.println("Updating 'your_analog_channel' channel ...");

  // if 'loopCount' is even number, update 'your_analog_channel' channel to 1234
  // otherwise, update it to 5678
  if (anto.http.analogUpdate("your_analog_channel", (i % 2 ? 1234 : 5678)))
    Serial.println("Done");
  else
    Serial.println("Error");
}

void testUpdateString(uint8_t i)
{
  Serial.println("Updating 'your_string_channel' channel ...");

  // if 'loopCount' is even number, update 'your_string_channel' channel to Kohpai
  // otherwise, update it to George
  if (anto.http.stringUpdate("your_string_channel", (i % 2 ? "Kohpai" : "George")))
    Serial.println("Done");
  else
    Serial.println("Error");
}

void testGetDigital(void)
{
  bool i = 0;

  Serial.println("Getting 'your_digital_channel' channel ...");

  // get 'your_digital_channel' channel value and store it in 'i'
  if (anto.http.digitalGet(i, "your_digital_channel"))
    Serial.println(i);
  else
    Serial.println("Error");
}

void testGetAnalog(void)
{
  int32_t i;

  Serial.println("Getting 'your_analog_channel' channel ...");

  // get 'your_analog_channel' channel value and store it in 'i'
  if (anto.http.analogGet(i, "your_analog_channel"))
    Serial.println(i);
  else
    Serial.println("Error");
}

void testGetString(void)
{
  String str;

  Serial.println("Getting 'your_string_channel' channel ...");

  // get 'your_string_channel' channel value and store it in 'str'
  if (anto.http.stringGet(str, "your_string_channel"))
    Serial.println(str);
  else
    Serial.println("Error");
}

## Anto client library for ESP8266-Arduino
### This branch is a development on adopting Paho MQTT as a core library for MQTT

###### TODO ######
- Fix `AntoMQTT::messageHandler()` after reconnected from `AntoIO::mqtt.loop()`
- Other callback functions (OnPublished, OnDisconnected, OnConnected)
- Upload this library to Arduino repository
- Request via HTTPS
- Increase speed of keep-alive message
- Timer interrupt and remove `AntoMQTT::loop()`

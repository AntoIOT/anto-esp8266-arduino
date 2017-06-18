## 0.7.3 (2017-06-18)
* remove number from the names of example folders for library manager compatability
## 0.7.2 (2017-04-15)
* add shortcuts from AntoHTTP and AntoMQTT to AntoIO
## 0.7.1 (2017-04-10)
* add reconnect procedure inside `AntoMQTT::loop()`
## 0.7.0 (2017-04-10)
* distract arrived messages in `AntoMQTT::messageHandler()` into [thing, channel, payload]
## 0.6.4 (2017-04-10)
* add `AntoIO::begin()` to simplify the process
## 0.6.3 (2017-04-09)
* add `AntoIO::http.setHost()` and `AntoIO::mqtt.setHost()` functions to change URL of the server
## 0.6.2 (2017-04-09)
* remove username and password parameters from `AntoIO::mqtt.connect()`
## 0.6.1 (2017-04-09)
* MQTT over SSL/TLS supported
* New structure of the library
## 0.5.2 (2016-06-16)
* Add new overload methods for `AntoIO::pub()` (Integer, String, Character and Floating point)
* Edit example BasicMQTT
## 0.5.0 (2016-06-16)
* Add WiFi Manager (Smart config)
* Add example read temperature and humidity from DHT11 and send to server
## 0.4.1 (2016-05-31)
* Change client ID in MQTT connection
* Reformat API
* Add quick start anto example
## 0.3.0 (2016-05-30)
* Add MQTT subscribe or HTTP request for data service
## 0.2.0 (2016-04-23)
* Add MQTT client
* Modify HTTP request method
## 0.1.1 (2016-01-09)
* Delete internal libraries
## 0.1.0 (2015-11-28)
* Add Get/Set data channel via HTTP
* First release

#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#ifndef MQTT_BUFFER_SIZE
#define MQTT_BUFFER_SIZE 128
#endif

#define MQTTCLIENT_QOS1 0
#define MQTTCLIENT_QOS2 0

#include <Arduino.h>
#include <Client.h>
#include <Stream.h>
#include "lib/MQTTClient.h"
#include "Network.h"
#include "Timer.h"

typedef struct {
    char * topic;
    char * payload;
    unsigned int length;
    boolean retained;
} MQTTMessage;

template <class AntoMQTT>
class MQTTClient {
private:
  Network network;
  MQTT::Client<Network, Timer, AntoMQTT, MQTT_BUFFER_SIZE, 0> * client;
  MQTTPacket_connectData options;
  const char * hostname;
  int port;
  void MQTTClient_messageHandler(MQTT::MessageData &messageData);
public:
  MQTTClient();
  boolean begin(const char * hostname, Client& client, AntoMQTT *antoMqtt, void (AntoMQTT::*messageHandler) (MQTT::MessageData&));
  boolean begin(const char * hostname, int port, Client& client, AntoMQTT *antoMqtt, void (AntoMQTT::*messageHandler) (MQTT::MessageData&));
  void setWill(const char * topic);
  void setWill(const char * topic, const char * payload);
  boolean connect(const char * clientId);
  boolean connect(const char * clientId, const char* username, const char* password);
  boolean publish(String topic);
  boolean publish(String topic, String payload);
  boolean publish(const char * topic, String payload);
  boolean publish(const char * topic, const char * payload);
  boolean publish(const char * topic, char * payload, unsigned int length);
  boolean publish(MQTTMessage * message);
  boolean subscribe(String topic, AntoMQTT *antoMqtt);
  boolean subscribe(const char * topic, AntoMQTT *antoMqtt);
  boolean unsubscribe(String topic);
  boolean unsubscribe(const char * topic);
  void loop();
  boolean connected();
  boolean disconnect();
};

template<class AntoMQTT>
MQTTClient<AntoMQTT>::MQTTClient() {}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::begin(const char * hostname, Client& client, AntoMQTT *antoMqtt, void (AntoMQTT::*messageHandler) (MQTT::MessageData&)) {
  return this->begin(hostname, 1883, client, antoMqtt, messageHandler);
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::begin(const char * _hostname, int _port, Client& _client, AntoMQTT *antoMqtt, void (AntoMQTT::*messageHandler) (MQTT::MessageData&)) {
  this->client = new MQTT::Client<Network, Timer, AntoMQTT, MQTT_BUFFER_SIZE, 0>(this->network);
  this->network.setClient(&_client);
  this->client->setDefaultMessageHandler(antoMqtt, messageHandler);
  this->hostname = _hostname;
  this->port = _port;
  this->options = MQTTPacket_connectData_initializer;

  return true;
}

template<class AntoMQTT>
void MQTTClient<AntoMQTT>::setWill(const char * topic) {
  this->setWill(topic, "");
}

template<class AntoMQTT>
void MQTTClient<AntoMQTT>::setWill(const char * topic, const char * payload) {
  this->options.willFlag = 0x1;
  this->options.will.topicName.cstring = (char*)topic;
  this->options.will.message.cstring = (char*)payload;
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::connect(const char * clientId) {
  return this->connect(clientId, NULL, NULL);
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::connect(const char * clientId, const char * username, const char * password) {
  if(!this->network.connect((char*)this->hostname, this->port)) {
    return false;
  }

  this->options.clientID.cstring = (char*)clientId;
  if(username && password) {
    this->options.username.cstring = (char*)username;
    this->options.password.cstring = (char*)password;
  }

  return this->client->connect(this->options) == MQTT::SUCCESS;
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::publish(String topic) {
  return this->publish(topic.c_str(), "");
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::publish(String topic, String payload) {
  return this->publish(topic.c_str(), payload.c_str());
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::publish(const char * topic, String payload) {
  return this->publish(topic, payload.c_str());
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::publish(const char * topic, const char * payload) {
  return this->publish(topic, (char*)payload, (unsigned int)strlen(payload));
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::publish(const char * topic, char * payload, unsigned int length) {
  MQTT::Message message;
  message.qos = MQTT::QOS0;
  message.retained = false;
  message.dup = false;
  message.payload = payload;
  message.payloadlen = length;

  return client->publish(topic, message) == MQTT::SUCCESS;
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::publish(MQTTMessage * message) {
  MQTT::Message _message;
  _message.qos = MQTT::QOS0;
  _message.retained = message->retained;
  _message.dup = false;
  _message.payload = message->payload;
  _message.payloadlen = message->length;

  return client->publish(message->topic, _message) == MQTT::SUCCESS;
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::subscribe(String topic, AntoMQTT *antoMqtt) {
  return this->subscribe(topic.c_str(), antoMqtt);
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::subscribe(const char * topic, AntoMQTT *antoMqtt) {
  return client->subscribe(topic, MQTT::QOS0, antoMqtt, NULL) == MQTT::SUCCESS;
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::unsubscribe(String topic) {
  return this->unsubscribe(topic.c_str());
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::unsubscribe(const char * topic) {
  return client->unsubscribe(topic) == MQTT::SUCCESS;
}

template<class AntoMQTT>
void MQTTClient<AntoMQTT>::loop() {
  if(!this->network.connected() && this->client->isConnected()) {
    // the following call will not send a packet but reset the instance
    // to allow proper reconnection
    this->client->disconnect();
  }

  this->client->yield();
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::connected() {
  return this->client->isConnected();
}

template<class AntoMQTT>
boolean MQTTClient<AntoMQTT>::disconnect() {
  return this->client->disconnect() == MQTT::SUCCESS;
}

#endif

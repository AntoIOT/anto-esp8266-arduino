#ifndef ANTO_MQTT_H
#define ANTO_MQTT_H

#include <WiFiClientSecure.h>
#include <WiFiClient.h>

#include "mqtt/MQTTClient.h"

class AntoMQTT
{
    public:
        AntoMQTT(const char *user, const char *token, const char *thing):
            _mqtt(), _nets(), _net(), _user(user),
            _token(token), _thing(thing), _onData(NULL)
    {
        _host = (char *) malloc(sizeof("service.anto.io"));
        strcpy(_host, "service.anto.io");
    }

        void loop(void)
        {
            this->_mqtt.loop();
        }

        void onData(void (*_onData) (String, String, char*, unsigned int))
        {
            this->_onData = _onData;
        }

        bool disconnect(void)
        {
            return this->_mqtt.disconnect();
        }

        bool isConnected(void)
        {
            return this->_mqtt.connected();
        }

        bool connect( bool secure = false, const char * client_id = ""),

             pub(const char *channel, const char *msg,
                     int qos = 0, bool retain = false),
             pub(const char *channel, String& msg,
                     int qos = 0, bool retain = false),
             pub(String& channel, const char *msg,
                     int qos = 0, bool retain = false),
             pub(String& channel, String& msg,
                     int qos = 0, bool retain = false),
             pub(const char *channel, int msg,
                     int qos = 0, bool retain = false),
             pub(String& channel, int msg,
                     int qos = 0, bool retain = false),
             pub(const char *channel, double msg,
                     int qos = 0, bool retain = false),
             pub(String& channel, double msg,
                     int qos = 0, bool retain = false),
             pub(const char *thing, const char *channel, const char *msg,
                     int qos = 0, bool retain = false),
             pub(String& thing, String& channel, String& msg,
                     int qos = 0, bool retain = false),

             sub(const char *channel, int qos = 0),
             sub(String& channel, int qos = 0),
             sub(const char *thing, const char *channel, int qos = 0),
             sub(String& thing, String& channel, int qos = 0),

             service(const char *name, int qos = 0);

        void setHost(const char *host)
        {
            free(_host);

            _host = (char *) malloc(sizeof(host));
            strcpy(_host, host);
        }

    private:
        MQTTClient<AntoMQTT>    _mqtt;
        WiFiClientSecure        _nets;
        WiFiClient              _net;

        void MQTTClient_messageHandler(MQTT::MessageData &messageData);

        const char
            *_user,
            *_token,
            *_thing;

        char *_host;

        void (*_onData) (String, String, char*, unsigned int);
};

#endif

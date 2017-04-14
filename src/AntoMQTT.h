#ifndef ANTO_MQTT_H
#define ANTO_MQTT_H

#include <WiFiClientSecure.h>
#include <WiFiClient.h>

#include "mqtt/MQTTClient.h"

typedef void (*onMsg) (String, String, String);

class AntoMQTT
{
    public:
        AntoMQTT(const char *user, const char *token, const char *thing):
            _mqtt(), _nets(), _net(), _user(user),
            _token(token), _thing(thing),_lastConnSecure(false),
            _onData(NULL)
    {
        _host = (char *) malloc(sizeof("service.anto.io"));
        strcpy(_host, "service.anto.io");

        _lastConnClientId = (char *) malloc(1);
        *_lastConnClientId = '\0';
    }

        void loop(void)
        {
            this->_mqtt.loop();

            if (!(this->_mqtt.connected()))
                while (!this->connect(_lastConnSecure, _lastConnClientId))
                    delay(500);

            delay(100);
        }

        void onData(onMsg onData)
        {
            this->_onData = onData;
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

        void messageHandler(MQTT::MessageData &messageData);

        const char
            *_user,
            *_token,
            *_thing;

        char
            *_host,
            *_lastConnClientId;

        bool _lastConnSecure;

        onMsg _onData;
};

#endif

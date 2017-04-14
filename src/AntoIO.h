#ifndef ANTO_IO_H
#define ANTO_IO_H

#include "AntoMQTT.h"
#include "AntoWiFi.h"
#include "AntoHTTP.h"
#include "AntoCommon.h"

class AntoIO
{
    public:
        AntoMQTT mqtt;
        AntoWiFi wifi;
        AntoHTTP http;

        AntoIO(const char *user, const char *token, const char *thing):
            _user(user),
            _token(token),
            _thing(thing),
            mqtt(user, token, thing),
            http(token, thing),
            wifi()
        { }

        const char* getVersion(void);

        void begin(
                     const char *ssid,
                     const char* pwd,
                     onMsg onData,
                     bool secure = false);

        /* ============= START OF HTTP SECION ============= */

        bool digitalUpdate(const char* channel, bool value)
        {
            return this->http.digitalUpdate(channel, value);
        }

        bool digitalUpdate(const char* thing, const char* channel, bool value)
        {
            return this->http.digitalUpdate(thing, channel, value);
        }

        bool analogUpdate(const char* channel, int32_t value)
        {
            return this->http.analogUpdate(channel, value);
        }

        bool analogUpdate(
                const char* thing,
                const char* channel,
                int32_t value)
        {
            return this->http.analogUpdate(thing, channel, value);
        }

        bool stringUpdate(const char* channel, const char* value)
        {
            return this->http.stringUpdate(channel, value);
        }

        bool stringUpdate(
                const char* thing,
                const char* channel,
                const char* value)
        {
            return this->http.stringUpdate(thing, channel, value);
        }

        bool digitalGet(bool &val, const char* channel)
        {
            return this->http.digitalGet(val, channel);
        }

        bool digitalGet(bool &val, const char* thing, const char* channel)
        {
            return this->http.digitalGet(val, thing, channel);
        }

        bool analogGet(int32_t &val, const char* channel)
        {
            return this->http.analogGet(val, channel);
        }

        bool analogGet(int32_t &val, const char* thing, const char* channel)
        {
            return this->http.analogGet(val, thing, channel);
        }

        bool stringGet(String &val, const char* channel)
        {
            return this->http.stringGet(val, channel);
        }

        bool stringGet(String &val, const char* thing, const char* channel)
        {
            return this->http.stringGet(val, thing, channel);
        }

        bool request(String &val, const char *arg)
        {
            return this->http.request(val, arg);
        }

        bool httpRequest(String &result, const char *host, String arg)
        {
            return this->http.httpRequest(result, host, arg);
        }

        void removeHeader(String &str)
        {
            this->http.removeHeader(str);
        }

        /* ============= END OF HTTP SECION ============= */

        /* ============= START OF MQTT SECION ============= */

        void loop(void) { this->mqtt.loop(); }

        void onData(onMsg onData) { this->mqtt.onData(onData); }

        bool disconnect(void) { return this->mqtt.disconnect(); }

        bool isConnected(void) { return this->mqtt.isConnected(); }

        bool connect( bool secure = false, const char * client_id = "")
        {
            return this->mqtt.connect(secure, client_id);
        }

        bool pub(const char *channel, const char *msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(channel, msg, qos, retain);
        }

        bool pub(const char *channel, String& msg,
                int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(channel, msg, qos, retain);
        }

        bool pub(String& channel, const char *msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(channel, msg, qos, retain);
        }

        bool pub(String& channel, String& msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(channel, msg, qos, retain);
        }

        bool pub(const char *channel, int msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(channel, msg, qos, retain);
        }

        bool pub(String& channel, int msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(channel, msg, qos, retain);
        }

        bool pub(const char *channel, double msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(channel, msg, qos, retain);
        }

        bool pub(String& channel, double msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(channel, msg, qos, retain);
        }

        bool pub(const char *thing, const char *channel, const char *msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(thing, channel, msg, qos, retain);
        }

        bool pub(String& thing, String& channel, String& msg,
                     int qos = 0, bool retain = false)
        {
            return this->mqtt.pub(thing, channel, msg, qos, retain);
        }

        bool sub(const char *channel, int qos = 0)
        {
            return this->mqtt.sub(channel, qos);
        }

        bool sub(String& channel, int qos = 0)
        {
            return this->mqtt.sub(channel, qos);
        }

        bool sub(const char *thing, const char *channel, int qos = 0)
        {
            return this->mqtt.sub(thing, channel, qos);
        }

        bool sub(String& thing, String& channel, int qos = 0)
        {
            return this->mqtt.sub(thing, channel, qos);
        }

        bool service(const char *name, int qos = 0)
        {
            return this->mqtt.service(name, qos);
        }

        /* ============= START OF MQTT SECION ============= */


    private:
        void printArtWork(void);

        const char
            *_user,
            *_token,
            *_thing;
};

#endif

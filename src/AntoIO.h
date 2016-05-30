/*
 * Anto.io - The easiest ESP8266 library for Arduino IDE
 *
 * by Anto.io
 * 13/09/2015
*/

#ifndef ANTO_IO_H
#define ANTO_IO_H

#include "mqtt/MQTT.h"

class AntoIO
{
public:

    AntoIO();

    bool 
        begin(char* ssid, char *passphrase, char* token, char* user, char* defaultThing),
        begin(const char* ssid, const char *passphrase, const char* token, const char* user, const char* defaultThing),

        digitalUpdate(const char* channel, bool value),
        digitalUpdate(const char* thing, const char* channel, bool value),

        analogUpdate(const char* channel, int32_t value),
        analogUpdate(const char* thing, const char* channel, int32_t value),

        stringUpdate(const char* channel, const char* value),
        stringUpdate(const char* thing, const char* channel, const char* value),

        digitalGet(const char* channel),
        digitalGet(const char* thing,const char* channel),

        isConnected(void);

    int32_t
        analogGet(const char* channel),
        analogGet(const char* thing,const char* channel);

    String 
        stringGet(const char* channel),
        stringGet(const char* thing,const char* channel),

        requestHttp(const char*, String arg),
        request(const char *arg);

    void 
        pub(const char *channel, const char *msg),
        pub(const char *thing, const char *channel, const char *msg),

        sub(const char *channel),
        sub(const char *thing, const char *channel),

        service(const char *name),
        
        connect(void),
        onConnected(void (*)(void)),
        onDisconnected(void (*)(void)),
        onMsgArrv(void (*)(String&, String&)),
        onPublished(void (*)(void));

private:
    void disconnectedCB(void);

    const char
        *_host,
        *_broker,
        *_token,
        *_user,
        *_getParam,
        *_setParam,
        *_defaultThing;

    MQTT _myMqtt;

    String 
        responseFilter(String str),
        getStringValue(String json);

    bool
        isResponseSuccess(String json),
        getDigitalValue(String json);

    const uint16_t
        _PORT = 1883;

    int32_t
        getAnalogValue(String json);
};

extern AntoIO Anto;

#endif

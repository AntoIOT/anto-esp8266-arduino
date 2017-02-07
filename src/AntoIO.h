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

        const char* getVersion(void)
        {
            static const char *ver = ANTO_VER;

            return ver;
        }

    private:
        const char
            *_user,
            *_token,
            *_thing;
};

#endif

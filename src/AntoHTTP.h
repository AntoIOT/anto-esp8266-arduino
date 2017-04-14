#ifndef ANTO_HTTP_H
#define ANTO_HTTP_H

#include <Arduino.h>

class AntoHTTP
{
    public:
        AntoHTTP(const char *token, const char *thing):
            _token(token), _thing(thing)
    {
        _host = (char *) malloc(sizeof("api.anto.io"));
        strcpy(_host, "api.anto.io");
    }

        bool digitalUpdate(const char* channel, bool value)
        {
            return digitalUpdate(_thing, channel, value);
        }

        bool digitalUpdate(const char* thing, const char* channel, bool value);

        bool analogUpdate(const char* channel, int32_t value)
        {
            return analogUpdate(_thing, channel, value);
        }

        bool analogUpdate(
                const char* thing,
                const char* channel,
                int32_t value);

        bool stringUpdate(const char* channel, const char* value)
        {
            return stringUpdate(_thing, channel, value);
        }

        bool stringUpdate(
                const char* thing,
                const char* channel,
                const char* value);

        bool digitalGet(bool &val, const char* channel)
        {
            return digitalGet(val, _thing, channel);
        }

        bool digitalGet(bool &val, const char* thing, const char* channel);

        bool analogGet(int32_t &val, const char* channel)
        {
            return analogGet(val, _thing, channel);
        }

        bool analogGet(int32_t &val, const char* thing, const char* channel);

        bool stringGet(String &val, const char* channel)
        {
            return stringGet(val, _thing, channel);
        }

        bool stringGet(String &val, const char* thing, const char* channel);
        bool request(String &val, const char *arg);
        bool httpRequest(String &result, const char *host, String arg);
        void removeHeader(String &str);

        void setHost(const char *host)
        {
            free(_host);

            _host = (char *) malloc(sizeof(host));
            strcpy(_host, host);
        }

    private:
        bool isResponseSuccess(String json);

        const char
            *_token,
            *_thing;

        char *_host;

};

#endif /* ifndef ANTO_HTTP_H */

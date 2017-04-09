#include <WiFiClient.h>

#include "json/ArduinoJson.h"
#include "AntoHTTP.h"

#define ANTO_GET    "/channel/get/"
#define ANTO_SET    "/channel/set/"

bool AntoHTTP::digitalUpdate(
        const char* thing,
        const char* channel,
        bool value)
{
    String str;
    String arg;

    arg = String(ANTO_SET) +
        _token+ "/" +
        thing+ "/" +
        channel + "/" +
        (value ? "1" : "0");

    if (!httpRequest(str, _host, arg))
        return false;

    removeHeader(str);

    if (isResponseSuccess(str))
        return true;
    else
        return false;
}

bool AntoHTTP::analogUpdate(
        const char* thing,
        const char* channel,
        int32_t value)
{
    String str;
    String arg;

    arg = String(ANTO_SET) +
        _token + "/" +
        thing + "/" +
        channel + "/" +
        String(value);

    if (!httpRequest(str, _host, arg))
        return false;

    removeHeader(str);

    if (isResponseSuccess(str))
        return true;
    else
        return false;
}


bool AntoHTTP::stringUpdate(
        const char* thing,
        const char* channel,
        const char* value)
{
    String str;
    String arg;

    arg = String(ANTO_SET) +
        _token + "/" +
        thing + "/" +
        channel + "/" + value;

    if (!httpRequest(str, _host, arg))
        return false;

    removeHeader(str);

    if (isResponseSuccess(str))
        return true;
    else
        return false;
}

bool AntoHTTP::digitalGet(bool &val, const char* thing, const char* channel)
{
    String str;
    String arg;
    StaticJsonBuffer<200> jsonBuffer;

    arg = String(ANTO_GET) +
        _token + "/" +
        thing + "/" +
        channel;

    if (!httpRequest(str, _host, arg))
        return false;

    removeHeader(str);
    JsonObject& root = jsonBuffer.parseObject(str);

    if (!root.success())
        return false;

    if (root["result"] == true) {
        val = (root["value"] == 1);
        return true;
    } else {
        return false;
    }
}

bool AntoHTTP::analogGet(int32_t &val, const char* thing, const char* channel)
{
    String str;
    String arg;
    StaticJsonBuffer<200> jsonBuffer;

    arg = String(ANTO_GET) +
        _token + "/" +
        thing + "/" +
        channel;

    if (!httpRequest(str, _host, arg))
        return false;

    removeHeader(str);
    JsonObject& root = jsonBuffer.parseObject(str);

    if (!root.success())
        return false;

    if (root["result"] == true) {
        val = root["value"];
        return true;
    } else {
        return false;
    }
}

bool AntoHTTP::stringGet(String &val, const char* thing, const char* channel)
{
    String str;
    String arg;
    StaticJsonBuffer<200> jsonBuffer;

    val = String("");
    arg = String(ANTO_GET) +
        _token
        + "/" + thing
        + "/" + channel;

    if (!httpRequest(str, _host, arg))
        return false;

    removeHeader(str);
    JsonObject& root = jsonBuffer.parseObject(str);

    if (!root.success())
        return false;

    if (root["result"] == true) {
        val = String((const char*)root["value"]);
        return true;
    } else {
        return false;
    }
}

bool AntoHTTP::httpRequest(String &result, const char *host, String arg)
{
    WiFiClient client;
    uint8_t count;

    result = String("");

    for (count = 10; count && !client.connect(host, 80); --count);

    if (!count)
        return false;

    client.print(String("GET ")+arg+" HTTP/1.1\r\n"+"Host: "+host+"\r\n\r\n");

    for (count = 50; count && !client.available(); --count) delay(100);

    if (!count)
        return false;

    while (client.available())
        result += client.readStringUntil('\r');

    // return (str = removeHeader(str));
    return true;
}

bool AntoHTTP::request(String &val, const char *service)
{
    String str;
    String arg;
    StaticJsonBuffer<200> jsonBuffer;

    val = String("");
    arg = String("/request/") + _token + "/" + service;

    if (!httpRequest(str, _host, arg))
        return false;

    removeHeader(str);
    JsonObject& root = jsonBuffer.parseObject(str);

    if (!root.success())
        return false;

    if (root["result"] == true) {
        val = String((const char*)root["value"]);
        return true;
    } else {
        return false;
    }
}

void AntoHTTP::removeHeader(String &str)
{
    uint32_t index = str.indexOf("\n\n");

    str.remove(0, index + 2);
}

bool AntoHTTP::isResponseSuccess(String json)
{
    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success())
        return false;

    return root["result"];
}

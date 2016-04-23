#include "json/ArduinoJson.h"
#include "wifi/ESP8266WiFi.h"
#include "AntoIO.h"

AntoIO::AntoIO() : _host("api.anto.io"), _broker("service.anto.io"), _getParam("/channel/get/"),
    _setParam("/channel/set/"), _myMqtt("client1", "service.anto.io", 1883) {}

bool AntoIO::begin(char* ssid, char *passphrase, char* token, char* user, char* defaultThing)
{
    return begin((const char*)ssid, (const char*)passphrase, (const char*)token, (const char*)user, (const char*)defaultThing);
}

bool AntoIO::begin(const char* ssid, const char *passphrase, const char* token, const char *user, const char* defaultThing) 
{
    bool result = false;
    uint8_t count;

    _myMqtt.setUserPwd(user, token);
    _token = token;
    _defaultThing = defaultThing;
    _user = user;

    WiFi.begin(ssid, passphrase);

    for (count = 10; count && (WiFi.status() != WL_CONNECTED); --count) delay(500);

    if (count) result = true;

    connect();

    return result;
}

bool AntoIO::digitalUpdate(const char* channel, bool value)
{
    return digitalUpdate(_defaultThing, channel, value);
}

bool AntoIO::digitalUpdate(const char* thing, const char* channel, bool value)
{
    String str = requestHttp(_host, String(_setParam)+_token+"/"+thing+"/"+channel+"/"+(value ? "1":"0"));

    if (str.equals(""))
        return false;

    if (isResponseSuccess(str))
        return true;
    else 
        return false;
}
bool AntoIO::analogUpdate(const char* channel, int32_t value)
{
    return analogUpdate(_defaultThing, channel, value);
}

bool AntoIO::analogUpdate(const char* thing, const char* channel, int32_t value)
{
    String str = requestHttp(_host, String(_setParam)+_token+"/"+thing+"/"+channel+"/"+String(value));

    if (str.equals(""))
        return false;

    if (isResponseSuccess(str)) {
        return true;
    }
    else return false;
}

bool AntoIO::stringUpdate(const char* channel, const char* value)
{
    return stringUpdate(_defaultThing, channel, value);
}

bool AntoIO::stringUpdate(const char* thing, const char* channel, const char* value)
{
    String str = requestHttp(_host, String(_setParam)+_token+"/"+thing+"/"+channel+"/"+value);

    if (str.equals(""))
        return false;

    if (isResponseSuccess(str)) {
        return true;
    }
    else return false;
}

bool AntoIO::digitalGet(const char* channel)
{
    return digitalGet(_defaultThing, channel);
}

bool AntoIO::digitalGet(const char* thing, const char* channel)
{
    String str = requestHttp(_host, String(_getParam)+_token+"/"+thing+"/"+channel);

    if (str.equals(""))
        return false;

    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(str);

/* 
 * return real "FALSE", still thinking
 */
    if (!root.success())
        return false;
    
    if (root["result"] == true)
        return (root["value"] == 1 ? true : false);

/* 
 * return real "FALSE", still thinking
 */
    else return false;
}

int32_t AntoIO::analogGet(const char* channel)
{
    return analogGet(_defaultThing, channel);
}

int32_t AntoIO::analogGet(const char* thing, const char* channel)
{
    String str = requestHttp(_host, String(_getParam)+_token+"/"+thing+"/"+channel);

    if (str.equals(""))
        return 0;

    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(str);

/* 
 * return real "FALSE", still thinking
 */
    if (!root.success())
        return 0;
    
    if (root["result"] == true)
        return root["value"];
/* 
 * return real "FALSE", still thinking
 */
    else return 0;
}

String AntoIO::stringGet(const char* channel)
{
    return stringGet(_defaultThing, channel);
}

String AntoIO::stringGet(const char* thing, const char* channel)
{
    String str = requestHttp(_host, String(_getParam)+_token+"/"+thing+"/"+channel);

    if (str.equals(""))
        return str;

    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(str);

/* 
 * return real "FALSE", still thinking
 */
    if (!root.success())
        return "";
    
    if (root["result"] == true)
        return root["value"];
/* 
 * return real "FALSE", still thinking
 */
    else "";
}

String AntoIO::responseFilter(String str)
{
    uint32_t index = str.indexOf('{');

    str.remove(0, index);
    
    return str;
}

bool AntoIO::isResponseSuccess(String json)
{
    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success())
        return false;
    
    return root["result"];
}

String AntoIO::requestHttp(const char *host, String arg) 
{
    WiFiClient client;
    uint8_t count;

//  String for response message.
    String str = "";
    
//  Wait for client to connect to the anto api web service.
    for (count = 10; count && !client.connect(host, 80); --count);

//    if (!count) return (str = "host connection failed");
    if (!count) return str;

    client.print(String("GET ")+arg+" HTTP/1.1\r\n"+"Host: "+host+"\r\n\r\n");

    for (count = 50; count && !client.available(); --count) delay(100);

//    if (!count) return (str = "client available timeout");
    if (!count) return str;

    while (client.available())
        str += client.readStringUntil('\r');

    return (str = responseFilter(str));
}

String AntoIO::request(const char *arg) 
{
    String str = requestHttp(_host, String("/request/") + arg);

    if (str.equals(""))
        return str;

    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(str);

/* 
 * return real "FALSE", still thinking
 */
    if (!root.success())
        return "";
    
    if (root["result"] == true)
        return root["value"];
/* 
 * return real "FALSE", still thinking
 */
    else "";
}

void AntoIO::connect(void)
{
    _myMqtt.connect();
}

bool AntoIO::isConnected(void)
{
    return _myMqtt.isConnected();
}

void AntoIO::pub(const char *channel, const char *msg)
{
    pub(_defaultThing, channel, msg);
}

void AntoIO::pub(const char *thing, const char *channel, const char *msg)
{
    String topic("channel/");
    String message(msg);

    topic += _user;
    topic += "/";
    topic += thing;
    topic += "/";
    topic += channel;

    _myMqtt.publish(topic, message);
}

void AntoIO::sub(const char *channel)
{
    sub(_defaultThing, channel);
}

void AntoIO::sub(const char *thing, const char *channel)
{
    _myMqtt.subscribe(String("channel/")+_user+"/"+thing+"/"+channel);
}

void AntoIO::onMsgArrv(void (*function)(String&, String&))
{
    _myMqtt.onData(function);
}

void AntoIO::onDisconnected(void (*function)(void))
{
    _myMqtt.onDisconnected(function);
}

void AntoIO::onConnected(void (*function)(void))
{
    _myMqtt.onConnected(function);
}

void AntoIO::onPublished(void (*function)(void))
{
    _myMqtt.onPublished(function);
}

AntoIO Anto;

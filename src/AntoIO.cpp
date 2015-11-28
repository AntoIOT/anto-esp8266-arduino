
#include "AntoIO.h"

AntoIO::AntoIO() : _host("api.anto.io"), _getParam("/channel/get/"), _setParam("/channel/set/")
{
//    wifi_set_event_handler_cb((wifi_event_handler_cb_t)&AntoIO::_eventCallback);
}

bool AntoIO::begin(char* ssid, char *passphrase, char* token, char* defaultThing)
{
    return begin((const char*)ssid, (const char*)passphrase, (const char*)token, (const char*)defaultThing);
}

bool AntoIO::begin(const char* ssid, const char *passphrase, const char* token, const char* defaultThing) 
{
    bool result = false;
    uint8_t count;

    _token = token;
    _defaultThing= defaultThing;

    WiFi.begin(ssid, passphrase);

    for (count = 10; count && (WiFi.status() != WL_CONNECTED); --count) delay(500);

    if (count) result = true;

    return result;
}

bool AntoIO::digitalUpdate(const char* channel, bool value)
{
    return digitalUpdate(_defaultThing, channel, value);
}

bool AntoIO::digitalUpdate(const char* thing, const char* channel, bool value)
{
    WiFiClient client;
    uint8_t count;

//  String for response message.
    String str = "";
    
//  Wait for client to connect to the anto api web service.
    for (count = 10; count && !client.connect(_host, 80); --count);

//    if (!count) return (str = "api wrong");
    if (!count) return false;

    client.print(String("GET ")+_setParam+_token+"/"+thing+"/"+channel+"/"+(value? "on":"off")+" HTTP/1.1\r\n"+"Host: "+_host+"\r\n\r\n");

    for (count = 50; count && !client.available(); --count) delay(100);

//    if (!count) return (str = "not available");
    if (!count) return false;

    while (client.available()) {
        str += client.readStringUntil('\r');
    }

    str = responseFilter(str);

    if (isResponseSuccess(str)) {
        return true;
    }
    else return false;

//    return str;
}
bool AntoIO::analogUpdate(const char* channel, int32_t value)
{
    return analogUpdate(_defaultThing, channel, value);
}

bool AntoIO::analogUpdate(const char* thing, const char* channel, int32_t value)
{
    WiFiClient client;
    uint8_t count;

//  String for response message.
    String str = "";
    
//  Wait for client to connect to the anto api web service.
    for (count = 10; count && !client.connect(_host, 80); --count);

//    if (!count) return (str = "api wrong");
    if (!count) return false;

    client.print(String("GET ")+_setParam+_token+"/"+thing+"/"+channel+"/"+String(value)+" HTTP/1.1\r\n"+"Host: "+_host+"\r\n\r\n");

    for (count = 50; count && !client.available(); --count) delay(100);

//    if (!count) return (str = "not available");
    if (!count) return false;

    while (client.available()) {
        str += client.readStringUntil('\r');
    }

    str = responseFilter(str);

    if (isResponseSuccess(str)) {
        return true;
    }
    else return false;

//    return str;
}

bool AntoIO::stringUpdate(const char* channel, const char* value)
{
    return stringUpdate(_defaultThing, channel, value);
}

bool AntoIO::stringUpdate(const char* thing, const char* channel, const char* value)
{
    WiFiClient client;
    uint8_t count;

//  String for response message.
    String str = "";
    
//  Wait for client to connect to the anto api web service.
    for (count = 10; count && !client.connect(_host, 80); --count);

//    if (!count) return (str = "api wrong");
    if (!count) return false;

    client.print(String("GET ")+_setParam+_token+"/"+thing+"/"+channel+"/"+value+" HTTP/1.1\r\n"+"Host: "+_host+"\r\n\r\n");

    for (count = 50; count && !client.available(); --count) delay(100);

//    if (!count) return (str = "not available");
    if (!count) return false;

    while (client.available()) {
        str += client.readStringUntil('\r');
    }

    str = responseFilter(str);

    if (isResponseSuccess(str)) {
        return true;
    }
    else return false;

//    return str;
}

bool AntoIO::digitalGet(const char* channel)
{
    return digitalGet(_defaultThing, channel);
}

bool AntoIO::digitalGet(const char* thing, const char* channel)
{
    WiFiClient client;
    uint8_t count;

//  String for response message.
    String str = "";
    
//  Wait for client to connect to the anto api web service.
    for (count = 10; count && !client.connect(_host, 80); --count);

//    if (!count) return (str = "api wrong");
    if (!count) return false;
//    if (!count) return 'q';

    client.print(String("GET ")+_getParam+_token+"/"+thing+"/"+channel+" HTTP/1.1\r\n"+"Host: "+_host+"\r\n\r\n");

    for (count = 50; count && !client.available(); --count) delay(100);

//    if (!count) return (str = "not available");
    if (!count) return false;
//    if (!count) return 'q';

    while (client.available()) {
        str += client.readStringUntil('\r');
    }

    str = responseFilter(str);

    if (isResponseSuccess(str)) {
        return getDigitalValue(str);
    }
/* 
 * return real "FALSE", still thinking
 */
    else return false;


//    else return str;
//    else return 'q';
}

int32_t AntoIO::analogGet(const char* channel)
{
    return analogGet(_defaultThing, channel);
}

int32_t AntoIO::analogGet(const char* thing, const char* channel)
{
    WiFiClient client;
    uint8_t count;

//  String for response message.
    String str = "";
    
//  Wait for client to connect to the anto api web service.
    for (count = 10; count && !client.connect(_host, 80); --count);

//    if (!count) return (str = "api wrong");
    if (!count) return false;

    client.print(String("GET ")+_getParam+_token+"/"+thing+"/"+channel+" HTTP/1.1\r\n"+"Host: "+_host+"\r\n\r\n");

    for (count = 50; count && !client.available(); --count) delay(100);

//    if (!count) return (str = "not available");
    if (!count) return false;

    while (client.available()) {
        str += client.readStringUntil('\r');
    }

    str = responseFilter(str);

    if (isResponseSuccess(str)) {
        return getAnalogValue(str);
    }
/* 
 * return real "FALSE", still thinking
 */
    else return 0;

//    return str;
}

String AntoIO::stringGet(const char* channel)
{
    return stringGet(_defaultThing, channel);
}

String AntoIO::stringGet(const char* thing, const char* channel)
{
    WiFiClient client;
    uint8_t count;

//  String for response message.
    String str = "";
    
//  Wait for client to connect to the anto api web service.
    for (count = 10; count && !client.connect(_host, 80); --count);

//    if (!count) return (str = "api wrong");
    if (!count) return "";

    client.print(String("GET ")+_getParam+_token+"/"+thing+"/"+channel+" HTTP/1.1\r\n"+"Host: "+_host+"\r\n\r\n");

    for (count = 50; count && !client.available(); --count) delay(100);

//    if (!count) return (str = "not available");
    if (!count) return "";

    while (client.available()) {
        str += client.readStringUntil('\r');
    }

    str = responseFilter(str);

    if (isResponseSuccess(str)) {
        return getStringValue(str);
    }
/* 
 * return real "FALSE", still thinking
 */
    else "";

//    return str;
}

String AntoIO::responseFilter(String str)
{
    uint32_t index = str.indexOf('{');

    str.remove(0, index);
    
    return str;
}

bool AntoIO::isResponseSuccess(String json)
{
    uint8_t start, end;
    String str;

    start = json.indexOf("result\":\"")+9;
    end = start + 4;

    str = json.substring(start, end);

    if (str.equals("true")) return true;
    else return false;
}

bool AntoIO::getDigitalValue(String json)
{
    uint8_t index;//, end, start;
    char ch;
//    String str;

    index = json.indexOf("value\":\"")+8;
//    start = json.indexOf("value\":\"")+8;
//    end = start + 1;

//    str = json.substring(start, end);
    ch = json.charAt(index);

    if (ch == '1') return true;
    else return false;
//    return str;
//    return ch;
}

int32_t AntoIO::getAnalogValue(String json)
{
    uint8_t index;
    String str = "";

    index = json.indexOf("value\":\"")+8;

    while (json.charAt(index) != '"') {
        str += json.charAt(index);

        index++;
    }

    return str.toInt();
}

String AntoIO::getStringValue(String json)
{
    uint8_t index;
    String str = "";

    index = json.indexOf("value\":\"")+8;

    while (json.charAt(index) != '"') {
        str += json.charAt(index);

        index++;
    }

    return str;
}

AntoIO Anto;

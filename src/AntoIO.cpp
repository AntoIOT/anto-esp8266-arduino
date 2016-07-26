
#include "json/ArduinoJson.h"
#include "AntoIO.h"

#define ANTO_VER    "v0.5.2"
#define ANTO_HOST   "api.anto.io"
#define ANTO_BROKER "service.anto.io"
#define ANTO_GET    "/channel/get/"
#define ANTO_SET    "/channel/set/"
#define ANTO_BROKER_PORT 1883
#define ANTO_RAND_STR_LEN 10

void gen_random(char *s, const int len);
bool isResponseSuccess(String json);
String responseFilter(String str);


AntoIO::AntoIO(const char *user, const char *token, 
        const char *thing, const char *client_id): 
    mqtt(client_id, ANTO_BROKER, ANTO_BROKER_PORT), 
    _user(user), _token(token), _thing(thing)
{
    String clientId(ANTO_VER);

    clientId += '-';
    clientId += user;
    clientId += '-';

    if (client_id[0] == 0) {
        char randString[ANTO_RAND_STR_LEN + 1];

        randomSeed(analogRead(0));
        gen_random(randString, ANTO_RAND_STR_LEN);

        clientId += randString;
    }
    else
        clientId += client_id;

    char buf[clientId.length() + 1];

    clientId.toCharArray(buf, clientId.length() + 1);

    mqtt.setClientId(buf);
    mqtt.setUserPwd(user, token);
}

const char* AntoIO::getVersion(void)
{
    return ANTO_VER;
}

bool AntoIO::smartConfig (void)
{
    wifiManager.setDebugOutput(false);
    wifiManager.autoConnect("Anto Smart Config");
    
    return true;
}

bool AntoIO::begin(const char* ssid, const char *passphrase) 
{
    bool result = false;
    uint8_t count;

    WiFi.begin(ssid, passphrase);

    for (count = 50; count && (WiFi.status() != WL_CONNECTED); --count) 
        delay(100);

    if (count) 
        result = true;

    return result;
}

bool AntoIO::digitalUpdate(const char* channel, bool value)
{
    return digitalUpdate(_thing, channel, value);
}

bool AntoIO::digitalUpdate(const char* thing, const char* channel, bool value)
{
    String str = requestHttp(ANTO_HOST, String(ANTO_SET) + _token+ "/" + 
            thing+ "/" + channel + "/" + (value ? "1" : "0"));

    if (str.equals(""))
        return false;

    if (isResponseSuccess(str))
        return true;
    else 
        return false;
}
bool AntoIO::analogUpdate(const char* channel, int32_t value)
{
    return analogUpdate(_thing, channel, value);
}

bool AntoIO::analogUpdate(const char* thing, const char* channel, int32_t value)
{
    String str = requestHttp(ANTO_HOST, String(ANTO_SET) + _token + "/" + 
            thing + "/" + channel + "/" + String(value));

    if (str.equals(""))
        return false;

    if (isResponseSuccess(str))
        return true;
    else
        return false;
}

bool AntoIO::stringUpdate(const char* channel, const char* value)
{
    return stringUpdate(_thing, channel, value);
}

bool AntoIO::stringUpdate(const char* thing, const char* channel, 
        const char* value)
{
    String str = requestHttp(ANTO_HOST, String(ANTO_SET) + _token + "/" +
            thing + "/" + channel + "/" + value);

    if (str.equals(""))
        return false;

    if (isResponseSuccess(str))
        return true;
    else
        return false;
}

bool AntoIO::digitalGet(const char* channel)
{
    return digitalGet(_thing, channel);
}

bool AntoIO::digitalGet(const char* thing, const char* channel)
{
    String str = requestHttp(ANTO_HOST, String(ANTO_GET) + _token + "/" +
            thing + "/" + channel);

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
    else
        return false;
}

int32_t AntoIO::analogGet(const char* channel)
{
    return analogGet(_thing, channel);
}

int32_t AntoIO::analogGet(const char* thing, const char* channel)
{
    String str = requestHttp(ANTO_HOST, String(ANTO_GET) + _token + "/" + 
            thing + "/" + channel);

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
    else
        return 0;
}

String AntoIO::stringGet(const char* channel)
{
    return stringGet(_thing, channel);
}

String AntoIO::stringGet(const char* thing, const char* channel)
{
    String str = requestHttp(ANTO_HOST, String(ANTO_GET) + _token 
            + "/" + thing + "/" + channel);

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
    else
        return "";
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
    String str = requestHttp(ANTO_HOST, String("/request/") 
            + _token + "/" + arg);

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
    else 
        return "";
}

void AntoIO::pub(const char *channel, const char *msg, 
        int qos, bool retain)
{
    pub(_thing, channel, msg, qos, retain);
}

void AntoIO::pub(String& channel, String& msg, 
        int qos, bool retain)
{
    pub(_thing, channel, msg, qos, retain);
}

void AntoIO::pub(const char *channel, String& msg, 
        int qos, bool retain)
{
    String ch(channel);

    pub(_thing, ch, msg, qos, retain);
}

void AntoIO::pub(String& channel, const char *msg, 
        int qos, bool retain)
{
    String m(msg);

    pub(_thing, channel, m, qos, retain);
}

void AntoIO::pub(const char *channel, int msg, 
        int qos, bool retain)
{
    String m(msg);
    String ch(channel);

    pub(_thing, ch, m, qos, retain);
}

void AntoIO::pub(String& channel, int msg, 
        int qos, bool retain)
{
    String m(msg);

    pub(_thing, channel, m, qos, retain);
}

void AntoIO::pub(const char *channel, char msg, 
        int qos, bool retain)
{
    const char m = msg;

    pub(_thing, channel, &m, qos, retain);
}

void AntoIO::pub(String& channel, char msg, 
        int qos, bool retain)
{
    String m(msg);

    pub(_thing, channel, m, qos, retain);
}
        
void AntoIO::pub(const char *channel, double msg, int qos, bool retain)
{
    String m(msg);
    String ch(channel);

    pub(_thing, ch, m, qos, retain);
}
	    
void AntoIO::pub(String& channel, double msg, int qos, bool retain)
{
    String m(msg);

    pub(_thing, channel, m, qos, retain);
}

void AntoIO::pub(const char *thing, const char *channel, const char *msg, 
        int qos, bool retain)
{
    String topic("channel/");
    String message(msg);

    topic += _user;
    topic += "/";
    topic += thing;
    topic += "/";
    topic += channel;

    mqtt.publish(topic, message, qos, (retain ? 1:0));
}

void AntoIO::pub(const char *thing, String& channel, String& msg, 
        int qos, bool retain)
{
    String topic("channel/");

    topic += _user;
    topic += "/";
    topic += thing;
    topic += "/";
    topic += channel;

    mqtt.publish(topic, msg, qos, (retain ? 1:0));
}

void AntoIO::sub(const char *channel, int qos)
{
    sub(_thing, channel, qos);
}

void AntoIO::sub(const char *thing, const char *channel, int qos)
{
    mqtt.subscribe(String("channel/")+_user+"/"+thing+"/"+channel, qos);
}

void AntoIO::service(const char *name, int qos)
{
    mqtt.subscribe(String("service/")+ name, qos);
}

String responseFilter(String str)
{
    uint32_t index = str.indexOf('{');

    str.remove(0, index);
    
    return str;
}

bool isResponseSuccess(String json)
{
    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success())
        return false;
    
    return root["result"];
}

void gen_random(char *s, const int len) {
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i)
        s[i] = alphanum[random(300) % (sizeof(alphanum) - 1)];

    s[len] = 0;
}

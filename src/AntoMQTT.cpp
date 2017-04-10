#include "AntoMQTT.h"
#include "AntoCommon.h"

#define ANTO_MQTT_PORT      1883
#define ANTO_MQTTS_PORT     1884
#define ANTO_RAND_STR_LEN   10

static void gen_random(char *s, const uint8_t len)
{
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i)
        s[i] = alphanum[random(300) % (sizeof(alphanum) - 1)];

    s[len] = 0;
}

bool AntoMQTT::connect(
        bool secure,
        const char * client_id)
{
    uint8_t count;
    String clientId(ANTO_VER);

    clientId += '-';
    clientId += this->_user;
    clientId += '-';

    if (client_id[0] == 0) {
        char randString[ANTO_RAND_STR_LEN + 1];

        randomSeed(analogRead(0));
        gen_random(randString, ANTO_RAND_STR_LEN);

        clientId += randString;
    } else {
        clientId += client_id;

        free(_lastConnClientId);
        _lastConnClientId = (char *) malloc(sizeof(client_id));
        strcpy(_lastConnClientId, client_id);
    }

    char buf[clientId.length() + 1];

    clientId.toCharArray(buf, clientId.length() + 1);

    if (secure)
        this->_mqtt.begin(
                _host,
                ANTO_MQTTS_PORT,
                this->_nets, this,
                &AntoMQTT::messageHandler);
    else
        this->_mqtt.begin(
                _host,
                ANTO_MQTT_PORT,
                this->_net,
                this,
                &AntoMQTT::messageHandler);

    for (
            count = 50;
            count && (!this->_mqtt.connect(buf, this->_user, this->_token));
            --count)
        delay(100);

    _lastConnSecure = secure;

    if (count == 0)
        return false;
    else
        return true;
}

bool AntoMQTT::pub(const char *channel, const char *msg,
        int qos, bool retain)
{
    return pub(this->_thing, channel, msg, qos, retain);
}

bool AntoMQTT::pub(const char *channel, String& msg,
        int qos, bool retain)
{
    String ch(channel);
    String th(this->_thing);

    return pub(th, ch, msg, qos, retain);
}

bool AntoMQTT::pub(String& channel, const char *msg,
        int qos, bool retain)
{
    String m(msg);
    String th(this->_thing);

    return pub(th, channel, m, qos, retain);
}

bool AntoMQTT::pub(String& channel, String& msg,
        int qos, bool retain)
{
    String th(this->_thing);

    return pub(th, channel, msg, qos, retain);
}

bool AntoMQTT::pub(const char *channel, int msg,
        int qos, bool retain)
{
    String m(msg);
    String ch(channel);
    String th(this->_thing);

    return pub(th, ch, m, qos, retain);
}

bool AntoMQTT::pub(String& channel, int msg,
        int qos, bool retain)
{
    String m(msg);
    String th(this->_thing);

    return pub(th, channel, m, qos, retain);
}

bool AntoMQTT::pub(const char *channel, double msg, int qos, bool retain)
{
    String m(msg);
    String ch(channel);
    String th(this->_thing);

    return pub(th, ch, m, qos, retain);
}

bool AntoMQTT::pub(String& channel, double msg, int qos, bool retain)
{
    String m(msg);
    String th(this->_thing);

    return pub(th, channel, m, qos, retain);
}

bool AntoMQTT::pub(const char *thing, const char *channel, const char *msg,
        int qos, bool retain)
{
    String topic("channel/");
    String message(msg);

    topic += this->_user;
    topic += "/";
    topic += thing;
    topic += "/";
    topic += channel;

    return this->_mqtt.publish(topic, message);
}

bool AntoMQTT::pub(String& thing, String& channel, String& msg,
        int qos, bool retain)
{
    String topic("channel/");

    topic += this->_user;
    topic += "/";
    topic += thing;
    topic += "/";
    topic += channel;

    return this->_mqtt.publish(topic, msg);
}

bool AntoMQTT::sub(const char *channel, int qos)
{
    return sub(this->_thing, channel, qos);
}

bool AntoMQTT::sub(String& channel, int qos)
{
    String th(this->_thing);

    return sub(th, channel, qos);
}

bool AntoMQTT::sub(const char *thing, const char *channel, int qos)
{
    String topic("channel/");

    topic += this->_user;
    topic += "/";
    topic += thing;
    topic += "/";
    topic += channel;

    return this->_mqtt.subscribe(topic, this);
}

bool AntoMQTT::sub(String& thing, String& channel, int qos)
{
    String topic("channel/");

    topic += this->_user;
    topic += "/";
    topic += thing;
    topic += "/";
    topic += channel;

    return this->_mqtt.subscribe(topic, this);
}

bool AntoMQTT::service(const char *name, int qos)
{
    String service("service/");
    service += name;

    return this->_mqtt.subscribe(service, this);
}

void AntoMQTT::messageHandler(MQTT::MessageData &messageData)
{
  MQTT::Message &message = messageData.message;

  // null terminate topic to create String object
  int len = messageData.topicName.lenstring.len;
  char topic[len+1];
  memcpy(topic, messageData.topicName.lenstring.data, (size_t)len);
  topic[len] = '\0';

  char *channel = strrchr(topic, '/') + 1;
  *(channel - 1) = '\0';
  char *thing = strrchr(topic, '/') + 1;

  // get payload
  char * payload = (char *)message.payload;

  // null terminate payload if enough space is available
  if(message.payloadlen < MQTT_BUFFER_SIZE) {
    payload[message.payloadlen] = '\0';
  }

  if (this->_onData)
      _onData(String(thing), String(channel), String(payload));
  // messageReceived(String(topic), String(payload), (char*)message.payload, (unsigned int)message.payloadlen);
}

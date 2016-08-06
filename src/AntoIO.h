/*
 * Anto.io - The easiest ESP8266 library for Arduino IDE
 * by Anto.io
*/
#ifndef ANTO_IO_H
#define ANTO_IO_H

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <wifimanager/WiFiManager.h>

#include "mqtt/MQTT.h"

class AntoIO
{
public:

    AntoIO(const char *user, const char *token, const char *thing, const char *client_id = "");

    MQTT mqtt;

    bool 
        smartConfig(void),
        begin(const char* ssid, const char *passphrase),

        digitalUpdate(const char* channel, bool value),
        digitalUpdate(const char* thing, const char* channel, bool value),

        analogUpdate(const char* channel, int32_t value),
        analogUpdate(const char* thing, const char* channel, int32_t value),

        stringUpdate(const char* channel, const char* value),
        stringUpdate(const char* thing, const char* channel, const char* value),

        digitalGet(const char* channel),
        digitalGet(const char* thing,const char* channel);

    const char *getVersion(void);

    int32_t
        analogGet(const char* channel),
        analogGet(const char* thing,const char* channel);

    String 
        stringGet(const char* channel),
        stringGet(const char* thing,const char* channel),

        requestHttp(const char*, String arg),
        request(const char *arg), // Deprecated
		getDataService(const char *arg);

    void
		showVersion(void),
		connectMQTT(void),
        pub(const char *channel, const char *msg, 
                int qos = 0, bool retain = false),
	    pub(String& channel, String& msg, 
                int qos = 0, bool retain = false),
        pub(const char *channel, String& msg, 
                int qos = 0, bool retain = false),
	    pub(String& channel, const char *msg, 
                int qos = 0, bool retain = false),
        pub(const char *channel, int msg, 
                int qos = 0, bool retain = false),
	    pub(String& channel, int msg, 
                int qos = 0, bool retain = false),
        pub(const char *channel, char msg, 
                int qos = 0, bool retain = false),
	    pub(String& channel, char msg, 
                int qos = 0, bool retain = false),
        pub(const char *channel, double msg, 
                int qos = 0, bool retain = false),
	    pub(String& channel, double msg, 
                int qos = 0, bool retain = false),
        pub(const char *thing, const char *channel, const char *msg, 
                int qos = 0, bool retain = false),
        pub(const char *thing, String& channel, String& msg, 
                int qos = 0, bool retain = false),

        sub(const char *channel, int qos = 0),
        sub(const char *thing, const char *channel, int qos = 0),

        service(const char *name, int qos = 0); // Deprecated
	
	void
		on(const char* eventName, void (* callback)(String& thing, String& channel, String& msg)),
		on(const char* eventName, void (* callback)(void));
		
private:
    WiFiManager wifiManager;

    const char
        *_user,
        *_token,
        *_thing;
		
	void (*cb_onDataReceived)(String& thing, String& channel, String& msg);
	void (*cb_onConnected)(void);
	void (*cb_onDisconnected)(void);
	void (*cb_onPublished)(void);
};

#endif

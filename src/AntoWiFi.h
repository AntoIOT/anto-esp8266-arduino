#ifndef ANTO_WIFI_H
#define ANTO_WIFI_H

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "wifimanager/WiFiManager.h"

class AntoWiFi
{
    public:
        AntoWiFi(void) { }

        bool smartConfig(void)
        {
            wifiManager.setDebugOutput(false);
            wifiManager.autoConnect("Anto Smart Config");

            return true;
        }

        // timeout is under development
        bool begin(
                const char* ssid,
                const char *passphrase,
                uint16_t timeout = 0)
        {
            bool result = false;
            uint8_t count;

            WiFi.begin(ssid, passphrase);

            for (count = 50; count && (!WiFi.isConnected()); --count)
                delay(100);

            if (count)
                result = true;

            return result;
        }

    private:
        WiFiManager wifiManager;
};

#endif

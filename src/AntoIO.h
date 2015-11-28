/*
 * Anto.io - The easiest ESP8266 library for Arduino IDE
 *
 * by Anto.io
 * 13/09/2015
*/

#ifndef ANTO_IO_H
#define ANTO_IO_H

#include "ESP8266WiFi.h"

class AntoIO
{
public:

    AntoIO();

    /**
     * Start Wifi connection
     * if passphrase is set the most secure supported mode will be automatically selected
     * @param ssid const char*          Pointer to the SSID string.
     * @param passphrase const char *   Optional. Passphrase. Valid characters in a passphrase must be between ASCII 32-126 (decimal).
     * @param channel                   Optional. Channel of AP
     * @return
     */
    bool begin(char* ssid, char *passphrase, char* token, char* defaultDev);
    bool begin(const char* ssid, const char *passphrase, const char* token, const char* defaultDev);


   /* Wait for Wifi connection to reach a result
    * returns the status reached or disconnect if STA is off
    */

    bool digitalUpdate(const char* channel, bool value);
    bool digitalUpdate(const char* thing, const char* channel, bool value);

    bool analogUpdate(const char* channel, int32_t value);
    bool analogUpdate(const char* thing, const char* channel, int32_t value);

    bool stringUpdate(const char* channel, const char* value);
    bool stringUpdate(const char* thing, const char* channel, const char* value);

    /* Set up an open access point
     *
     * param ssid: Pointer to the SSID string.
     */
    
    bool digitalGet(const char* channel);
    bool digitalGet(const char* thing,const char* channel);

    int32_t analogGet(const char* channel);
    int32_t analogGet(const char* thing,const char* channel);

    String stringGet(const char* channel);
    String stringGet(const char* thing,const char* channel);

    //bool service(const char* device,const char* channel);

/* protected:
 *     static void _scanDone(void* result, int status);
 *     void * _getScanInfoByIndex(int i);
 *     static void _smartConfigCallback(uint32_t status, void* result);
 *     static void _eventCallback(void *event);
 *     bool _smartConfigStarted;
 *     bool _smartConfigDone;
 * 
 *     bool _useApMode;
 *     bool _useClientMode;
 * 	bool _useStaticIp;
 * 	
 * 	static bool _scanAsync;
 * 	static bool _scanStarted;
 * 	static bool _scanComplete;
 * 
 *     static size_t _scanCount;
 *     static void* _scanResult;
 */
private:
    const char
        *_host,
        *_token,
        *_getParam,
        *_setParam,
        *_defaultThing;

    String 
        responseFilter(String str);

    bool
        isResponseSuccess(String json),
        getDigitalValue(String json);

    int32_t
        getAnalogValue(String json);

    String
        getStringValue(String json);
};

extern AntoIO Anto;

#endif

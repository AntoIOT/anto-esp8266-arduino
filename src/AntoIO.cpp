#include "AntoIO.h"

const char* AntoIO::getVersion(void)
{
    static const char *ver = ANTO_VER;

    return ver;
}

void AntoIO::printArtWork(void)
{
    Serial.println("    _          _");
    Serial.println("   / \\   _ __ | |_ ___");
    Serial.println("  / _ \\ | '_ \\| __/ _ \\ ");
    Serial.println(" / ___ \\| | | | || (_) |");
    Serial.println("/_/   \\_\\_| |_|\\__\\___/ ");
    Serial.println();
}

void AntoIO::begin(
        const char *ssid,
        const char* pwd,
        onMsg onData,
        bool secure)
{
    while (!this->wifi.begin(ssid, pwd));
    Serial.print("\n\nWiFi Connected to ");
    Serial.println(ssid);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    while (!this->mqtt.connect(secure));
    Serial.println("Broker Connected");

    printArtWork();

    Serial.print("Anto library version: ");
    Serial.println(this->getVersion());
    Serial.println();

    this->mqtt.onData(onData);
}

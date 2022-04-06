
#include "wifi_keys.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

#define MQTT_HOST IPAddress(10, 0, 1, 2) // Broker IP
#define MQTT_PORT 1883

// MQTT Subscription Variables
int Mode = 0.00;
float Salinity = 0.00;
float doLow = 0.00;
float doHigh = 0.00;
bool wsRainclear = false;

// Subscription Topics
const char *subTopic[] = {"MQTT/TEST/MODE",
                          "MQTT/TEST/SALINITY",
                          "MQTT/TEST/DOLOW",
                          "MQTT/TEST/DOHIGH",
                          "MQTT/TEST/rainClear"};


// Publish Topics

const char *pubTopic[] = {
    "MQTT/TEST/heart",              // 0
    "MQTT/TEST/IP",                 // 1
    "MQTT/TEST/relativeHumidity",   // 2
    "MQTT/TEST/outdoorTemp",        // 3
    "MQTT/TEST/lightIntensity",     // 4
    "MQTT/TEST/Temperature",        // 5
    "MQTT/TEST/soilmoisture",       // 6
    "MQTT/TEST/rainVolume",         // 7
    "MQTT/TEST/windSpeed",          // 8
    "MQTT/TEST/windDirection",      // 9
    "MQTT/TEST/DO",                 // 10
    "MQTT/TEST/tempBot",            // 11
    "MQTT/TEST/blowerSTAT",         // 12
    "MQTT/TEST/callingBell",        // 13
    "MQTT/TEST/office/temperature", // 14
    "MQTT/TEST/storage/temperature"}; // 15
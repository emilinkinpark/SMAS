
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
// Others
int clear = false; // Clears Flash
bool wsRainclear = false;
bool reset = false;


// Motor Control and Feedback
int mode;
int motorCTRL;
bool motorFault;
bool motorSTAT;
float Salinity;
float doLow;
float doHigh;


// Temp Variables to store last state
bool modeTemp;
bool motorControlTemp;
float SalinityTemp;
float doLowTemp;
float doHighTemp;
bool clearTemp;

// Subscription Topics
const char *subTopic[] = {
    "MQTT/TEST/MODE",      // 0
    "MQTT/TEST/SALINITY",  // 1
    "MQTT/TEST/DOLOW",     // 2
    "MQTT/TEST/DOHIGH",    // 3
    "MQTT/TEST/MOTORCTRL"  // 4
    "MQTT/TEST/rainClear", // 5
    "MQTT/TEST/reset",     // 6
    "MQTT/TEST/CLEAR"      // 7
};

// Publish Topics

const char *pubTopic[] = {
    "MQTT/TEST/heart",               // 0
    "MQTT/TEST/IP",                  // 1
    "MQTT/TEST/relativeHumidity",    // 2
    "MQTT/TEST/outdoorTemp",         // 3
    "MQTT/TEST/lightIntensity",      // 4
    "MQTT/TEST/temperature",         // 5
    "MQTT/TEST/soilmoisture",        // 6
    "MQTT/TEST/rainVolume",          // 7
    "MQTT/TEST/windSpeed",           // 8
    "MQTT/TEST/windDirection",       // 9
    "MQTT/TEST/DO",                  // 10
    "MQTT/TEST/tempBot",             // 11
    "MQTT/TEST/motorSTAT",          // 12
    "MQTT/TEST/callingBell",         // 13
    "MQTT/TEST/office/temperature",  // 14
    "MQTT/TEST/storage/temperature", // 15
    "MQTT/TEST/motorFAULT",         // 16
};
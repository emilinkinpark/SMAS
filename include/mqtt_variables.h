
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
bool reset = false; // Resets ESP32
int clear = false;  // Clears Flash
bool wsRainclear = false;

// Motor Control
int modemc;
float Salinity;
int doLvl;

bool mode;
bool motorCTRL;
bool motorSTAT;
float doLow;
float doHigh;

// Feedback
bool motorFault;

// Temp Variables to store last state
bool modeTemp;
bool motorControlTemp;
bool modemcTemp;
float SalinityTemp;
int doLvlTemp;
float doLowTemp;
float doHighTemp;

// Subscription Topics
const char *subTopic[] = {
    "MQTT/TEST/MODEMC",    // 0
    "MQTT/TEST/SALINITY",  // 1
    "MQTT/TEST/DOLVL",     // 2
    "MQTT/TEST/reset",     // 3
    "MQTT/TEST/CLEAR",     // 4
    "MQTT/TEST/rainClear"  // 5
};

// Publish Topics

const char *pubTopic[] = {
    "MQTT/TEST/heart",            // 0
    "MQTT/TEST/IP",               // 1
    "MQTT/TEST/relativeHumidity", // 2
    "MQTT/TEST/bmeTemp",          // 3
    "MQTT/TEST/lightIntensity",   // 4
    "MQTT/TEST/device1T",          // 5
    "MQTT/TEST/soilmoisture",     // 6
    "MQTT/TEST/rainVolume",       // 7
    "MQTT/TEST/windSpeed",        // 8
    "MQTT/TEST/windDirection",    // 9
    "MQTT/TEST/DO",               // 10
    "MQTT/TEST/tempBot",          // 11
    "MQTT/TEST/soilT",            // 12
    "MQTT/TEST/atmPressure",      // 13
    "MQTT/TEST/altitude"          // 14
};
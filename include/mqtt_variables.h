
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
    "MQTT/TANK3/MODEMC",    // 0
    "MQTT/TANK3/SALINITY",  // 1
    "MQTT/TANK3/DOLVL",     // 2
    "MQTT/TANK3/reset",     // 3
    "MQTT/TANK3/CLEAR",     // 4
    "MQTT/TANK3/rainClear"  // 5
};

// Publish Topics

const char *pubTopic[] = {
    "MQTT/TANK3/heart",            // 0
    "MQTT/TANK3/IP",               // 1
    "MQTT/TANK3/relativeHumidity", // 2
    "MQTT/TANK3/bmeTemp",          // 3
    "MQTT/TANK3/lightIntensity",   // 4
    "MQTT/TANK3/device1T",          // 5
    "MQTT/TANK3/soilmoisture",     // 6
    "MQTT/TANK3/rainVolume",       // 7
    "MQTT/TANK3/windSpeed",        // 8
    "MQTT/TANK3/windDirection",    // 9
    "MQTT/TANK3/DO",               // 10
    "MQTT/TANK3/tempBot",          // 11
    "MQTT/TANK3/soilT",            // 12
    "MQTT/TANK3/atmPressure",      // 13
    "MQTT/TANK3/altitude"          // 14
};
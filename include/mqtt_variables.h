
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
    "MQTT/TANK/MODEMC",    // 0
    "MQTT/TANK/SALINITY",  // 1
    "MQTT/TANK/DOLVL",     // 2
    "MQTT/TANK/reset",     // 3
    "MQTT/TANK/CLEAR",     // 4
    "MQTT/TANK/rainClear"  // 5
};

// Publish Topics

const char *pubTopic[] = {
    "MQTT/TANK/heart",            // 0
    "MQTT/TANK/IP",               // 1
    "MQTT/TANK/relativeHumidity", // 2
    "MQTT/TANK/bmeTemp",          // 3
    "MQTT/TANK/lightIntensity",   // 4
    "MQTT/TANK/device1T",          // 5
    "MQTT/TANK/soilmoisture",     // 6
    "MQTT/TANK/rainVolume",       // 7
    "MQTT/TANK/windSpeed",        // 8
    "MQTT/TANK/windDirection",    // 9
    "MQTT/TANK/DO",               // 10
    "MQTT/TANK/tempBot",          // 11
    "MQTT/TANK/soilT",            // 12
    "MQTT/TANK/atmPressure",      // 13
    "MQTT/TANK/altitude"          // 14
};
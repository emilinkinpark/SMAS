
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
    //"MQTT/weatherStation/MODEMC",   // 0
    //"MQTT/weatherStation/SALINITY", // 1
    //"MQTT/weatherStation/DOLVL",    // 2
    //"MQTT/weatherStation/reset",    // 3
    //"MQTT/weatherStation/CLEAR"     // 4
    //,"MQTT/weatherStation/rainClear" //
};

// Publish Topics

const char *pubTopic[] = {
    "MQTT/weatherStation/heart",            // 0
    "MQTT/weatherStation/IP",               // 1
    "MQTT/weatherStation/relativeHumidity", // 2
    "MQTT/weatherStation/bmeTemp",      // 3
    "MQTT/weatherStation/lightIntensity",   // 4
    "MQTT/weatherStation/dryAirT",          // 5
    "MQTT/weatherStation/soilmoisture",     // 6
    "MQTT/weatherStation/rainVolume",       // 7
    "MQTT/weatherStation/windSpeed",        // 8
    "MQTT/weatherStation/windDirection",    // 9
    "MQTT/weatherStation/DO",               // 10
    "MQTT/weatherStation/tempBot",          // 11
    "MQTT/weatherStation/soilT",            // 12
    "MQTT/weatherStation/atmPressure",      // 13
    "MQTT/weatherStation/altitude"          // 14
};

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
    "MQTT/indoorAir/MODEMC",   // 0
    "MQTT/indoorAir/SALINITY", // 1
    "MQTT/indoorAir/DOLVL",    // 2
    "MQTT/indoorAir/reset",    // 3
    "MQTT/indoorAir/CLEAR",    // 4
    "MQTT/indoorAir/rainClear" // 5
};

// Publish Topics

const char *pubTopic[] = {
    "MQTT/indoorAir/heart",            // 0
    "MQTT/indoorAir/IP",               // 1
    "MQTT/indoorAir/relativeHumidity", // 2
    "MQTT/indoorAir/bmeTemp",          // 3
    "MQTT/indoorAir/lightIntensity",   // 4
    "MQTT/indoorAir/device1T",         // 5
    "MQTT/indoorAir/soilmoisture",     // 6
    "MQTT/indoorAir/rainVolume",       // 7
    "MQTT/indoorAir/windSpeed",        // 8
    "MQTT/indoorAir/windDirection",    // 9
    "MQTT/indoorAir/DO",               // 10
    "MQTT/indoorAir/tempBot",          // 11
    "MQTT/indoorAir/soilT",            // 12
    "MQTT/indoorAir/atmPressure",      // 13
    "MQTT/indoorAir/altitude",         // 14
    "MQTT/indoorAir/callingBell",      // 15
    "MQTT/indoorAir/office",           // 16
    "MQTT/indoorAir/storage"           // 17
};
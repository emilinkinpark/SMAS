/* Checklist before uploading to device, remember to KISS (Keep It Super Simple)
* Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more
* To enable or disable type of sensor, check enabler.h
* Always Change MQTT Topic using Find and Replace; usually MQTT/Test would be used for testing
*/
#include <Arduino.h>
#include "headers.h" // Add all headers to the main page here

void setup()
{

  Serial.begin(9600);

  mqttInit();    // Initialising MQTT Parameters, check mqtt.h for more
  otaInit();     // Initialising OTA
  sensInit();    // Initialising All MODBUS Sensors
  i2cInit();     // Initialising Default I2C Pins
  bme680Init();  // Intialising BME680
  bh1750Init();  // Initialising BH1750
  ds18b20init(); // Intialising DS18B20
}

void loop()
{

  bme680Loop();    // BME680
  bh1750Loop();    // BH1750
  ds18b20Loop();   // DS18B20
  moistsensLoop(); // Moisture Sensor
  windSpeed();     // Wind Speed Sensor
  windDir();       // Wind Direction Sensor
  tempHumid();     // Outdoor Humidity and Temperature Sensor
  DO();            // Dissolved Oxygen Sensor
  rainVol(wsRainclear);

#ifdef ENABLE_MQTT
  // MQTT Publish
  publish(0, "MQTT/TEST/heart");
#ifdef ENABLE_RAINVOLUME
  subscribe("MQTT/TEST/rainClear"); // 24 Rain Clear Command Subscribtion
  publish(wsRainclear, "MQTT/TEST/rainClear");
#endif
#ifdef ENABLE_BME680
  publish(relHum1, "MQTT/TEST/relativeHumidity");
  publish(temp1, "MQTT/TEST/outdoorTemp");
#endif

#ifdef ENABLE_BH1750
  publish(lux, "MQTT/TEST/lightIntensity");
#endif

#ifdef ENABLE_DS18B20
  publish(temperature_1, "MQTT/TEST/Temperature");
#endif

#ifdef ENABLE_MOISTSENSOR
  publish(soilmoistperc, "MQTT/TEST/soilmoisture");
#endif

#ifdef ENABLE_RAINVOLUME
  publish(rainvol, "MQTT/TEST/rainVolume");
#endif

#ifdef ENABLE_WINDSPEED
  publish(windspeed, "MQTT/TEST/windSpeed");
#endif

#ifdef ENABLE_WINDDIR
  publish(winddir, "MQTT/TEST/windDirection");
#endif

#ifdef ENABLE_DO
  publish(averagedomgl, "MQTT/TEST/DO");
  publish(doTemp, "MQTT/TEST/tempBot");
#endif

  publish(1, "MQTT/TEST/heart");
#endif
  vTaskDelay(2000 / portTICK_PERIOD_MS);
}

// Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more
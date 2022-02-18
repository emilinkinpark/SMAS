// Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more

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
  publish(0, "MQTT/SCAL2/heart");
#ifdef ENABLE_RAINVOLUME
  subscribe("MQTT/SCAL2/rainClear"); // 24 Rain Clear Command Subscribtion
  publish(wsRainclear, "MQTT/SCAL2/rainClear");
#endif
#ifdef ENABLE_BME680
  publish(relHum1, "MQTT/SCAL2/relativeHumidity");
  publish(temp1, "MQTT/SCAL2/outdoorTemp");
#endif

#ifdef ENABLE_BH1750
  publish(lux, "MQTT/SCAL2/lightIntensity");
#endif

#ifdef ENABLE_DS18B20
  publish(temperature_1, "MQTT/SCAL2/Temperature");
#endif

#ifdef ENABLE_MOISTSENSOR
  publish(soilmoistperc, "MQTT/SCAL2/soilmoisture");
#endif

#ifdef ENABLE_RAINVOLUME
  publish(rainvol, "MQTT/SCAL2/rainVolume");
#endif

#ifdef ENABLE_WINDSPEED
  publish(windspeed, "MQTT/SCAL2/windSpeed");
#endif

#ifdef ENABLE_WINDDIR
  publish(winddir, "MQTT/SCAL2/windDirection");
#endif

#ifdef ENABLE_DO
  publish(averagedomgl, "MQTT/SCAL2/DO");
  publish(doTemp, "MQTT/SCAL2/tempBot");
#endif

  publish(1, "MQTT/SCAL2/heart");
#endif
  vTaskDelay(2000 / portTICK_PERIOD_MS);
}

// Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more
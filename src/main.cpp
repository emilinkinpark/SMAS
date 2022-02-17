/* The codes are licensed under GNU LESSER GENERAL PUBLIC LICENSE
 *   Copyright © 2007 Free Software Foundation, Inc. <https://fsf.org/>
 *   More on the lincense at <https://www.gnu.org/licenses/lgpl-3.0.en.html>
 *   Everyone is permitted to copy and distribute verbatim copies of this license document, but changing is not allowed.
 *
 *   Acknowledgement: The project uses a lot of free libraries from different contributors. An special thanks to all hard working software people.
 *                    Specific acknowledgement is made into the seperate files in the include folder.
 *
 *   The purpose of this project is to create a Weather Station Data Translator for Rouf Aquaculture Pvt. Ltd (Proposed) Khulna, Bangladesh Intensive Prawn Farming Project.
 *   The field slave devices talks back to ESP32 (Master) over RS485 Modbus.
 *   The data is taken in and send to MQTT Broker over Wifi
 *
 *   Dedicated to Tyler Goodwin, the mate who influenced me to join the software side;
 *
 */


// Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more

#include <Arduino.h>
#include "headers.h"

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
  rainVol(wsRainclear);

#ifdef ENABLE_MQTT
  // MQTT Publish
  publish(0, "MQTT/HATCHERY2/heart");
  subscribe("MQTT/HATCHERY2/rainClear"); // 24 Rain Clear Command Subscribtion
  publish(wsRainclear, "MQTT/HATCHERY2/rainClear");

#ifdef ENABLE_BME680
  publish(relHum1, "MQTT/HATCHERY2/relativeHumidity");
  publish(temp1, "MQTT/HATCHERY2/outdoorTemp");
#endif

#ifdef ENABLE_BH1750
  publish(lux, "MQTT/HATCHERY2/lightIntensity");
#endif

#ifdef ENABLE_DS18B20
  publish(temperature_1, "MQTT/HATCHERY2/soilTemp");
#endif

#ifdef ENABLE_MOISTSENSOR
  publish(soilmoistperc, "MQTT/HATCHERY2/soilmoisture");
#endif

#ifdef ENABLE_RAINVOLUME
  publish(rainvol, "MQTT/HATCHERY2/rainVolume");
#endif

#ifdef ENABLE_WINDSPEED
  publish(windspeed, "MQTT/HATCHERY2/windSpeed");
#endif

#ifdef ENABLE_WINDDIR
  publish(winddir, "MQTT/HATCHERY2/windDirection");
#endif

  publish(1, "MQTT/HATCHERY2/heart");
#endif
  vTaskDelay(2000 / portTICK_PERIOD_MS);
}
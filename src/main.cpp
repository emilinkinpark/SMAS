/* Checklist before uploading to device, remember to KISS (Keep It Super Simple)
 * Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more
 * To enable or disable type of sensor, check enabler.h
 * Always Change MQTT Topic using Find and Replace; usually MQTT/TEST would be used for TESTing
 */
#include <Arduino.h>
#include "headers.h"

Preferences preferences;
TaskHandle_t Task1, Task2; // FreeRTOS Schedule Handler

void sensors(void *param)
{
  sensInit();    // Initialising All MODBUS Sensors
  i2cInit();     // Initialising Default I2C Pins
  bme680Init();  // Intialising BME680
  bh1750Init();  // Initialising BH1750
  ds18b20init(); // Intialising DS18B20
  for (;;)
  {
    DO();                 // Read DO Sensor
    bme680Loop();         // BME680
    bh1750Loop();         // BH1750
    ds18b20Loop();        // DS18B20
    moistsensLoop();      // Moisture Sensor
    rainVol(wsRainclear); // Rain Volume Sensor
    windSpeed();          // Wind Speed Sensor
    windDir();            // Wind Direction Sensor
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void wireless(void *param)
{
  mqttInit(); // Initialising MQTT Parameters, check mqtt.h for more
  webserverInit();
  for (;;)
  {
    // Subscribe to MQTT Topics
    int sizearr = sizeof(subTopic) / sizeof(subTopic[0]);

    for (int i = 0; i < sizearr; i++)
    {
      subscribe(subTopic[i]);
    }
    // espReset(); // Resets on MQTT Command

#ifdef ENABLE_MQTT
    // MQTT Publish
    mqttClient.publish(pubTopic[0], 0, false, "1");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
#ifdef ENABLE_BME680
    mqttClient.publish(pubTopic[2], 0, false, String(relHum1).c_str());
    mqttClient.publish(pubTopic[3], 0, false, String(temp1).c_str());
    mqttClient.publish(pubTopic[13], 0, false, String(pressure).c_str());
    // mqttClient.publish(pubTopic[14], 0, false, String(altitude).c_str());

#endif
#ifdef ENABLE_BH1750
    mqttClient.publish(pubTopic[4], 0, false, String(lux).c_str());
#endif

#ifdef ENABLE_DS18B20
    mqttClient.publish(pubTopic[5], 0, false, String(dryAirT).c_str());
    mqttClient.publish(pubTopic[12], 0, false, String(soilT).c_str());
#endif

#ifdef ENABLE_MOISTSENSOR
    mqttClient.publish(pubTopic[6], 0, false, String(soilmoistperc).c_str());

#endif

#ifdef ENABLE_RAINVOLUME
    mqttClient.publish(pubTopic[7], 0, false, String(rainvol).c_str());

#endif

#ifdef ENABLE_WINDSPEED
    mqttClient.publish(pubTopic[8], 0, false, String(windspeed).c_str());

#endif

#ifdef ENABLE_WINDDIR
    mqttClient.publish(pubTopic[9], 0, false, String(winddir).c_str());

#endif

#ifdef ENABLE_DO
    mqttClient.publish(pubTopic[10], 0, false, String(averagedomgl).c_str());
    mqttClient.publish(pubTopic[11], 0, false, String(doTemp).c_str());
#endif

    mqttClient.publish(pubTopic[0], 0, false, "0");
    mqttClient.publish(pubTopic[1], 0, false, WiFi.localIP().toString().c_str());
#endif
    serverLoop();
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
  // free(subTopic); // Empties Stack Memory
}

bool motorInit = true; // Param for Triggering MOTOR PIN Once during cycle

void setup()
{
  Serial.begin(9600);
  // ioSetup(); // Testing IO Pins

  xTaskCreatePinnedToCore(
      sensors,   // Task Function
      "sensors", // Task Name
      5000,      // Stack Size
      NULL,      // Task Function Parameters
      1,         // Priority
      &Task1,    // Task Handler
      1);        // Core
  xTaskCreatePinnedToCore(
      wireless,   // Task Function
      "wireless", // Task Name
      5000,       // Stack Size
      NULL,       // Task Function Parameters
      1,          // Priority
      &Task2,     // Task Handler
      0);         // Core
}
  void loop()
  {

    // Should Remain Empty
  }

  // Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more
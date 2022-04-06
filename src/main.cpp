/* Checklist before uploading to device, remember to KISS (Keep It Super Simple)
 * Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more
 * To enable or disable type of sensor, check enabler.h
 * Always Change MQTT Topic using Find and Replace; usually MQTT/TEST would be used for TESTing
 */
#include <Arduino.h>
#include "headers.h" // Add all headers to the main page here

void wireless(void *Param)
{
  mqttInit(); // Initialising MQTT Parameters, check mqtt.h for more
  otaInit();  // Initialising OTA
  for (;;)
  {
    // Subscribe to MQTT Topics
    int sizearr = sizeof(subTopic) / sizeof(subTopic[0]);
    for (int i = 0; i < sizearr; i++)
    {
      subscribe(subTopic[i]);
    }

#ifdef ENABLE_MQTT
    // MQTT Publish
    mqttClient.publish(pubTopic[0], 0, false, "0");
#ifdef ENABLE_BME680
   publish(relHum1, pubTopic[2]);
   publish(temp1, pubTopic[3]);
#endif
#ifdef ENABLE_BH1750
    publish(lux, pubTopic[4]);
#endif

#ifdef ENABLE_DS18B20
    //publish(temperature_1, pubTopic[5]);
    publish(temperature_1, pubTopic[14]);
    publish(temperature_1, pubTopic[15]);
    
#endif

#ifdef ENABLE_MOISTSENSOR
    publish(soilmoistperc, pubTopic[6]);
#endif

#ifdef ENABLE_RAINVOLUME
    publish(rainvol, pubTopic[7]);
#endif

#ifdef ENABLE_WINDSPEED
    publish(windspeed, pubTopic[8]);
#endif

#ifdef ENABLE_WINDDIR
    publish(winddir, pubTopic[9]);
#endif

#ifdef ENABLE_DO
    publish(averagedomgl, pubTopic[10]);
    publish(doTemp, pubTopic[11]);
#endif
#ifdef ENABLE_MOTORCONTROL
    publish(blowerStat, pubTopic[12]);
#endif
#ifdef ENABLE_CALLINGBELL
    publish(callingbell, pubTopic[13]);
#endif
    mqttClient.publish(pubTopic[0], 0, false, "1");
    mqttClient.publish(pubTopic[1], 0, false, WiFi.localIP().toString().c_str());
#endif
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

void allSensors(void *Param)
{
  sensInit();    // Initialising All MODBUS Sensors
  i2cInit();     // Initialising Default I2C Pins
  bme680Init();  // Intialising BME680
  bh1750Init();  // Initialising BH1750
  ds18b20init(); // Intialising DS18B20
  for (;;)
  {
    bme680Loop();         // BME680
    bh1750Loop();         // BH1750
    ds18b20Loop();        // DS18B20
    moistsensLoop();      // Moisture Sensor
    rainVol(wsRainclear); // Rain Volume Sensor
    windSpeed();          // Wind Speed Sensor
    windDir();            // Wind Direction Sensor
    tempHumid();          // Outdoor Humidity and Temperature Sensor
    DO();                 // Dissolved Oxygen Sensor

    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}

void ioControl(void *Param)
{
  ioSetup();

  for (;;)
  {

    callingbell = digitalRead(16);

#ifdef ENABLE_MOTORCONTROL
    switch (Mode)
    {
    case 1: // Dependant
      salinity = Salinity;
      blowerStat = motorControl(averagedomgl, doLow, doHigh);
      if (blowerStat == true)
      {
        digitalWrite(20, HIGH);
      }
      else
      {
        digitalWrite(20, LOW);
      }
      break;

    default: // Independant
      blowerStat = motorControl(averagedomgl, 4.5, 5.0);
      if (blowerStat == true)
      {
        digitalWrite(20, HIGH);
      }
      else
      {
        digitalWrite(20, LOW);
      }
      break;
    }
#endif
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(9600);
  xTaskCreatePinnedToCore(wireless, "wireless", 5000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(allSensors, "allSensors", 10000, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(ioControl, "pumpControl", 5000, NULL, 1, NULL, 1);
}
void loop()
{
  //
}

// Do not forget to change IPAddress of ESP32 before uploading; Check wifi_keys.h for more
#include "enabler.h"
#include "Arduino.h"
#include "globalvar.h"

const int moistsensPin = 34; // ADC Hardware Connected Pin

int moistsensLoop()
{
#ifdef ENABLE_MOISTSENSOR
    uint moist = analogRead(moistsensPin);
    soilmoistperc = map(moist, AirVal, WaterVal, 0, 100);
    vTaskDelay(60000 / portTICK_PERIOD_MS);
#endif
#ifdef ENABLE_MOISTSENSOR_DEBUG
    Serial.print("Moisture Sensor ADC: ");
    Serial.println(moist);
    Serial.print("Moisture Sensor % : ");
    Serial.println(soilmoistperc);
#endif
    return 0;
}
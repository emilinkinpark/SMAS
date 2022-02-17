#include "enabler.h"
#include "Arduino.h"

const int moistsensPin = 34; // ADC Hardware Connected Pin

const int AirVal = 3583;
const int WaterVal = 1585;


uint soilmoistperc = 0;
int moistsensLoop()
{
#ifdef ENABLE_MOISTSENSOR
    uint moist = analogRead(moistsensPin);
    soilmoistperc = map(moist, AirVal, WaterVal, 0, 100);
#endif
#ifdef ENABLE_MOISTSENSOR_DEBUG
    Serial.print("Moisture Sensor ADC: ");
    Serial.println(moist);
    Serial.print("Moisture Sensor % : ");
    Serial.println(soilmoistperc);
#endif
    return 0;
}
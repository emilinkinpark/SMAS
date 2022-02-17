/* This code is taken from https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/
All rights to the unmodified code goes to Rui Santos from Random Nerd Tutorials

The modified bit of the code is owned by Rouf Bangladesh Pty Ltd

*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include "enabler.h"

float temperature_1 = 0.00;
//float temperature_2 = 0.00;

#define ONEWIREBUS 4 // Define OneWire Bus

OneWire oneWire(ONEWIREBUS);

DallasTemperature sensors(&oneWire);

void ds18b20init()
{
#ifdef ENABLE_DS18B20
    sensors.begin();
#endif
}

void ds18b20Loop()
{
#ifdef ENABLE_DS18B20
    sensors.requestTemperatures();
    temperature_1 = sensors.getTempCByIndex(0);
    //temperature_2 = sensors.getTempCByIndex(1);

#endif

#ifdef ENABLE_DS18B20_DEBUG
    Serial.print("Temperature 1: ");
    Serial.print(temperature_1);
    Serial.println(" °C");
    // Serial.print("Temperature 2: ");
    // Serial.print(temperature_2);
    // Serial.println(" °C");

#endif
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

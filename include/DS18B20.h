/* This code is taken from https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/
All rights to the unmodified code goes to Rui Santos from Random Nerd Tutorials

The modified bit of the code is owned by Rouf Bangladesh Pty Ltd

*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include "enabler.h"
#include "globalvar.h"

// float temperature_2 = 0.00;

//#define ONEWIREBUS 4 // Define OneWire Bus  // Use this for future Use
#define ONEWIREBUS 18    // Define OneWire Bus
#define SECONDWIREBUS 19 // Define OneWire Bus

OneWire oneWire(ONEWIREBUS);
OneWire secondWire(SECONDWIREBUS);

DallasTemperature firstSensor(&oneWire);
DallasTemperature secondSensor(&secondWire);

void ds18b20init()
{
#ifdef ENABLE_DS18B20
    firstSensor.begin();
    secondSensor.begin();
#endif
}

void ds18b20Loop()
{
#ifdef ENABLE_DS18B20

    firstSensor.requestTemperatures();
    temperature_1 = firstSensor.getTempCByIndex(0);
    secondSensor.requestTemperatures();
    temperature_2 = secondSensor.getTempCByIndex(0);

#endif

#ifdef ENABLE_DS18B20_DEBUG
    Serial.print("Temperature 1: ");
    Serial.print(temperature_1);
    Serial.println(" °C");
    Serial.print("Temperature 2: ");
    Serial.print(temperature_2);
    Serial.println(" °C");

#endif
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

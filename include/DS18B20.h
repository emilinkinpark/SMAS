/* This code is taken from https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/
All rights to the unmodified code goes to Rui Santos from Random Nerd Tutorials

The modified bit of the code is owned by Rouf Bangladesh Pty Ltd

*** A pull up Resistor 470 Ohm Must be connected to Data Pin of DS1280; 


*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include "enabler.h"
#include "globalvar.h"


#define ONEWIREBUS 4 // Define OneWire Bus  // Use this for future Use
//#define ONEWIREBUS 18 // Define OneWire Bus

OneWire oneWire(ONEWIREBUS);

DallasTemperature firstSensor(&oneWire);

#ifdef ENABLE_DS18B20_MULTI
#define SECONDWIREBUS 19 // Define OneWire Bus
OneWire secondWire(SECONDWIREBUS);
DallasTemperature secondSensor(&secondWire);
#endif

void ds18b20init()
{
#ifdef ENABLE_DS18B20
    firstSensor.begin();
#endif
#ifdef ENABLE_DS18B20_MULTI
    secondSensor.begin();
#endif
}
    float lasttemp=0;

float sigCondition(float temp)
{
    if (temp > 0 && temp <= 60)
    {
       lasttemp = temp;
        return temp;
    }
    else
    {
        return lasttemp;
        Serial.print("ELSE: "); Serial.println(lasttemp);
    }
}

void ds18b20Loop()
{
#ifdef ENABLE_DS18B20

    firstSensor.requestTemperatures();
    temperature_1 = sigCondition(firstSensor.getTempCByIndex(0));

#endif
#ifdef ENABLE_DS18B20_MULTI
    secondSensor.requestTemperatures();
    temperature_2 = sigCondition(secondSensor.getTempCByIndex(0));

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

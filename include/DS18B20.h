/* This code is taken from https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/
All rights to the unmodified code goes to Rui Santos from Random Nerd Tutorials

The modified bit of the code is owned by Rouf Bangladesh Pty Ltd

*** A pull up Resistor 4k7 Ohm Must be connected to Data Pin of DS1280;


*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include "enabler.h"
#include "globalvar.h"

#ifdef ENABLE_DS18B20

#define ONEWIREBUS 4 // Define OneWire Bus

OneWire oneWire(ONEWIREBUS);

DallasTemperature DS18B20(&oneWire);

DeviceAddress device1 = {0x28, 0x0F, 0xE1, 0x20, 0x26, 0x20, 0x01, 0x87}; // TANK2
//DeviceAddress device1 = {0x28, 0xCE, 0xA6, 0x29, 0x26, 0x20, 0x01, 0x04}; // TANK3
#endif

#ifdef ENABLE_DS18B20_DEBUG

int devCount;                    // Number of temperature devices found
DeviceAddress tempDeviceAddress; // Used to store unknown DS18B20
#endif

float sigCondition(float temp)
{
    float lasttemp = 0.00;
    if (temp > 0 && temp <= 60)
    {
        float lasttemp = temp;
        return temp;
    }
    else
    {
        return lasttemp;
#ifdef ENABLE_DS18B20_DEBUG

        Serial.print("ELSE: ");
        Serial.println(lasttemp);
#endif
    }
}

void printAddress(DeviceAddress deviceAddress) // Prints out devices address on the bus
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (deviceAddress[i] < 16)
            Serial.print("0");
        Serial.println(deviceAddress[i], HEX);
    }
}
void ds18b20init()
{
#ifdef ENABLE_DS18B20
    DS18B20.begin();
#endif
}

void ds18b20Loop()
{
#ifdef ENABLE_DS18B20
    DS18B20.requestTemperatures(); // Request DS18B20 Sensor Data
    device1T = DS18B20.getTempC(device1);
    if (device1T == -127.00)
    {
        device1T = 25.00;
    }
    else
    {
        // Do Nothing
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);
#endif

#ifdef ENABLE_DS18B20_DEBUG

    devCount = DS18B20.getDeviceCount();

    for (int i = 0; i < devCount; i++)
    {
        // Search the wire for address
        if (DS18B20.getAddress(tempDeviceAddress, i))
        {
            // Output the device ID
            Serial.print("Temperature for device: ");
            Serial.println(i, DEC);
            printAddress(tempDeviceAddress);
            // Print the data
            float tempC = DS18B20.getTempC(tempDeviceAddress);
            Serial.print("Temp C: ");
            Serial.println(tempC);
        }
    }
    Serial.print("device1T C: ");
    Serial.println(device1T);

#endif
}

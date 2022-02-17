#include <Arduino.h>
#include <Wire.h>
#include "enabler.h"

#define I2C_SDA 21
#define I2C_SCL 22

void i2cInit()
{
#ifdef ENABLE_I2C
    Wire.begin(I2C_SDA, I2C_SCL);
#endif
#ifdef ENABLE_I2CSCAN
    i2cScanner();
#endif
}

void i2cScanner()
{
    Serial.println();
    Serial.println("I2C scanner. Scanning ...");
    int count = 0;

    for (int i = 1; i < 120; i++)
    {
        Wire.beginTransmission(i);
        if (Wire.endTransmission() == 0)
        {
            Serial.print("Found address: ");
            Serial.print(i, DEC);
            Serial.print(" (0x");
            Serial.print(i, HEX);
            Serial.println(")");
            count++;
        }                                      // end of good response
        vTaskDelay(2000 / portTICK_PERIOD_MS); // give devices time to recover
    }                                          // end of for loop
    Serial.println("Done.");
    Serial.print("Found ");
    Serial.print(count, DEC);
    Serial.println(" device(s).");
}
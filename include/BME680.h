#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "enabler.h"

#define inSense1_ADDRESS 0X77

Adafruit_BME680 inSense1;

#define SEALEVELPRESSURE_HPA (1013.25)


void bme680Init()
{
#ifdef ENABLE_BME680
    bool status1 = inSense1.begin(inSense1_ADDRESS);

    inSense1.setTemperatureOversampling(BME680_OS_8X);
    inSense1.setHumidityOversampling(BME680_OS_2X);
    inSense1.setPressureOversampling(BME680_OS_4X);
    inSense1.setIIRFilterSize(BME680_FILTER_SIZE_3);

    // inSense1.setGasHeater(320, 150); // 320*C for 150 ms
#endif

#ifdef ENABLE_BME680_DEBUG
    if (!status1)
    {
        Serial.println(F("Could not find a valid sensor 1, check wiring!"));
        while (1)
            ;
    }
#endif
}

void bme680Loop()
{
#ifdef ENABLE_BME680
    unsigned long endTime1 = inSense1.beginReading();

    if (!inSense1.endReading())
    {
        Serial.println("Failed to complete reading sensor 1:(");
        return;
    }
    temp1 = inSense1.temperature;
    relHum1 = inSense1.humidity;
    pressure = inSense1.pressure;
    altitude = inSense1.readAltitude(SEALEVELPRESSURE_HPA);

    vTaskDelay(60000 / portTICK_PERIOD_MS);
// gasRes1 = inSense1.gas_resistance / 1000.0;
#endif
#ifdef ENABLE_BME680_DEBUG

    if (endTime1 == 0)
    {
        Serial.println(F("Failed to begin reading sensor 1 :("));
        return;
    }
    else
    {
        // Do Nothing
    }

    Serial.print(F("Sensor 1 Reading started at "));
    Serial.println(millis());
    Serial.print(F("and wll finish at "));
    Serial.println(endTime1);
    vTaskDelay(50 / portTICK_PERIOD_MS);

    Serial.print(F("Sensor 1 Temperature = "));
    Serial.println(temp1);
    Serial.print(F("Sensor 1 Humidity = "));
    Serial.println(relHum1);
    Serial.print(F("Sensor 1 Gas = "));
    Serial.println(gasRes1);
    Serial.print(F("Sensor 1 Pressure = "));
    Serial.println(pressure);
    Serial.print(F("Sensor 1 Altitude = "));
    Serial.println(altitude);
    vTaskDelay(100 / portTICK_PERIOD_MS);
#endif
}
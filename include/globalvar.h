#ifndef GLOBALVAR_H_INCLUDED

#define GLOBALVAR_H_INCLUDED

#include "Arduino.h"
// ADS1115 variable
int16_t results;
// BH1750 variable
float lux = 0.00;
// BME680 variables
float temp1 = 0.00;
float relHum1 = 0.00;
float gasRes1 = 0.00; // Not Used

// DS18B20 variables
float temperature_1 = 0.00;
float temperature_2 = 0.00;

// moisture sensor variables
const int AirVal = 3583;
const int WaterVal = 1585;
uint soilmoistperc = 0;

// MODBUS Sensor variables

//  Wind Speed Sensor JXBS-3001-FS-RS
float windspeed;

// Wind direction Sensor
int winddir = 0.00;

// Outdoor Temperature and Relative Humidity Sensor
float outdoorTemperature = 0.00;
float outdoorrealtiveHumidity = 0.00;

// Rainfall Volume Gauge
float rainvol = 0.00;

// DO sensor variables
float salinity = 11.00;
float doTemp = 0.00;
float averagedomgl = 0.00;

#endif /* GLOBALVAR_H_INCLUDED */
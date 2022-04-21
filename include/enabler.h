#ifndef ENABLER_H_INCLUDED

#define ENABLER_H_INCLUDED

/**** FUNCTION ENABLE ****/
#define ENABLE_WIFI   // Enables WiFi Connectivity
//#define ENABLE_I2C    // Enables I2C
#define ENABLE_MQTT   // Connects to MQTT Server and Starts OTA
#define ENABLE_OTA    // Starts OTA
#define ENABLE_MODBUS // Enables Modbus

/**** SENSOR ENABLE ****/
// #define ENABLE_BME680 // BME680 TEMPERATURE AND HUMIDITY SENSOR ENABLE (I2C)
// #define ENABLE_BH1750 // BH1750 LIGHT INTENSITY SENSOR ENABLE (I2C)
// #define ENABLE_ADS1115 // ADS1115 ADC Reading ENABLE (I2C)
// #define ENABLE_DS18B20     // DS18B20 Digital Temeperature Sensor (One Wire)
// #define ENABLE_DS18B20_MULTI // Enables Two DS18B20 Sensors
// #define ENABLE_MOISTSENSOR // Moisture Sensor (ADC)
// #define ENABLE_WINDSPEED   // WIND SPEED ENABLE (MODBUS)
// #define ENABLE_WINDDIR     // WIND DIRECTION ENABLE (MODBUS)
// #define ENABLE_RAINVOLUME  // RAIN GAUGE ENABLE (MODBUS)
#define ENABLE_DO          // DO Sensor ENABLE (MODBUS)

//#define ENABLE_pH   // pH Sensor ENABLE (MODBUS) // DEPRECATED since 2021
//#define ENABLE_TEMPHUMID // Temperature and Humidity Sensor (MODBUS) //DEPRECATED from 09102021

/**** DEBUG MODE ****/
//#define ENABLE_WIFI_DEBUG // Connects to MainBase if dont defined connects to GloryCTRL Network
//#define ENABLE_SERIAL_DEBUG // Initialises Serial Debug
//#define ENABLE_I2CSCAN      // Serial Prints I2C Address
//#define ENABLE_MQTTSUB_DEBUG   // Serial Prints MQTT Subscription Variables
//#define ENABLE_MODBUS_DEBUG // Serial Prints MODBUS RAW DATA
//#define ENABLE_MOISTSENSOR_DEBUG // Serial Prints Moisture Sensor Data
//#define ENABLE_BME680_DEBUG  // BME680 SENSOR DEBUG MODE (I2C)
//#define ENABLE_BH1750_DEBUG // BH1750 SENSOR DEBUG MODE (I2C)
//#define ENABLE_ADS1115_DEBUG // ADS1115 ADC Reading ENABLE (I2C)
//#define ENABLE_DS18B20_DEBUG // DS18B20 Temperature Sensor DEBUG MODE (One Wire)
//#define ENABLE_WINDSPEED_DEBUG // Serial Prints Wind Speed Data (MODBUS)
//#define ENABLE_WINDDIR_DEBUG // Serial Prints Wind Direction Data (MODBUS)
//#define ENABLE_RAINVOL_DEBUG // Serial Prints Rain Volume Data  (MODBUS)
//#define ENABLE_DO_DEBUG   // DO Sensor ENABLE (MODBUS)
//#define ENABLE_IOCONTROL_DEBUG // IOCONTROL DEBUG MODE

//#define ENABLE_pH   // pH Sensor ENABLE (MODBUS) // DEPRECATED from 2021
//#define ENABLE_TEMPHUMID_DEBUG // Serial Prints Temp and Humidity Data (MODBUS) //DEPRECATED from 09102021


/*** IO Control ***/
//#define ENABLE_CALLINGBELL    // Calling Bell 
#define ENABLE_MOTORCONTROL // Enables Ring Blower Control Logic

#endif /* ENABLER_H_INCLUDED */

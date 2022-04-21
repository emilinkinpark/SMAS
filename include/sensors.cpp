/*  Smoothed by Matthew Fryer
 */

#include "modbus.cpp"
#include "conversions.cpp"
#include <Smoothed.h>
#include "enabler.h"
#include "globalvar.h"

// Serial Pins Definition
#define UART1_RX 4
#define UART1_TX 2
#define UART2_RX 16
#define UART2_TX 17

// DO Sensor
#define O2_slaveID 0x0E
#define O2_slaveID_DEC 14

boolean doHeart = 0;
float DOmgl = 0.00;

/* // Deprecated since 2021
#define pH_slaveID 0x01
#define pH_slaveID_DEC 1
*/

// DO variables
Smoothed<float> AverageDOmgl;

void sensInit()
{
#ifdef ENABLE_MODBUS
  Serial2.begin(9600, SERIAL_8N1, UART2_RX, UART2_TX); // RX - Green //TX- White
  AverageDOmgl.begin(SMOOTHED_AVERAGE, 9);             // Initialising Average class
  Serial.println("Sensor Init Complete");
#endif
}

void windSpeed() // Wind Speed Sensor
{
#ifdef ENABLE_WINDSPEED
  byte buffLength = 8;
  int buff[buffLength];
  modbusMasterTransmit(3, 0x01, 0x03, 0x00, 0x00, 0x00, 0x02); // Request Data Block from Sensor
  vTaskDelay(200 / portTICK_PERIOD_MS);

  modbusRead(3, 1, buffLength, buff); // Acquiring Data
  float windspeedConv = buff[4] / 10.00;
  buff[6] = 0;
  // // Error Checking
  // if (windspeedConv >= 0.00 && windspeedConv <= 40.00)
  // {
  //   windspeed = windspeedConv;
  // }
  // else
  // {
  //   windspeed = 0.00;
  //   Serial.println("Wind Speed Sensor error");
  // }
  windspeed = windspeedConv;

  if (Serial2.available() > 0)
  {
    serial_flush_buffer(3); // Cleaning Response
  }
#ifdef ENABLE_WINDSPEED_DEBUG
  Serial.print("Wind Speed: ");
  Serial.println(windspeed);
#endif
#endif
}

void windDir() // Wind Direction Sensor
{
#ifdef ENABLE_WINDDIR
  byte buffLength = 6;
  int buff[buffLength];

  modbusMasterTransmit(3, 0x02, 0x03, 0x00, 0x00, 0x00, 0x01); // Request Data Block from Sensor
  vTaskDelay(200 / portTICK_PERIOD_MS);

  modbusRead(3, 2, buffLength, buff); // Acquiring Data

  uint winddirtemp = hex16_signedint(buff[3], buff[4]);
  if (winddirtemp >= 0 && winddirtemp <= 360)
  {
    winddir = winddirtemp;
  }
  else
  {
    winddir = 0;
    Serial.println("Wind Direction Sensor error");
  }

  if (Serial2.available() > 0)
  {
    serial_flush_buffer(3); // Cleaning Response
  }
#endif
#ifdef ENABLE_WINDDIR_DEBUG
  Serial.print("Wind Direction: ");
  Serial.println(winddir);
#endif
}

void tempHumid() // Depreciated from 09/10/2021 BME680 Used Instead
{
#ifdef ENABLE_TEMPHUMID
  byte buffLength = 8;
  int buff[buffLength];

  modbusMasterTransmit(3, 0x03, 0x03, 0x00, 0x00, 0x00, 0x02); // Request Data Block from Sensor
  vTaskDelay(200 / portTICK_PERIOD_MS);

  modbusRead(3, 0x03, buffLength, buff); // Acquiring Data

  outdoorrealtiveHumidity = hex16_signedint(buff[3], buff[4]) / 10.00; // Unit: deg C
  outdoorTemperature = hex16_signedint(buff[5], buff[6]) / 10.00;      // Unit is in %

  if (Serial2.available() > 0)
  {
    serial_flush_buffer(3); // Cleaning Response
  }

#ifdef ENABLE_TEMPHUMID_DEBUG
  Serial.print("Relative Humidity: ");
  Serial.println(outdoorrealtiveHumidity);
  Serial.print("Temperature: ");
  Serial.println(outdoorTemperature);
#endif
#endif
}

bool rainVol(bool clear)
{

  // Clears Rainfall Data if clear = true

#ifdef ENABLE_RAINVOLUME
  if (clear == true)
  {
    modbusMasterTransmit(3, 0x04, 0x06, 0x01, 0x08, 0x00, 0x01); // Request Data Block from Sensor
    vTaskDelay(200 / portTICK_PERIOD_MS);
    Serial.println("Rainfall Volume Clear"); // Needs to be done once every 24 hours

    if (Serial2.available() > 0)
    {
      serial_flush_buffer(3); // Cleaning Response
    }
  }
  else
  {
    byte buffLength = 12;
    int buff[buffLength];

    modbusMasterTransmit(3, 0x04, 0x03, 0x00, 0x00, 0x00, 0x04); // Request Data Block from Sensor
    vTaskDelay(200 / portTICK_PERIOD_MS);

    modbusRead(3, 0x04, buffLength, buff); // Acquiring Data

    uint timer = hex16_signedint(buff[7], buff[8]);       // Unit: seconds  Internal Timer of the Gauge
    rainvol = hex16_signedint(buff[9], buff[10]) / 10.00; // Unit is in %
  }

  if (Serial2.available() > 0)
  {
    serial_flush_buffer(3); // Cleaning Response
  }

#endif
#ifdef ENABLE_RAINVOL_DEBUG
  Serial.print("Rain Volume: ");
  Serial.println(rainvol);
  Serial.print("Rain Clear CMD: ");
  Serial.println(clear);
#endif
  return 0;
}

void DO(float saline)
{
#ifdef ENABLE_DO

  /* Flow Chart
                Start Measurement -> Delay 2 seconds ->               Request DO and Temp Data
                                                                |                                     ^
                                                                v                                     |
                                                        Gathers 10 DOmg/l samples for averaging -> Delay 1 second
                                                                |
                                                                v
                                                        Get Average DOmg/l data
                                                                |
                                                                v
                                                        Stop Measurement
                                                                |
                                                                v
                                                        Send Data to MQTT Broker
*/
  int o2[13]; // O2 buffer length must have a size of 12 bytes
  float tempDO = 0.00;
  byte DOfaultstatus = 0;

  // Start Measurement
  modbusMasterTransmit(3, O2_slaveID, 0x03, 0x25, 0x00, 0x00, 0x01); // Serial2 used for Transceive Data
  if (Serial2.available() > 0)
  {
    serial_flush_buffer(3); // Cleaning Response
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    for (byte count = 0; count <= 10; count++) // Receiving DO data 10 times and averaging
    {
      modbusMasterTransmit(3, O2_slaveID, 0x03, 0x26, 0x00, 0x00, 0x04); // Request Data Block from Sensor

      modbusRead(3, O2_slaveID_DEC, 13, o2); // Acquiring Data and saving into o2
      vTaskDelay(100 / portTICK_PERIOD_MS);

      tempDO = floatTOdecimal(o2[3], o2[4], o2[5], o2[6]);

      if (tempDO >= 0 && tempDO <= 40)
      {
        doTemp = tempDO;
      }
      else if (doTemp == 0.00) // Safety measure if DO sensor internal temperature sensor from not working
      {
        doTemp = 25.00;
      }
      else
      {
        doTemp = 25.00;
      }
      
      float Conv_DOPerc = floatTOdecimal(o2[7], o2[8], o2[9], o2[10]);

      memset(o2, 0, sizeof(o2)); // Empties array

      DOmgl = domglcalc(saline, doTemp, Conv_DOPerc);

      if (isnan(DOmgl) != 0.00) // Checks Error Data Received
      {
        count = count - 1;
        if (Serial2.available() > 0)
        {
          serial_flush_buffer(3); // Cleaning Response
        }
        DOfaultstatus++; // DOfaultstatus increment
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      else
      {
        AverageDOmgl.add(DOmgl); // Adds Data for averaging
        DOfaultstatus = 0;       // DOfaultstatus reset
      }
      if (DOfaultstatus >= 15) // If Sensor does not respond 15 times then, publish error and break;
      {
        doHeart = 0; // Sends out when DO Sensor Fails
#ifdef ENABLE_DO_DEBUG
        Serial.println("DO Sensor Failed");
#endif
        break;
      }
      else
      {
        doHeart = 1;
      }
    }

    // Stop Measurement
    modbusMasterTransmit(3, O2_slaveID, 0x03, 0x2E, 0x00, 0x00, 0x01);

    if (Serial2.available() > 0)
    {
      serial_flush_buffer(3); // Cleaning Response
    }

#ifdef ENABLE_DO_DEBUG
    Serial.println("DO Measurement Complete");
#endif

    averagedomgl = AverageDOmgl.get(); // Stores the average value into variable

    if (isnan(averagedomgl) != 0.00) // Checks Error Data Received
    {
      doHeart = 0;
#ifdef ENABLE_DO_DEBUG
      Serial.println("DO Heart Failure :(");
#endif
    }
    else
    {
      AverageDOmgl.clear(); // Clears Average data
    }
  }
  else
  {
    doHeart = 0;
#ifdef ENABLE_DO_DEBUG
    Serial.println("DO HEART WORKING :)");
    Serial.print("DO: ");
    Serial.println(averagedomgl);
    Serial.print("DO Temperature: ");
    Serial.println(doTemp);
#endif
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
#endif
}

/* // Deprecated in 2021 versions
void pH()
{
  int ph_temp[13]; //pH sensor buffer

  ph_heart = 0;

  modbusMasterTransmit(3, 0x01, 0x03, 0x00, 0x00, 0x00, 0x04); //Requesting ORP, pH, Temperature and Resistance
  if (Serial2.available() > 0)
  {
    serial_flush_buffer(3); //Cleaning Response
    delay(100);

    modbusMasterTransmit(3, 0x01, 0x03, 0x00, 0x00, 0x00, 0x04); //Requesting ORP, pH, Temperature and Resistance
    modbusRead(3, pH_slaveID_DEC, 15, ph_temp);                  //Acquiring Data and saving into ph_temp
    delay(100);

    //Serial.println("Slave ID not matched Transmission Halt!");
    //Serial.println(o2[0], HEX);
    //ORP = hex16_signedint(ph_temp[3], ph_temp[4]) / 10.00;
    ph_val = hex16_signedint(ph_temp[5], ph_temp[6]) / 100.00;
    ph_temperature = hex16_signedint(ph_temp[7], ph_temp[8]) / 10.00;
    memset(ph_temp, 0, sizeof(ph_temp)); //Empties array

    //resitance = hex16_signedint(ph_temp[9], ph_temp[10]);
    ph_heart = 1;
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
  else
  {
    ph_heart = 0;
    Serial.println("pH Sensor Not Detected");
  }
}
*/

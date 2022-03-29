#ifndef MQTTSUB_H_INCLUDED

#define MQTTSUB_H_INCLUDED

#include "Arduino.h"




// Subscription Global Variables
bool wsRainclear = false;

void rainsubscribe(char *topic, String messageTemp)
{

    if (strcmp(topic, "MQTT/weatherStation/rainClear") == 0)
    {
        // Serial.println(messageTemp); // Debugging
        if (messageTemp == "1")
        {
#ifdef ENABLE_RAINVOL_DEBUG
            Serial.println("Received 1");
#endif
            wsRainclear = true;
        }
        else if (messageTemp == "1.00")
        {
#ifdef ENABLE_RAINVOL_DEBUG
            Serial.println("Received 1");
#endif
            wsRainclear = true;
        }
        else if (messageTemp == "0")
        {
#ifdef ENABLE_RAINVOL_DEBUG
            Serial.println("Received 0");
#endif
            wsRainclear = false;
        }
        else if (messageTemp == "0.00")
        {
#ifdef ENABLE_RAINVOL_DEBUG
            Serial.println("Received 0");
#endif
            wsRainclear = false;
        }
        else
        {
            // Do Nothing
        }
    }
}



#endif /* MQTTSUB_H_INCLUDED */
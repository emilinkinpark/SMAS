
#include "wifi_keys.h"

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>


#define MQTT_HOST IPAddress(10, 0, 1, 2)
#define MQTT_PORT 1883




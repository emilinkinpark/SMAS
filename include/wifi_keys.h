#include <WiFi.h>
#include "enabler.h"
/*   Caution Read This before updating field devices using ElegantOs

1) local_IP adress must be set accordingly;
2) tankADDR must be updated
3) Update Salinity in conversions.cpp 
 
*/

// Declare static IPs of device
/* Static IP
10.0.1.6 -> HATCHERY2          OTA Address 10.0.1.6:4000/update
10.0.1.12 -> weatherStation    OTA Address 10.0.1.12:4000/update
10.0.1.19 -> Pond8             OTA Address 10.0.1.19:4000/update
10.0.1.20 -> Tank1             OTA Address 10.0.1.20:4000/update
10.0.1.21 -> Tank2             OTA Address 10.0.1.21:4000/update
10.0.1.22 -> Tank3             OTA Address 10.0.1.22:4000/update
*/


/*Note for Future, DHCP might be used in the future, a though a reporting database needs to be setup to keep track of the field devices*/
IPAddress local_IP(10, 0, 1, 6);
IPAddress gateway(10, 0, 1, 1);
IPAddress subnet(255, 255, 0, 0);

#ifdef ENABLE_WIFI_DEBUG
#define ssid "MainBase"
#define pass "Glory001!1"
#else
#define ssid "GloryCTRL"   
#define pass "Gloryhabib1@1"
#endif
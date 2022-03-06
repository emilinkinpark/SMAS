#include <WiFi.h>
#include "enabler.h"
/*   Caution Read This before updating field devices using ElegantOs

1) local_IP adress must be set accordingly;
2) tankADDR must be updated
3) Update Salinity in conversions.cpp 
 
*/

// Declare static IPs of device
/* Static IP
10.0.1.5 -> Test                //Always to be remain free for prototyping and testing
10.0.1.6 -> SCAL1              OTA Address 10.0.1.6:4000/update
10.0.1.7 -> SCAL2              OTA Address 10.0.1.7:4000/update
10.0.1.10 -> Siemens S700 PLC
10.0.1.12 -> weatherStation    OTA Address 10.0.1.12:4000/update
10.0.1.14 -> indoorAir
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
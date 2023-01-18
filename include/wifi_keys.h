#include <WiFi.h>
#include <ESPmDNS.h>
#include "enabler.h"
/*   Caution Read This before updating field devices using ElegantOs

1) local_IP adress must be set accordingly;
2) tankADDR must be updated
3) Update Salinity in conversions.cpp

*/

// Declare static IPs of device
/* Static IP
10.0.1.5 -> Test               //Always to be remain free for prototyping and testing http://10.0.1.5/update
10.0.1.6 -> SCAL1              OTA Address 10.0.1.6:4000/update
10.0.1.7 -> SCAL2              OTA Address 10.0.1.7:4000/update
10.0.1.10 -> Siemens S700 PLC  // Out of Bound for Use
10.0.1.12 -> weatherStation    OTA Address http://10.0.1.12/update
10.0.1.14 -> indoorAir         OTA Address http://10.0.1.14/update
10.0.1.19 -> Empty
10.0.1.20 -> Tank1             OTA Address http://10.0.1.20/update
10.0.1.21 -> Tank2             OTA Address http://10.0.1.21/update
10.0.1.22 -> Tank3             OTA Address http://10.0.1.22/update
*/

/*Note for Future, DHCP might be used in the future, a though a reporting database needs to be setup to keep track of the field devices*/
IPAddress local_IP(10, 0, 1, 14);
IPAddress gateway(10, 0, 1, 1);
IPAddress subnet(255, 255, 0, 0);

String hostname = "test"; //Use "name".local to access from network, " " means character

#ifdef ENABLE_WIFI_DEBUG
#define ssid "MainBase"
#define pass "Glory001!1"
#else
#define ssid "GloryCTRL"
#define pass "Gloryhabib1@1"
#endif


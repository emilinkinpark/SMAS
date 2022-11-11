#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "enabler.h"

AsyncWebServer server(80);

void otaSeq()
{

  server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", ""); });

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

void otaInit()
{
#ifdef ENABLE_OTA
  otaSeq(); // Initialising OTA
#endif
}

/* void otaLoop() // Deprecated from 27/11/2021
{
  AsyncElegantOTA.loop();
} */
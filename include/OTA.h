#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <ESPmDNS.h>
#include <string.h>
#include "enabler.h"
AsyncWebServer server(4000);

void otaSeq()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    Serial.print(".");
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", String(WiFi.localIP().toString()+":4000/update")); });

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
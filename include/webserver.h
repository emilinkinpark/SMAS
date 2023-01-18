#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "SPIFFS.h"
#include <Arduino_JSON.h>
#include "enabler.h"

AsyncWebServer server(80); // Server Open at Port 80

#ifdef ENABLE_WEBSERV
AsyncEventSource events("/events"); // Event Source on /events

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 9500;
#endif
void notFound(AsyncWebServerRequest *request)
{
#ifdef ENABLE_WEBSERV
  request->send(404, "text/plain", "Not found");
#endif
}

void webserverInit() // Server Source, Request and Response
{
#ifdef ENABLE_WEBSERV
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  disableCore0WDT(); /*Large Web Page doesnt provide call back to ESP32, as a result, the watchdog thinks that instructions have locked up and reboots*/

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", String(), false); }); // Main HTML //getSensorReadings
  server.on("/style", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/style.css", "text/css"); }); // Style Sheet
  server.on("/gloryagro", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/gloryagro.png", "image/png"); }); // Glory Agro Logo
  server.on("/sifd", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/sifd.png", "image/png"); }); // SIFD Logo

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client)
                   {
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    } });
  // send event with message "hello!", id current millis
  // and set reconnect delay to 1 second
  // client->send("hello!", NULL, millis(), 10000); });
  server.addHandler(&events);

  /*****
  Uncomment this section for parsing input data from webpage to ESP32
  Get form data from Web Page Forms and store into variable.
  *****/
  /* server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
             {
               String inputMessage;
               String inputParam;
               if (request->hasParam("lp"))             // Change PARAM to html input tag id
               {
                 inputMessage = request->getParam("lp")->value(); // Change PARAM to html input tag id
                 lp = inputMessage.toFloat();               // Set global variable and link it here
                 Serial.print("LP: ");
                 Serial.println(lp);  // Serial Debug
               }
                if (request->hasParam("hp"))             // Change PARAM to html input tag id
               {
                 inputMessage = request->getParam("hp")->value(); // Change PARAM to html input tag  or name
                 //hp = inputMessage.toFloat();               // Set global variable and link it here
                 Serial.print("hp: ");
                 Serial.println(hp);  // Serial Debug
               }
               if (request->hasParam("button"))             // Change PARAM to html input tag id
               {
                 inputMessage = request->getParam("button")->value(); // Change PARAM to html input tag id
                 int button = inputMessage.toInt();               // Set global variable and link it here
                 Serial.print("Button: ");
                 Serial.println(button);  // Serial Debug
               }
               else
               {
                 inputMessage = "No message sent";
                 inputParam = "none";
               });
               */
  // Start server

  server.onNotFound(notFound);
  server.begin();
#endif
#ifdef ENABLE_OTA
  AsyncElegantOTA.begin(&server); // Start ElegantOTA
#endif
}

void serverLoop()
{
#ifdef ENABLE_WEBSERV
  if ((millis() - lastTime) > timerDelay)
  {
    // Send Events to the client with the Sensor Readings Every 10 seconds
    // events.send("ping", NULL, millis());
    events.send(WiFi.localIP().toString().c_str(), "ip", millis());
    events.send(String(device1T).c_str(), "device1T", millis());
    events.send(String(device2T).c_str(), "device2T", millis());
    events.send(String(callbell).c_str(), "callbell", millis());
    lastTime = millis();
  }
#endif
}
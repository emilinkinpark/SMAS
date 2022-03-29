/*
  MQTT Client Powered by AsyncMqttClient
*/
#ifndef MQTT_H_INCLUDED

#define MQTT_H_INCLUDED

#include "mqtt_variables.h"
#include "enabler.h"
#include "mqttsub.cpp"

// Class Declaration
AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.config(local_IP, gateway, subnet, INADDR_NONE, INADDR_NONE);
  WiFi.begin(ssid, pass);
}

void connectToMqtt()
{
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event)
{
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event)
  {
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    connectToMqtt();
    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.println("WiFi lost connection");
    xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    xTimerStart(wifiReconnectTimer, 0);
    break;
  }
}

void onMqttConnect(bool sessionPresent) /// Check for mqtt publish and subscribe examples
{
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected())
  {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
  // Serial.println("Subscribe acknowledged.");
  // Serial.print("  packetId: ");
  // Serial.println(packetId);
  // Serial.print("  qos: ");
  // Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId)
{
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) // Reads Subscription Data
{
  // Receving Subscribed Data
  String messageTemp;
  for (int i = 0; i < len; i++)
  {
    messageTemp += (char)payload[i];
  }
  rainsubscribe(topic, messageTemp);
  
}

void onMqttPublish(uint16_t packetId)
{
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void publish(float var, const char *publishTopic) // Inputs the variable and sends to the specified topics
{
  char buf[100];
  dtostrf(var, 5, 2, buf);
  mqttClient.publish(publishTopic, 0, false, buf);
}

void subscribe(const char *subscribeTopic)
{
  mqttClient.subscribe(subscribeTopic, 2);
}

void mqttSeq()
{
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  // mqtt_topic_declaration();               // Deprecated from 2021 versions
}

void mqttInit()
{
#ifdef ENABLE_MQTT
  mqttSeq(); // Initialising MQTT Parameters, check mqtt.h for more
#endif
#ifdef ENABLE_WIFI
  connectToWifi(); // Initialising MQTT Parameters, check mqtt.h for more
#endif
}

#endif /* MQTT_H_INCLUDED */
// Deprecated from 2021 versions
/*

//Topic Declaration
char tankAddr[70] = tankADDR; //"MQTT/weatherStation";
char windSpeed_TOPIC[20];
char windDirection_TOPIC[20];
char outdoorTemp_TOPIC[20];
char relativeHumidity_TOPIC[20];
char rainVolume_TOPIC[20];
char heart_TOPIC[20];


void mqtt_topic_declaration() // Stores Topics into variables
{
  strcat(windSpeed_TOPIC, tankAddr);
  strcat(windSpeed_TOPIC, "/windSpeed"); //weatherStation/windSpeed  20 characters
  strcat(windDirection_TOPIC, tankAddr);
  strcat(windDirection_TOPIC, "/windDirection"); //weatherStation/windDirection  20 characters
  strcat(outdoorTemp_TOPIC, tankAddr);
  strcat(outdoorTemp_TOPIC, "/outdoorTemp"); //weatherStation/outdoorTemp  20 characters
  strcat(relativeHumidity_TOPIC, tankAddr);
  strcat(relativeHumidity_TOPIC, "/relativeHumidity"); //weatherStation/relativeHumidity  20 characters
  strcat(rainVolume_TOPIC, tankAddr);
  strcat(rainVolume_TOPIC, "/rainVolume"); //weatherStation/rainVolume  20 characters
  strcat(heart_TOPIC, tankAddr);
  strcat(heart_TOPIC, "/heart"); //weatherStation/relativeHumidity  20 characters
}


void mqttKepwarepublish(float var, const char *tag, const char *publish_topic) // Keepware Formate
{
  char temp[8];

  char buf[100];
  dtostrf(var, 1, 2, temp);
  strcpy(buf, "{");
  strcat(buf, "\"");
  strcat(buf, tag);
  strcat(buf, "\"");
  strcat(buf, "\:");
  strcat(buf, temp);
  strcat(buf, "}");
  mqttClient.publish(publish_topic, 1, false, buf);
}
*/

#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config/config_parameter.h"
#include "config/config_main.h"

extern const char* clientName;
extern const char* mqtt_server;

void mqtt_callback(char* topic, byte* message, unsigned int length);
void mqttReConnect();
void mqttEmit(String topic, String value);

 #endif
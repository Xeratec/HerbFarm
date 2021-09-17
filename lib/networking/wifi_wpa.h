#ifndef NETWORKING_WIFI_WPA_H
#define NETWORKING_WIFI_WPA_H

#include <Arduino.h>
#include <WiFi.h>

extern const char* clientName;
extern const char* wlan_ssid;
extern const char* wlan_pwd;
extern WiFiClient  wifiClient;

void setup_wifi();

#endif
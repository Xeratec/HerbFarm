#ifndef NETWORKING_WIFI_EAP_H
#define NETWORKING_WIFI_EAP_H

#include <Arduino.h>
#include <WiFi.h>
#include "esp_wpa2.h"

extern const char* clientName;
extern const char* wlan_ssid;
extern const char* wlan_pwd;
extern const char* eap_identity;
extern const char* eap_password;
extern WiFiClient  wifiClient;

void setup_wifi();

#endif
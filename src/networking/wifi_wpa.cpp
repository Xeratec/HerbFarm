#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>

#include "config/config_wifi.h"

void setup_wifi() {
  Serial.println(F("---------------Wlan WPA-------------"));
  Serial.print(F("-> Connecting to "));
  Serial.println(wlan_ssid);

  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  WiFi.begin(wlan_ssid, wlan_pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F(""));
  Serial.print(F("-> WiFi connected."));
  Serial.print(F("-> IP address: "));
  Serial.println(WiFi.localIP()); 
}
/**
 * wifi_wpa.c
 * 
 * This file is part of the Herb Farm distribution (https://github.com/Xeratec/HerbFarm).
 * Copyright (C) 2021 Philip Wiese
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "wifi_wpa.h"

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
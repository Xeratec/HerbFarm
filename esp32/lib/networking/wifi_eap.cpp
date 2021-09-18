/**
 * wifi_eap.c
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

#include "wifi_eap.h"

void setup_wifi() {
  Serial.println(F("---------------Wlan EAP-------------"));
  Serial.print(F("-> Connecting to "));
  Serial.println(wlan_ssid);

  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)eap_identity, strlen(eap_identity)); //provide identity
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)eap_identity, strlen(eap_identity)); //provide username --> identity and username is same
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)eap_password, strlen(eap_password)); //provide password
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
  esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
  WiFi.begin(wlan_ssid); //connect to wifi

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F(""));
  Serial.print(F("-> WiFi connected."));
  Serial.print(F("-> IP address: "));
  Serial.println(WiFi.localIP()); 
}
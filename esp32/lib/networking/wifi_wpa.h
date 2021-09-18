/**
 * wifi_wpa.h
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
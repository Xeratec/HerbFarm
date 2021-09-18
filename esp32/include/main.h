/**
 * main.h
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

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "config/config_main.h"
#include "config/config_parameter.h"
#include "config/config_wifi.h"

#include "mqtt.h"
#include "sensors.h"

#ifdef USE_WIFI_WPA
#include "wifi_wpa.h"
#endif

#ifdef USE_WIFI_EAP
#include "wifi_eap.h"
#endif

extern PubSubClient    client;
/**
 * config_wifi.h
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

#ifndef CONFIG_WIFI_H
#define CONFIG_WIFI_H

const char* clientName =  "com.maketec.esp32";

// MQTT configuration
// const char* mqtt_server = "maketec.vsos.ethz.ch";
const char* mqtt_server = "192.33.91.117"; // Same as "maketec.vsos.ethz.ch"
// const char* mqtt_server = "77.109.161.99"; // Local Server

#ifdef USE_WIFI_WPA
const char* wlan_ssid =   "WOKO";
const char* wlan_pwd  =   "WLAN-4-WOKO";
#endif

#ifdef USE_WIFI_EAP
const char* wlan_ssid = "eduroam";
#endif

const char* eap_identity = "wiesep@student-net.ethz.ch";
const char* eap_password = "TeR?86618.-18en";

#endif
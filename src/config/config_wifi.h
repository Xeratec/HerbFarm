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

const char* eap_identity = "wiesep@student-net.ethz.ch";
const char* eap_password = "TeR?86618.-18en";
#endif

#endif
#ifndef CONFIG_WIFI_H
#define CONFIG_WIFI_H

const char* clientName =  "com.maketec.esp32";

#ifdef USE_WIFI_WPA
const char* wlan_ssid =   "WOKO";
const char* wlan_pwd  =   "WLAN-4-WOKO";

#endif

#ifdef USE_WIFI_EAP
const char* wlan_ssid = "eduroam";
const char* wlan_host = "arduino.php5.sk"; 

#define EAP_IDENTITY "wiesep@student-net.ethz.ch"
#define EAP_PASSWORD "TeR?86618.-18en"


#endif

#endif
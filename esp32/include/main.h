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
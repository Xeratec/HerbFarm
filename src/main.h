#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "config/config_main.h"
#include "config/config_parameter.h"
#include "config/config_wifi.h"

#include "networking/mqtt.h"
#include "sensor/sensors.h"

#ifdef USE_WIFI_WPA
#include "networking/wifi_wpa.h"
#endif

#ifdef USE_WIFI_EAP
#include "networking/wifi_eap.h"
#endif

extern PubSubClient    client;
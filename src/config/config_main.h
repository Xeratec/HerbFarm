#ifndef CONFIG_MAIN_H
#define CONFIG_MAIN_H

// Configuration
#define DHTPIN            GPIO_NUM_4
#define DHTTYPE           DHT11    
#define SOILMOISTUREPIN   GPIO_NUM_34
#define WATERLEVELPIN     GPIO_NUM_35
#define LIGHTINTESITYPIN  GPIO_NUM_32
#define ULTRASONICPIN     GPIO_NUM_33
#define PUMPPIN           GPIO_NUM_23

// MQTT configuration
//const char* mqtt_server = "maketec.vsos.ethz.ch";
const char* mqtt_server = "192.33.91.117";

#endif
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "sensor/sensor.h"

#include "config/config_main.h"
#include "config/config_parameter.h"

#ifdef USE_WIFI_WPA
#include "networking/wifi_wpa.h"
#endif

#ifdef USE_WIFI_EAP
#include "networking/wifi_eap.h"
#endif

// Global Variables
WiFiClient      wifiClient;;
PubSubClient    client(wifiClient);
Sensor          sensors(DHTPIN, DHTTYPE, SOILMOISTUREPIN, WATERLEVELPIN, LIGHTINTESITYPIN, ULTRASONICPIN);

String          payload;

long timer_loop = 0;

void mqtt_callback(char* topic, byte* message, unsigned int length) {

}

void setup()
{
    Serial.begin(115200);
    Serial.println(F("########## Herb Farm V 1.0 #########"));
    Serial.println(F("############### SETUP ##############"));

    setup_wifi();

    sensors.init();
    sensors.printSensorDetails();

    client.setServer(mqtt_server, 1883);
    client.setCallback(mqtt_callback);

    pinMode(PUMPPIN, OUTPUT);

    Serial.println("Setup done");
}

void mqttReConnect() {
    while (!client.connected()) {
        Serial.print(F("-> Attempting MQTT connection to "));
        Serial.print(mqtt_server);
        Serial.print(F("... ")); 
        if (client.connect(clientName)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void mqttEmit(String topic, String value)
{
    client.publish((char*) topic.c_str(), (char*) value.c_str());
}

void loop()
{   

  
    if (!client.connected()) {
        mqttReConnect();
    }
    delay(100);
  

  // Broadcast sensor values every 5 seconds
    long now = millis();
    if (now - timer_loop > SENSOR_UPDATE_TIME) {
        timer_loop = now;

        Sensor::SensorData data = sensors.getSensorData();
        

        // Send data to MQTT Listener
        mqttEmit("herb-farm/temperature", (String) data.temperature());
        mqttEmit("herb-farm/humidity", (String) data.humidity());
        mqttEmit("herb-farm/soilMoisture", (String) data.soilMoisture());
        mqttEmit("herb-farm/waterLevel",   (String) data.waterLevel());

        /*
        // Pump control
        if (sensor_waterLevel_raw < LIMIT_WATERLEVEL) {
        if (sensor_soilMoisture_raw > LIMIT_MOISTURE) {
            digitalWrite(PUMPPIN, HIGH);
        } else {
            digitalWrite(PUMPPIN, LOW);
        }
        } else
        {
        digitalWrite(PUMPPIN, LOW);
        }
        */
  }
  
}

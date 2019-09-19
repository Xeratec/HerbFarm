#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "config/config_main.h"
#include "config/config_parameter.h"

#ifdef USE_WIFI_WPA
#include "networking/wifi_wpa.h"
#endif

#ifdef USE_WIFI_EAP
#include "networking/wifi_eap.h"
#endif

// Global Variables
WiFiClient wifiClient;;
PubSubClient client(wifiClient);
DHT_Unified dht(DHTPIN, DHTTYPE);

String    payload;

uint32_t  loopDelay_ms;

uint16_t  sensor_soilMoisture_raw;
uint16_t  sensor_waterLevel_raw;
uint16_t  sensor_lightIntensity_raw;
uint16_t  sensor_ultraSonic_raw;
float_t   sensor_temperature;
float_t   sensor_humidity;

long timer_loop = 0;

void setup_sensor_temperature() {
    Serial.println(F("-------------Sensor: Temp-----------"));
    dht.begin();

    // Print temperature sensor details.
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F(""));
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    // Set delay between sensor readings based on sensor details.
    loopDelay_ms = sensor.min_delay / 1000;
}

void mqtt_callback(char* topic, byte* message, unsigned int length) {

}

void setup()
{
    Serial.begin(115200);
    Serial.println(F("########## Herb Farm V 1.0 #########"));
    Serial.println(F("############### SETUP ##############"));
    setup_wifi();
    setup_sensor_temperature();

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

        sensors_event_t event;
        dht.temperature().getEvent(&event);
        if (isnan(event.temperature)) {
            Serial.println(F("Error reading temperature!"));
        }
        else {
            Serial.print(F("Temperature: "));
            Serial.print(event.temperature);
            Serial.println(F("°C"));
            sensor_temperature = event.temperature;
        }
        // Get humidity event and print its value.
        dht.humidity().getEvent(&event);
        if (isnan(event.relative_humidity)) {
            Serial.println(F("Error reading humidity!"));
        }
        else {
            Serial.print(F("Humidity: "));
            Serial.print(event.relative_humidity);
            Serial.println(F("%"));
            sensor_humidity = event.relative_humidity;
        }

        sensor_soilMoisture_raw = analogRead(SOILMOISTUREPIN);
        Serial.print(F("Soil Moisture: "));
        // Convert values to percentage
        //sensor_soilMoisture_raw = map(sensor_soilMoisture_raw,4096,0,1,100);
        Serial.println(sensor_soilMoisture_raw);

        sensor_waterLevel_raw = analogRead(WATERLEVELPIN);
        Serial.print(F("Water Level: "));
        // Convert values to percentage
        //sensor_waterLevel_raw = map(sensor_waterLevel_raw,0,4096,0,100);
        Serial.println(sensor_waterLevel_raw);

        // Send data to MQTT Listener
        mqttEmit("herb-farm/temperature", (String) sensor_temperature);
        mqttEmit("herb-farm/humidity", (String) sensor_humidity);
        mqttEmit("herb-farm/soilMoisture", (String) sensor_soilMoisture_raw);
        mqttEmit("herb-farm/waterLevel",   (String) sensor_waterLevel_raw);

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

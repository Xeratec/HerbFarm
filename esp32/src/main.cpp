#include "main.h"

// Global Variables
Sensors sensors(DHTPIN, DHTTYPE, SOILMOISTUREPIN, WATERLEVELPIN, LIGHTINTESITYPIN, ULTRASONICPIN);

long timer_loop = 0;

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
    digitalWrite(PUMPPIN, LOW);

    Serial.println("-- Setup done --");
}

void loop()
{   
    if (!client.connected()) {
        mqttReConnect();
    }
    client.loop();
    delay(100);

    // Broadcast sensor values every 5 seconds
    long now = millis();
    if (now - timer_loop > SENSOR_UPDATE_TIME) {
        timer_loop = now;

        Sensors::SensorData data = sensors.getSensorData();
        data.printData();
        Serial.println();

        // Send data to MQTT Listener
        mqttEmit("herb-farm/temperature", (String) data.temperature());
        mqttEmit("herb-farm/humidity", (String) data.humidity());
        mqttEmit("herb-farm/soilMoisture", (String) data.soilMoisture());
        mqttEmit("herb-farm/waterLevel",   (String) data.waterLevel());
  }
}
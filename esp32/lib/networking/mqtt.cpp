/**
 * mqtt.c
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

#include "mqtt.h"

WiFiClient      wifiClient;;
PubSubClient    client(wifiClient);


void mqtt_callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;
    
    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    // if (String(topic) == "herb-farm/pump") {
    //     if (messageTemp == "timed"){
    //         Serial.print("Pumping water for ");
    //         Serial.print(PUMP_DURATION);
    //         Serial.println(" 5s!");
    //         digitalWrite(PUMPPIN, HIGH);
    //         delay(PUMP_DURATION); 
    //         digitalWrite(PUMPPIN, LOW);
    //    }
    // }
}

void mqttReConnect() {
    while (!client.connected()) {
        Serial.print(F("-> Attempting MQTT connection to "));
        Serial.print(mqtt_server);
        Serial.print(F("... ")); 
        if (client.connect(clientName)) {
            Serial.println("connected");
            client.subscribe("herb-farm/pump");  
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

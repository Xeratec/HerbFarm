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

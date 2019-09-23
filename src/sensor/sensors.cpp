#include "sensors.h"

void Sensors::SensorData::printData() {
    Serial.print("Temperature: ");
    Serial.print(temperature());
    Serial.println("°C");

    Serial.print("Humidity: ");
    Serial.print(humidity());
    Serial.println("%");

    Serial.print("Soil Moisture: ");
    Serial.println(soilMoisture());

    Serial.print("Water Level: ");
    Serial.println(waterLevel());
}

float_t Sensors::SensorData::temperature() {
    return temperature_raw;
}

float_t Sensors::SensorData::humidity() {
    return humidity_raw;
}

float_t Sensors::SensorData::soilMoisture() {
    return soilMoisture_raw;
}

float_t Sensors::SensorData::waterLevel() {
    return waterLevel_raw;
}

float_t Sensors::SensorData::tankLevel() {
    return ultraSonic_raw;
}

Sensors::Sensors(uint8_t dht_pin, uint8_t dht_type, uint8_t waterLevel_pin, uint8_t soilMoisture_pin, uint8_t lightIntensity_pin, uint8_t ultraSonic_pin) : 
    device_dht(DHT_Unified(dht_pin, dht_type)) 
{

    sensor_soilMoisture_pin = soilMoisture_pin;
    sensor_waterLevel_pin = waterLevel_pin;
    sensor_lightIntensity_pin = lightIntensity_pin;
}

void Sensors::init() {
    device_dht.begin();
}
    
Sensors::SensorData Sensors::getSensorData() {
    SensorData data;
    sensors_event_t event;

    device_dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
    }
    else {
        data.temperature_raw = event.temperature;
    }
    // Get humidity event and print its value.
    device_dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
    }
    else {
        data.humidity_raw = event.relative_humidity;
    }

    data.soilMoisture_raw = analogRead(sensor_soilMoisture_pin);

    data.soilMoisture_raw = analogRead(sensor_waterLevel_pin);

    return data;

}

void Sensors::printSensorDetails() {
    // Print temperature sensor details.
    Serial.println(F("-------------Sensors: Temp-----------"));
    sensor_t sensor;
    device_dht.temperature().getSensor(&sensor);
    Serial.println(F("Temperature Sensors"));
    Serial.print  (F("Sensors Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F(""));
    // Print humidity sensor details.
    device_dht.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensors"));
    Serial.print  (F("Sensors Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
}


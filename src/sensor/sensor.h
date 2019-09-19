#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class Sensor {
    public:
        class SensorData;
        // (De-) / Constructor
        Sensor(uint8_t dht_pin, uint8_t dht_type, uint8_t waterLevel_pin, uint8_t soilMoisture_pin, uint8_t lightIntensity_pin, uint8_t ultraSonic_pin);
        ~Sensor();
        void init();

        SensorData  getSensorData();
        void        printSensorDetails();

        uint8_t sensor_soilMoisture_pin;
        uint8_t sensor_waterLevel_pin;
        uint8_t sensor_lightIntensity_pin;
        

    private:
        DHT_Unified     device_dht;


};

class Sensor::SensorData {
    public:
        std::string to_string();
        float_t     temperature(); 
        float_t     humidity();
        float_t     soilMoisture();
        float_t     waterLevel();
        float_t     tankLevel();

        uint16_t    temperature_raw;
        uint16_t    humidity_raw;
        uint16_t    soilMoisture_raw;
        uint16_t    waterLevel_raw;
        uint16_t    lightIntensity_raw;
        uint16_t    ultraSonic_raw;

};

#endif
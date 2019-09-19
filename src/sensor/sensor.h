#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class Sensor {
    public:
        void    printSensorDetails();

        class SensorData {
            public:
                operator    sdt::string()   const;
                float_t     temperature(); 
                float_t     humidity();
                float_t     soilMoisture();
                float_t     waterLevel();
                float_t     tankLevel();
            private:
                uint16_t    temperature_raw;
                uint16_t    humidity_raw;
                uint16_t    soilMoisture_raw;
                uint16_t    waterLevel_raw;
                uint16_t    lightIntensity_raw;
                uint16_t    ultraSonic_raw;

        };

    private:
        DHT_Unified     sensor_dht;


}




#endif
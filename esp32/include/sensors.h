/**
 * sensors.h
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

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "config/config_parameter.h"

class Sensors {
    public:
        class SensorData;
        // (De-) / Constructor
        Sensors(uint8_t dht_pin, uint8_t dht_type, uint8_t waterLevel_pin, uint8_t soilMoisture_pin, uint8_t lightIntensity_pin, uint8_t ultraSonic_pin);
        void init();

        SensorData  getSensorData();
        void        printSensorDetails();

        uint8_t sensor_soilMoisture_pin;
        uint8_t sensor_waterLevel_pin;
        uint8_t sensor_lightIntensity_pin;
        

    private:
        DHT_Unified     device_dht;


};

class Sensors::SensorData {
    public:
        void        printData();
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
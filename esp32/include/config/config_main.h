/**
 * config_main.h
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

#endif
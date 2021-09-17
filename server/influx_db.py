#!/usr/bin/env python3


"""A MQTT to InfluxDB Bridge

This script receives MQTT data and saves those to InfluxDB.

"""

import re
import datetime
from typing import NamedTuple

import paho.mqtt.client as mqtt
from influxdb import InfluxDBClient
import logging

INFLUXDB_ADDRESS = 'localhost'
INFLUXDB_USER = 'xertatec'
INFLUXDB_PASSWORD = 'Sxx59913'
INFLUXDB_DATABASE = 'iot'

MQTT_ADDRESS = 'localhost'
MQTT_USER = 'mqttuser'
MQTT_PASSWORD = 'mqttpassword'
MQTT_TOPIC = 'herb-farm/+'
MQTT_REGEX = 'herb-farm/([^/]+)'
MQTT_CLIENT_ID = 'MQTTInfluxDBBridge'

influxdb_client = InfluxDBClient(INFLUXDB_ADDRESS, 8086, INFLUXDB_USER, INFLUXDB_PASSWORD, None)
logging.basicConfig(level=logging.INFO)

class SensorData(NamedTuple):
    location: str
    measurement: str
    value: float


def on_connect(client, userdata, flags, rc):
    """ The callback for when the client receives a CONNACK response from the server."""
    print('Connected with result code ' + str(rc))
    client.subscribe(MQTT_TOPIC)


def on_message(client, userdata, msg):
    """The callback for when a PUBLISH message is received from the server."""
    logging.info(msg.topic + ' ' + str(msg.payload))
    _send_sensor_data_to_influxdb(msg.topic, msg.payload.decode('utf-8'))


def _send_sensor_data_to_influxdb(sensor_topic, sensor_value):
    match = re.match(MQTT_REGEX, sensor_topic)
    measurement = match.group(1)
    current_time = datetime.datetime.utcnow().isoformat()
    json_body = [
        {
            "measurement": measurement,
            "tags": {},
            "time": current_time,
            "fields": {
                "value": float(sensor_value)
            }
        }
    ]
    logging.info(json_body)
    influxdb_client.write_points(json_body)


def _init_influxdb_database():
    databases = influxdb_client.get_list_database()
    print(databases)
    if len(list(filter(lambda x: x['name'] == INFLUXDB_DATABASE, databases))) == 0:
        influxdb_client.create_database(INFLUXDB_DATABASE)
    influxdb_client.switch_database(INFLUXDB_DATABASE)


def main():
    _init_influxdb_database()

    mqtt_client = mqtt.Client(MQTT_CLIENT_ID)
    mqtt_client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
    mqtt_client.on_connect = on_connect
    mqtt_client.on_message = on_message

    mqtt_client.connect(MQTT_ADDRESS, 1883)
    mqtt_client.loop_forever()


if __name__ == '__main__':
    print('MQTT to InfluxDB bridge')
    main()

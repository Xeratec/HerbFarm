#!/usr/bin/env python3

# webhook.py
#
# This file is part of the Herb Farm distribution (https://github.com/Xeratec/HerbFarm).
# Copyright (C) 2021 Philip Wiese
# 
# This program is free software: you can redistribute it and/or modify  
# it under the terms of the GNU General Public License as published by  
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program. If not, see <http://www.gnu.org/licenses/>.


from flask import Flask
from flask import request
from flask_httpauth import HTTPBasicAuth
import paho.mqtt.client as mqtt
import json

client = mqtt.Client()

app = Flask(__name__)
auth = HTTPBasicAuth()

# http basic auth credentials
users = {
    "xeratec": "Sxx59913"
}


@auth.get_password
def get_pw(username):
    if username in users:
        return users.get(username)
    return None


@app.route('/alert', methods=['POST'])
@auth.login_required
def alert():
    client.connect("docker", 1883, 60)
    data = json.loads(request.data.decode('utf-8'))
    if data['state'] == 'alerting':
        client.publish(topic="/alert", payload="1", retain=True)
    elif data['state'] == 'ok':
        client.publish(topic="/alert", payload="0", retain=True)

    client.disconnect()

    return "ok"


if __name__ == "__main__":
    app.run(host='0.0.0.0')

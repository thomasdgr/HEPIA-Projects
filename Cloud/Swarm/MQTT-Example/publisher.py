import paho.mqtt.client as mqtt
import os
import time

def on_connect(client, userdata, flags, rc):
    if rc==0:
        print("Connection Successful! Returned code =",rc)
    else:
        print("Unable to Connect. Returned code =", rc)

def sender(client):
    while True:
        client.publish('comms', 'MQTT Secret Message')
        print('Published on topic comms')
        time.sleep(10)

if __name__ == "__main__":
    client = mqtt.Client()
    client.on_connect = on_connect

    client.connect('broker', 1883, 60)

    sender(client)

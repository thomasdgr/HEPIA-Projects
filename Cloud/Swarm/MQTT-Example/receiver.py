import paho.mqtt.client as mqtt
import os
import time

def on_connect(client, userdata, flags, rc):
    if rc==0:
        print("Connection Successful! Returned code =",rc)
    else:
        print("Unable to Connect. Returned code =", rc)

def on_message(client, userdata, msg):
    print(msg.topic + ': ' + str(msg.payload.decode('utf-8')))


if __name__ == "__main__":
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect('broker', 1883, 60)
    client.subscribe('comms')
    client.loop_forever()

import paho.mqtt.client as mqtt
import sqlite3
from datetime import datetime

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/ab2017/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

    #Alt kısım gelen mesajı karakter dizisi olarak aldıktan sonra taklalar taklalar
    message = str(msg.payload)
    #gelen_mesajın 2 den balayıp son değer hariç alınması için
    message = message[2:-1]
    topic = msg.topic
    print("Topic: ", topic)
    print("Received Message: ", message)
    time_now = datetime.now()
    date_now = datetime.ctime(time_now)

    with sqlite3.connect('vt.sqlite') as vt:
        im = vt.cursor()

        #Create mqtt_data named database
        im.execute("""CREATE TABLE IF NOT EXISTS mqtt_data
            (date_now, topic, message)""")

        #we create coming_data tuple for use in the database
        incoming_data = (date_now, topic, message)

        #insert tuple data into database
        im.execute("""INSERT INTO mqtt_data VALUES
            (?, ?, ?)""", incoming_data)

        vt.commit()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("iot.eclipse.org", 1883, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()

import paho.mqtt.client as mqtt
import sqlite3
from datetime import datetime

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("Humidity")
#    client.subscribe("/ab2017/mesaj")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

    #Alt kısım gelen mesajı karakter dizisi olarak aldıktan sonra taklalar taklalar
    gelen_mesaj = str(msg.payload)
    print(type(gelen_mesaj))
    #gelen_mesajın 2 den balayıp son değer hariç alınması için
    gelen_mesaj_parse = gelen_mesaj[2:-1]
    print(gelen_mesaj_parse)
    konu = "Humidity"
#    konu = "/ab2017/mesaj"
    an = datetime.now()
    tarih = datetime.ctime(an)

    with sqlite3.connect('vt.sqlite') as vt:
        im = vt.cursor()

        im.execute("""CREATE TABLE IF NOT EXISTS mqtt_depo
            (tarih, konu, icerik)""")
        veriler = (tarih, konu, gelen_mesaj_parse)

        im.execute("""INSERT INTO mqtt_depo VALUES
            (?, ?, ?)""", veriler)

        vt.commit()

client = mqtt.Client()
client.username_pw_set(username="ijibrftp",password="-2kSKUN9MznW")
client.on_connect = on_connect
client.on_message = on_message

client.connect("m10.cloudmqtt.com", 11665, 60)

#client.connect("iot.eclipse.org", 1883, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()

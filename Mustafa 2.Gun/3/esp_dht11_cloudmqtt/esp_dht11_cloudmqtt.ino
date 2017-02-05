#include <ESP8266WiFi.h>    //Esp8266 Wifi kütüphanesi
#include <PubSubClient.h>   //MQTT için Publisher ve Subscriber Kütüphanesi
#include "ESP8266_UserCongiguration.h"
#include <dht11.h> // dht11 kütüphanesini ekliyoruz.

#define DHT11PIN 2 // DHT11PIN olarak Dijital 2'yi belirliyoruz.
dht11 DHT11;

#define mqtt_server "m10.cloudmqtt.com"
#define mqtt_user "ijibrftp"
#define mqtt_password "-2kSKUN9MznW"
#define topic1 ""
#define topic2 "Temp"
#define topic3 "Hhumidity"
#define readSize 6

void callback(char* topic, byte* payload, unsigned int length);
WiFiClient espClient;
PubSubClient client(mqtt_server, 11665, callback, espClient);

// Ledi 12. pine bağlıyoruz
int ledPin = 12;
// Alınan veriyi 0. pine bağlıyoruz
int receivedData = 0;



void setup() {

  // Ledi bağladığımız 12. pin için çıkış tanımlaması
  pinMode(ledPin, OUTPUT);
  //Arduino üzerinde kullandığımız Serial portun Baud Rate 'ini 115200 olarak ayarlıyoruz
  Serial.begin(115200);
  // Wifi kurulumu için oluşturduğumuz fonksiyonu çağırıyoruz
  setup_wifi();
  // Topic3 ten gelen veriyi subscribe ediyor
  client.subscribe(topic3);
}

// Alınan veriyi yazmak için callback fonksiyonu tanımlıyoruz.
void callback(char* topic, byte* payload, unsigned int length) {
  char rxBuffer[readSize]; //Gelen datayı okumak için bir Buffer dizisi tanımlıyoruz.
  Serial.println();
  Serial.print("Incoming data: "); //Gelen datayı seri port üzerinden yolla.
  //Serial.println(topic);
  for (int i = 0; i < readSize; i++) { //Gelen datayı diziye kaydet.
    if (rxBuffer[i - 2] != '.') { //Gelen datayı parse etmek için kullanılan koşul.
      rxBuffer[i] = payload[i];
    }
    else i = readSize - 1;
  }
  //Serial.print(rxBuffer);

  receivedData = atoi(rxBuffer); //Buffer daki datayı int e çevir.
  Serial.println(receivedData); //Parse edilmiş gelen datayı seri port üzerinden yolla.
}

void setup_wifi() {  // WIFI ye bağlanmak için oluşturulmuş fonksiyon.
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void reconnect() { //Eğer cihaz server a bağlanamazsa sürekli bağlanmayı denemesi için yazılmış fonksiyon.
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("TestMQTT", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }

}

void pubMQTT(String topic, float topic_val) { //MQTT üzerinden bir datayı yayımlamak için gerekli fonksiyon.
  Serial.print("Newest topic " + topic + " value:");
  Serial.println(String(topic_val).c_str());
  client.publish(topic.c_str(), String(topic_val).c_str(), true);
}

long lastMsg = 0;

int receivedLast = 0;

void loop() { // Sürekli döngü.
  if (!client.connected()) { //Eğer cihaz MQTT yer bağlı değilse bağlanıp okumayı dene.
    reconnect();
    client.subscribe(topic3);
    client.subscribe(topic2);
  }

  client.loop();

  //5 seconds
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    //Gelen datanın bir önceki gelen data ile aynı olup olmadığını karşılaştır.
    if (receivedData != receivedLast) {
      analogWrite(ledPin, receivedData);
      receivedLast = receivedData;
    }
    
    int chk = DHT11.read(DHT11PIN);// temperature değişkenini sıcaklık değerini alma fonksiyonuna bağlıyoruz.
    Serial.print("Nem (%): ");
    Serial.println((float)DHT11.humidity, 2);

    Serial.print("Sicaklik (Celcius): ");
    Serial.println((float)DHT11.temperature, 2);
    // Sensörden gelen sıcaklık değerini Serial monitörde yazdırıyoruz.

  
    //Publish Values to MQTT broker
    pubMQTT(topic2, DHT11.temperature);
    pubMQTT(topic3, DHT11.humidity);
  }
}

// Aşağıdaki fonksiyon DS18B20 sıcaklık sensörümüzden gelen verileri
// Celcius cinsinden sıcaklık değerlerine çevirmek için kullanılıyor.
// Herhangi bir değişiklik yapmamız gerekmiyor.



#include <ESP8266WiFi.h> //Esp8266 Wifi kütüphanesi
#include <PubSubClient.h> //MQTT için Publisher ve Subscriber Kütüphanesi
#include <OneWire.h> // OneWire kütüphanesini ekliyoruz.
#include "ESP8266_UserCongiguration.h"


#define mqtt_server "iot.eclipse.org"
#define mqtt_user "Mustafa"
#define mqtt_password "1234"
#define topic1 ""
#define topic2 "Cakir/temperature"
#define topic3 "Cakir/speed"
#define readSize 6


void callback(char* topic, byte* payload, unsigned int length);
WiFiClient espClient;
PubSubClient client(mqtt_server, 1883, callback, espClient);

// Ledi 12. pine bağlıyoruz
int ledPin = 12;
// Alınan veriyi 0. pine bağlıyoruz
int receivedData=0;
// Sıcaklık sensörünü bağladığımız dijital pini 2 olarak belirliyoruz.
int DS18S20_Pin = 2; 
// Sıcaklık Sensörü Giriş-Çıkışı
OneWire ds(DS18S20_Pin);  // 2. Dijital pinde.

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
  for(int i=0; i<readSize; i++){  //Gelen datayı diziye kaydet.
    if(rxBuffer[i-2]!='.'){ //Gelen datayı parse etmek için kullanılan koşul.
      rxBuffer[i]=payload[i];
      }
      else i=readSize-1; 
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
    if(client.connect("TestMQTT", mqtt_user, mqtt_password)) {
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

void pubMQTT(String topic,float topic_val){ //MQTT üzerinden bir datayı yayımlamak için gerekli fonksiyon.
  Serial.print("Newest topic " + topic + " value:");
  Serial.println(String(topic_val).c_str());
  client.publish(topic.c_str(), String(topic_val).c_str(), true);
}

long lastMsg = 0;

int receivedLast=0;

void loop() { // Sürekli döngü.
  if (!client.connected()) { //Eğer cihaz MQTT yer bağlı değilse bağlanıp okumayı dene.
    reconnect();
    client.subscribe(topic3);
    }

  client.loop();
    
//2 seconds 
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    //Gelen datanın bir önceki gelen data ile aynı olup olmadığını karşılaştır.
  if(receivedData!=receivedLast){     
    analogWrite(ledPin, receivedData);
    receivedLast=receivedData;
    }
    // temperature değişkenini sıcaklık değerini alma fonksiyonuna bağlıyoruz.
    float temperature = getTemp();
    // Sensörden gelen sıcaklık değerini Serial monitörde yazdırıyoruz.
    Serial.print("Sicaklik: ");
    Serial.println(temperature);
    //Publish Values to MQTT broker
    pubMQTT(topic2,temperature);
    
  }
}

// Aşağıdaki fonksiyon DS18B20 sıcaklık sensörümüzden gelen verileri
// Celcius cinsinden sıcaklık değerlerine çevirmek için kullanılıyor.
// Herhangi bir değişiklik yapmamız gerekmiyor.

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -2000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -2000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -2000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;

}

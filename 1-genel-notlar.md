# Bu bölümde genel bilgilendirmeler yazılacaktır

1. `Arduino Create` platformu kullanılıyor. Bunun için detaylı bilgiler https://www.arduino.cc/en/Main/Create adresinden erişilebilir.
2. Arduino Create platformu için temel kurulumlar yapıldıktan sonra ki bunlar `Arduino Web Editor` ü kullanabilmek için gereken plugin ve hesap oluşturma işlemi.
3. `Arduino web editor` usb bağlantısı için `/dev/ttyACM0` bağlantısını kullanıyor ve ubuntu da bunu kullanması için izin vermek gerekli. Çözüm önerileri şurada http://askubuntu.com/questions/58119/changing-permissions-on-serial-port verilmiş.
Biz kısaca şu işlemi yapıyoruz: `sudo usermod -a -G dialout USERNAME` ve otorumu kapatıp açıyoruz. Bu işlem ne mi işe yarar :) kendimizi `dialout` grubuna dahil etmemizi sağlar.

  Bunu sevmediysen her seferinde `sudo chmod 666 ttyACM0` şeklinde erişim izinlerini de düzenleyebilirsin lakin her bilgisayar açılış kapanışında yeniden yapman gerekir. Gereksiz uğraş...

4. Linux üzerinde ARDUINO 1.8.1 IDE kurulumu. (Kaynakça: https://www.arduino.cc/en/guide/linux)
 * Download ARDUINO 1.8.1 IDE
 * Dosyayı çıkar
 * Terminali aç ve çıkarılan dizinin içine gir
 * Bu komutu çalıştır `./install.sh`
 * Kurulum gerçekleştikten sonra USB izin ayarları ve bord seçimini yaparsın artık :)

5. Arduino IDE'ye ESP 8266 mod MCU desteği eklenmesi.
 * Detaylı `ESP8266 core for Arduino` bilgisi için lütfen okuyunuz: http://esp8266.github.io/Arduino/versions/2.3.0/
 * Detaylı anlatım için: http://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/
 * https://github.com/esp8266/Arduino kütüphanesini ekleyeceğiz.
 * http://arduino.esp8266.com/stable/package_esp8266com_index.json
 * üstteki bu satırı kopyalayıp ARDUİNO 1.6 ÜZERİ VERSYONU İÇİNE TERCİHLER/DEVREKARTLARI YÖNETİCİSİ URL ALANINA YAPIŞTIRIYORUZ.
 * SONRA ARAÇLAR / KART / KART YÖNETİCİSİNE GİRİP 2. versyonunu kuruyoruz. SONRA ARAÇLAR/KART/Node MCU 1.0 (ESP-12Module) seçilir.  Not: Biz Node MCU kullanarak devreden yırttık:)

6. MQTT ile mesaj gönderme durumu MQTT Dash isimli Android uygulamasını kurduk.
  * Ekle dedikten sonra
  * Adress kısmına `iot.eclipse.org` yazıyoruz bu ücretsiz olarak hizmet veriyor. Name:ozgur port:1883
  * Sonra tekrar ekle diyoruz ve name:ozgur Topic:ab2017/mesaj şeklinde topic belirledik. (Kafana göre belirleyebilirsin topic kısmını)
  * Add bölümünde `Text` `Switch/button` `Range/progress` `Multi choice` `Image` ve `Color` ekleyebiliyoruz.
  * Önemli bilgi - Eğer aynı topic ismi ile `text` ve `botton` ekler isek birbirlerinin üzerine yazabiliyorlar. Keyifli iş :)
7. Ubuntu üzerinde MQTT'ye mesaj gönderebilmek için verilmesi gereken komut `mosquitto_pub -h iot.eclipse.org -t ab2017/mesaj -m "Özgür mesaj"` tabi mosquitto_pub kurulacak önce :)

8. ESP ile HelloServer uygulama örneği
 * Arduino IDE üzerinden Examples--> ESP8266WebServer--> Helloserver yüklemesi yapılır.
 * const char* ssid = "............";
 * const char* password = "........";  Ayarlarını uygun şekilde yapıyoruz. Yani telefonun SSID ve Parolası
 * Yükleme işlemini yaptıktan sonra ESP yi bir defa resetleyip durumu Serial Motitörden takip edebiliriz.
 * Ayrıca ESP için yeni bir `IP adresi` atayacak, `Serial Monitörden` bunu görebilirsin. Bu atanmış `IP adresini` tarayıcıya girerek mesajı görebilirsin.

9. `esp_temperature.ino` uygulaması için yapılacaklar.
 * `one wire` by Jim studt isimli kütüphaneyi ekliyoruz.
 * https://github.com/knolleary/pubsubclient/releases/tag/v2.6 adresinden zip olarak indirdiğimiz library'i ekliyoruz.

10. 5 Şubat Pazar notları
 * CloudMQTT hesap açıldı. Ücretsiz olarak hesap açıp kullanılabiliyor. Site: https://www.cloudmqtt.com/
 * CloudMQTT Overview altındaki bilgiler, Telefonda `MQTT Dash` uygulamasına gerekli değerler girilerek izlenebiliyor.
 * GitHub çalışmaları yapıldı.
 * `http://remotexy.com` Grafiksel olarak MODMCU ve ARDUINO kullanabileceğimiz faydalı web sitesi. Deligibi arayüz tasarlayabilirsin. APPinventor'ın bir benzeri.

11. 6 Şubat Pazartesi notları `platformio` kurulumu ve temel kullanım
 * Kurulum detayları http://docs.platformio.org/en/latest/ide/atom.html#installation
 * Kurulumda, eğer atom kurulu ise `platformio-ide` paketinin atom içerisinden kurmak yeterli oluyor
 * Yeni proje oluştururken hem `arduino uno` ve `MODMCU` yu board olarak ekledik. Neden ikisini de ekledik diye sorarsan öyle çalıştı tam bilmiyoruz.
 * Alakasız ek bilgi: MODMCU firmware dosyasını yeniden daha küçük şekilde yapılandırabiliyoruz. Bunun için firmware'i https://nodemcu-build.com/ sitesinden seçenekleri azaltarak yapabiliriz.
 * `Raspberyy Pi` wifi ayarlarını komut satırından yapma için: https://www.raspberrypi.org/documentation/configuration/wireless/wireless-cli.md
 * Secure copy için örnekler: http://www.hypexr.org/linux_scp_help.php
 * Copy the file "foobar.txt" from the local host to a remote host için: `$ scp foobar.txt your_username@remotehost.edu:/some/remote/directory`
 * MQTT WEB Socket ücretsiz deme için: http://www.hivemq.com/demos/websocket-client/
 * Ayrıca MQTT temelleri ve uygulaması üzerine güzel bilgiler olan bir site: http://www.hivemq.com/

12. `Digitalocean` üzerinde mosquitto kurulumu:
 * mosquitto kurulur: `sudo apt install mosquitto`
 * mosquitto servisini durduruyoruz: `sudo service mosquitto stop`
 * mosquitto servisini yeniden çalıştırıyoruz: `service mosquitto start`
 * Burada bize port numarası ve gerekli bilgileri veriyor. 1883 olacak
 * Bu kadar :) Şuan telefonunuzda ki `Dashboard`tan ayarları girip ve `topic` oluşturup MQTT yi kullanabilirsiniz.

13. 7 Şubat Salı notlar
 * OTA uygulaması için kullandığımız kod: `karakaplanm/iot/OTAWebLed/`
 * Ota güncelleme kodu: `pio run -t upload --upload-port 192.168.43.116`
 * Tabii yukarıda kendi ağımızdaki ESP'nin ip adresini giriyoruz.
 * `IP` adresini öğrenmek ve ağa bağlı cihazları taramak için: `nmap -sn 192.168.1.1/24` veya `arp -a` da veya detaylı sorgulama için `sudo nmap -sP 192.168.43.0/24` kullanılabiliyor.
 * APPinventor kullanımı Android uygulaması yapabilirsin `scratch` e benziyor :)
 * APPinventor web sitesi http://appinventor.mit.edu/explore/
 * osc(open sound control) açık bir protokol, google play de arayüzeler var appinventor ile yapması zor olduğu için hazır arayüzler kullanılabilirmiş. Bu protokol ile direk cihazdan cihaza `UDP` portunu kullanarak gönderim yapılıyor.
 * 

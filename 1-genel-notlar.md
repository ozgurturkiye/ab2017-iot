# Bu bölümde genel bilgilendirmeler yazılacaktır

1. `Arduino Create` platformu kullanılıyor. Bunun için detaylı bilgiler https://www.arduino.cc/en/Main/Create adresinden erişilebilir.
2. Arduino Create platformu için temel kurulumlar yapıldıktan sonra ki bunlar `Arduino Web Editor` ü kullanabilmek için gereken plugin ve hesap oluşturma işlemi.
3. `Arduino web editor` usb bağlantısı için `/dev/ttyACM0` bağlantısını kullanıyor ve ubuntu da bunu kullanması için izin vermek gerekli. Çözüm önerileri şurada http://askubuntu.com/questions/58119/changing-permissions-on-serial-port verilmiş.
Biz kısaca şu işlemi yapıyoruz: `sudo usermod -a -G dialout USERNAME` ve otorumu kapatıp açıyoruz. Bu işlem ne mi işe yarar :) kendimizi `dialout` grubuna dahil etmemizi sağlar.

  Bunu sevmediysen her seferinde `sudo chmod 666 ttyACM0` şeklinde erişim izinlerini de düzenleyebilirsin lakin her bilgisayar açılış kapanışında yeniden yapman gerekir. Gereksiz uğraş...

4. Linux üzerinde ARDUINO 1.8.1 IDE kurulumu. (Kaynakça: https://www.arduino.cc/en/guide/linux)
 4.1 Download ARDUINO 1.8.1 IDE
 4.2 Dosyayı çıkar
 4.3 Terminali aç ve çıkarılan dizinin içine gir
 4.4 Bu komutu çalıştır `./install.sh`
 4.5 Kurulum gerçekleştikten sonra USB izin ayarları ve bord seçimini yaparsın artık :)
 
5. Arduino IDE'ye ESP 8266 mod MCU desteği eklenmesi.
 * https://github.com/esp8266/Arduino kütüphanesini ekleyeceğiz.
 * http://arduino.esp8266.com/stable/package_esp8266com_index.json
 * üstteki bu satırı kopyalayıp ARDUİNO 1.6 ÜZERİ VERSYONU İÇİNE TERCİHLER/DEVREKARTLARI YÖNETİCİSİ URL ALANINA YAPIŞTIRIYORUZ.
 * SONRA ARAÇLAR / KART / KART YÖNETİCİSİNE GİRİP 2. versyonunu kuruyoruz. SONRA ARAÇLAR/KART/Node MCU 1.0 (ESP-12Module) seçilir.  Not: Biz Node MCU kullanarak devreden yırttık:)

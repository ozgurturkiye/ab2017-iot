# Bu bölümde genel bilgilendirmeler yazılacaktır

1. `Arduino Create` platformu kullanılıyor. Bunun için detaylı bilgiler https://www.arduino.cc/en/Main/Create adresinden erişilebilir.
2. Arduino Create platformu için temel kurulumlar yapıldıktan sonra ki bunlar `Arduino Web Editor` ü kullanabilmek için gereken plugin ve hesap oluşturma işlemi.
3. `Arduino web editor` usb bağlantısı için `/dev/ttyACM0` bağlantısını kullanıyor ve ubuntu da bunu kullanması için izin vermek gerekli. Çözüm önerileri şurada http://askubuntu.com/questions/58119/changing-permissions-on-serial-port verilmiş.
Biz kısaca şu işlemi yapıyoruz: `sudo usermod -a -G dialout USERNAME` ve otorumu kapatıp açıyoruz. Bu işlem ne mi işe yarar :) kendimizi `dialout` grubuna dahil etmemizi sağlar.

> Bunu sevmediysen her seferinde `sudo chmod 666 ttyACM0` şeklinde erişim izinlerini de düzenleyebilirsin lakin her bilgisayar açılış kapanışında yeniden yapman gerekir. Gereksiz uğraş...

4. 

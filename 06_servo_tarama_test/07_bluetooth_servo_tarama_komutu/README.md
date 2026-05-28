# 07 Bluetooth Servo Tarama Komutu

Bu klasörde Bluetooth üzerinden gelen T komutu ile servo motorun tarama hareketini başlatan ve duraklatan Arduino kodu bulunur.

Bu kodda robot araba F, B, L, R ve S karakterleriyle kontrol edilir. Servo motor ise T karakteri ile başlatılır veya duraklatılır.

## Komutlar

| Komut | Görev |
|---|---|
| F | İleri |
| B | Geri |
| L | Sol |
| R | Sağ |
| S | Dur |
| T | Servo taramayı başlat / duraklat |

## Servo Tarama Mantığı

T komutu gönderildiğinde servo motor 20 derece ile 160 derece arasında sağa-sola tarama yapmaya başlar. T komutu tekrar gönderildiğinde servo motor bulunduğu açıda durur. Tekrar T komutu gönderilirse tarama kaldığı yerden devam eder.

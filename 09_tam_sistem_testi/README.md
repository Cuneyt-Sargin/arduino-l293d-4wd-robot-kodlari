# 09 Tam Sistem Testi

Bu klasörde 4WD Bluetooth robot arabanın tüm özelliklerini birlikte test eden Arduino kodu bulunur.

Bu kod ile robot araba Bluetooth üzerinden kontrol edilir. İleri, geri, sağ, sol ve dur hareketleri yapılabilir. Servo motor T komutu ile tarama yapar. Buzzer ise H ve h komutları ile korna olarak kullanılır.

## Komutlar

| Komut | Görev |
|---|---|
| F | İleri |
| B | Geri |
| L | Sol |
| R | Sağ |
| S | Dur |
| T | Servo taramayı başlat / duraklat |
| H | Kornayı başlat |
| h | Kornayı durdur |

## Bağlantılar

Bluetooth modülü:

| Bluetooth Modülü | L293D Motor Shield |
|---|---|
| VCC | SERVO2 + |
| GND | SERVO2 - |
| TX | A0 |
| RX | A1 |

Servo motor:

| Servo Kablosu | L293D Motor Shield SERVO1 |
|---|---|
| Kahverengi / Siyah | - |
| Kırmızı | + |
| Turuncu / Sarı | S |

Buzzer:

| Buzzer Ucu | Bağlantı |
|---|---|
| + | A5 |
| - | GND |

## Kullanılan Kod

sketch_may21g_tam_sistem_testi_bluetooth_servo_korna.ino

## Amaç

Robot arabanın hareket sistemi, Bluetooth bağlantısı, servo tarama ve korna özelliklerini birlikte test etmek.

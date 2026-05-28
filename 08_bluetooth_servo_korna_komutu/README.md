# 08 Bluetooth Servo Korna Komutu

Bu klasörde Bluetooth üzerinden robot araba hareketi, servo tarama ve buzzer/korna kontrolü yapan Arduino kodu bulunur.

Bu kodda robot araba F, B, L, R ve S karakterleriyle kontrol edilir. Servo motor T karakteri ile başlatılır veya duraklatılır. Buzzer ise H ve h karakterleriyle kontrol edilir.

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

sketch_may21f_bluetooth_servo_korna_H_h_komutu.ino

## Amaç

Robot arabaya hareket kontrolü, servo tarama ve korna özelliğini birlikte eklemek.

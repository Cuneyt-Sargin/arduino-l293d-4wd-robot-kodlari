# 04 Seri Monitörden Karakter Göndererek Robotu Yönetme

Bu klasörde Arduino IDE Seri Monitör ekranından F, B, L, R ve S karakterleri gönderilerek 4WD robot arabanın kontrol edildiği Arduino kodu bulunur.

Bu aşamada Bluetooth kullanılmaz. Komutlar bilgisayardan Arduino’ya USB kablosu üzerinden gönderilir.

## Kullanılan Komutlar

| Karakter | Görev |
|---|---|
| F | İleri |
| B | Geri |
| L | Sol |
| R | Sağ |
| S | Dur |

## Amaç

Bu uygulamanın amacı, Bluetooth bağlantısına geçmeden önce Arduino’nun Seri Monitör üzerinden gelen karakterleri okuyabildiğini ve bu karakterlere göre motorları kontrol edebildiğini öğrenmektir.

#include <AFMotor.h>
#include <SoftwareSerial.h>

/*
  4WD Bluetooth Robot Araba - L293D Motor Shield

  Bu kodda komutlar bilgisayardaki Seri Monitör'den değil,
  telefondaki Serial Bluetooth Terminal uygulamasından gönderilir.

  Arduino IDE Seri Monitör sadece gelen komutu görmek ve kontrol etmek için kullanılır.

  Bluetooth bağlantısı:
  HC-05 / HC-06 TX  -> Shield A0   // Arduino RX pini
  HC-05 / HC-06 RX  -> Shield A1   // Arduino TX pini
  HC-05 / HC-06 VCC -> Shield SERVO2 +
  HC-05 / HC-06 GND -> Shield SERVO2 -

  Not:
  Bluetooth modülünün RX pini 3.3V seviyesinde çalıştığı için
  Arduino A1 -> Bluetooth RX hattında gerilim bölücü kullanmak daha güvenlidir.
*/

SoftwareSerial BT(A0, A1);  // RX, TX

AF_DCMotor motor1(1);  // M1
AF_DCMotor motor2(2);  // M2
AF_DCMotor motor3(3);  // M3
AF_DCMotor motor4(4);  // M4

int hiz = 170;  // 0-255 arası hız değeri

void setup() {
  Serial.begin(9600);  // Arduino IDE Seri Monitör
  BT.begin(9600);      // Serial Bluetooth Terminal bağlantısı

  motorlariAyarla();
  dur();

  Serial.println("Bluetooth robot araba hazir.");
  Serial.println("Komutlar telefondaki Serial Bluetooth Terminal uygulamasindan gonderilir.");
  Serial.println("Seri Monitor sadece gelen komutlari gostermek icin kullanilir.");
  Serial.println("Komutlar: F=Ileri, B=Geri, L=Sol, R=Sag, S=Dur");
}

void loop() {
  if (BT.available()) {
    char komut = BT.read();

    if (komut == '\n' || komut == '\r' || komut == ' ') {
      return;
    }

    if (komut >= 'a' && komut <= 'z') {
      komut = komut - 32;
    }

    Serial.print("Gelen komut: ");
    Serial.println(komut);

    if (komut == 'F') {
      Serial.println("Hareket: ILERI");
      ileri();
    }
    else if (komut == 'B') {
      Serial.println("Hareket: GERI");
      geri();
    }
    else if (komut == 'L') {
      Serial.println("Hareket: SOLA DON");
      solaDon();
    }
    else if (komut == 'R') {
      Serial.println("Hareket: SAGA DON");
      sagaDon();
    }
    else if (komut == 'S') {
      Serial.println("Hareket: DUR");
      dur();
    }
    else {
      Serial.println("Bilinmeyen komut. Kullan: F, B, L, R, S");
      dur();
    }
  }
}

void motorlariAyarla() {
  motor1.setSpeed(hiz);
  motor2.setSpeed(hiz);
  motor3.setSpeed(hiz);
  motor4.setSpeed(hiz);
}

void ileri() {
  motorlariAyarla();

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void geri() {
  motorlariAyarla();

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void sagaDon() {
  motorlariAyarla();

  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
}

void solaDon() {
  motorlariAyarla();

  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void dur() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
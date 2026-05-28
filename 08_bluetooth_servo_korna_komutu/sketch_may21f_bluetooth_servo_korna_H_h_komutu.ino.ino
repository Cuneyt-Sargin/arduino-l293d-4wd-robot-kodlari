#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

/*
  4WD Bluetooth Robot Araba
  Arduino Uno + L293D Motor Shield + HC-05 / HC-06 + Servo + Buzzer

  Bluetooth bağlantısı:
  HC-05 / HC-06 TX  -> Shield A0
  HC-05 / HC-06 RX  -> Shield A1
  HC-05 / HC-06 VCC -> Shield SERVO2 +
  HC-05 / HC-06 GND -> Shield SERVO2 -

  Servo bağlantısı:
  Servo kahverengi / siyah kablo -> Shield SERVO1 -
  Servo kırmızı kablo            -> Shield SERVO1 +
  Servo turuncu / sarı kablo     -> Shield SERVO1 S

  Buzzer bağlantısı:
  Buzzer + -> A5
  Buzzer - -> GND

  Komutlar:
  F = İleri
  B = Geri
  L = Sol
  R = Sağ
  S = Dur
  T = Servo taramayı başlat / duraklat
  H = Korna başlat
  h = Korna durdur
*/

SoftwareSerial BT(A0, A1);  // RX, TX

AF_DCMotor motor1(1);  // M1
AF_DCMotor motor2(2);  // M2
AF_DCMotor motor3(3);  // M3
AF_DCMotor motor4(4);  // M4

Servo servoMotor;

// Motor ayarı
int hiz = 170;

// Servo ayarları
int servoPin = 10;       // SERVO1 sinyal pini
int minAci = 20;
int maxAci = 160;
int servoAci = 90;
int servoYon = 1;
bool taramaAktif = false;

unsigned long oncekiServoZamani = 0;
int servoBekleme = 15;

// Buzzer ayarı
int buzzerPin = A5;
int kornaFrekansi = 2000;  // Hz

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  servoMotor.attach(servoPin);
  servoMotor.write(servoAci);

  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);

  motorlariAyarla();
  dur();

  Serial.println("4WD Bluetooth robot hazir.");
  Serial.println("Komutlar:");
  Serial.println("F = Ileri");
  Serial.println("B = Geri");
  Serial.println("L = Sol");
  Serial.println("R = Sag");
  Serial.println("S = Dur");
  Serial.println("T = Servo tarama baslat / duraklat");
  Serial.println("H = Korna baslat");
  Serial.println("h = Korna durdur");
  Serial.println("------------------------------------");
}

void loop() {
  bluetoothKomutOku();
  servoTaramayiCalistir();
}

void bluetoothKomutOku() {
  if (BT.available()) {
    char komut = BT.read();

    // Boşluk ve satır sonu karakterlerini yok say
    if (komut == '\n' || komut == '\r' || komut == ' ') {
      return;
    }

    /*
      ÖNEMLİ:
      h komutu kornayı durdurmak için küçük harf olarak kullanılıyor.
      Bu yüzden h karakterini büyük harfe çevirmeden önce kontrol ediyoruz.
    */
    if (komut == 'h') {
      kornaKapat();
      Serial.println("Korna durdu.");
      return;
    }

    // Diğer küçük harfleri büyük harfe çevir
    if (komut >= 'a' && komut <= 'z') {
      komut = komut - 32;
    }

    Serial.print("Gelen komut: ");
    Serial.println(komut);

    if (komut == 'F') {
      ileri();
      Serial.println("Hareket: ILERI");
    }
    else if (komut == 'B') {
      geri();
      Serial.println("Hareket: GERI");
    }
    else if (komut == 'L') {
      solaDon();
      Serial.println("Hareket: SOLA DON");
    }
    else if (komut == 'R') {
      sagaDon();
      Serial.println("Hareket: SAGA DON");
    }
    else if (komut == 'S') {
      dur();
      Serial.println("Hareket: DUR");
    }
    else if (komut == 'T') {
      taramaAktif = !taramaAktif;

      if (taramaAktif) {
        Serial.println("Servo tarama basladi / kaldigi yerden devam ediyor.");
      } else {
        Serial.println("Servo tarama duraklatildi. Servo bulundugu acida bekliyor.");
      }
    }
    else if (komut == 'H') {
      kornaAc();
      Serial.println("Korna caliyor.");
    }
    else {
      Serial.println("Bilinmeyen komut. F, B, L, R, S, T, H veya h kullaniniz.");
    }
  }
}

void servoTaramayiCalistir() {
  if (taramaAktif == false) {
    return;
  }

  unsigned long simdikiZaman = millis();

  if (simdikiZaman - oncekiServoZamani >= servoBekleme) {
    oncekiServoZamani = simdikiZaman;

    servoAci = servoAci + servoYon;
    servoMotor.write(servoAci);

    if (servoAci >= maxAci) {
      servoYon = -1;
    }

    if (servoAci <= minAci) {
      servoYon = 1;
    }
  }
}

void kornaAc() {
  tone(buzzerPin, kornaFrekansi);
}

void kornaKapat() {
  noTone(buzzerPin);
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

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void solaDon() {
  motorlariAyarla();

  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void dur() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

/*
  4WD Bluetooth Robot Araba
  Arduino Uno + L293D Motor Shield + HC-05 / HC-06 + Servo Motor

  Bluetooth bağlantısı:
  HC-05 / HC-06 TX  -> Shield A0
  HC-05 / HC-06 RX  -> Shield A1
  HC-05 / HC-06 VCC -> Shield SERVO2 +
  HC-05 / HC-06 GND -> Shield SERVO2 -

  Servo bağlantısı:
  Servo kahverengi / siyah kablo -> Shield SERVO1 -
  Servo kırmızı kablo            -> Shield SERVO1 +
  Servo turuncu / sarı kablo     -> Shield SERVO1 S

  L293D Motor Shield üzerinde:
  SERVO1 sinyal pini genellikle Arduino D10 pinine bağlıdır.

  Komutlar:
  F = İleri
  B = Geri
  L = Sol
  R = Sağ
  S = Dur
  T = Servo taramayı başlat / duraklat
*/

// Bluetooth için yazılımsal seri haberleşme
SoftwareSerial BT(A0, A1);  // RX, TX

// Motor tanımlamaları
AF_DCMotor motor1(1);  // M1
AF_DCMotor motor2(2);  // M2
AF_DCMotor motor3(3);  // M3
AF_DCMotor motor4(4);  // M4

// Servo tanımlaması
Servo servoMotor;

// Motor hızı
int hiz = 170;  // 0 - 255 arası

// Servo ayarları
int servoPin = 10;       // SERVO1 sinyal pini
int minAci = 20;         // Servo minimum açı
int maxAci = 160;        // Servo maksimum açı
int servoAci = 90;       // Servo başlangıç açısı
int servoYon = 1;        // 1: artan yön, -1: azalan yön

bool taramaAktif = false;

// millis() ile servo zaman kontrolü
unsigned long oncekiServoZamani = 0;
int servoBekleme = 15;   // Değer küçülürse servo daha hızlı tarar

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  // Servo başlatılır
  servoMotor.attach(servoPin);
  servoMotor.write(servoAci);

  // Motor hızları ayarlanır
  motorlariAyarla();

  // Başlangıçta motorlar durur
  dur();

  Serial.println("4WD Bluetooth robot hazir.");
  Serial.println("Komutlar:");
  Serial.println("F = Ileri");
  Serial.println("B = Geri");
  Serial.println("L = Sol");
  Serial.println("R = Sag");
  Serial.println("S = Dur");
  Serial.println("T = Servo taramayi baslat / duraklat");
  Serial.println("------------------------------------");
}

void loop() {
  bluetoothKomutOku();
  servoTaramayiCalistir();
}

void bluetoothKomutOku() {
  if (BT.available()) {
    char komut = BT.read();

    // Gereksiz karakterleri yok say
    if (komut == '\n' || komut == '\r' || komut == ' ') {
      return;
    }

    // Küçük harf gelirse büyük harfe çevir
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
    else {
      Serial.println("Bilinmeyen komut. F, B, L, R, S veya T kullaniniz.");
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

  // Sol taraf ileri, sağ taraf geri
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void solaDon() {
  motorlariAyarla();

  // Sol taraf geri, sağ taraf ileri
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
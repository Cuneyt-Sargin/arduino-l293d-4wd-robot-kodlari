#include <AFMotor.h>

/*
  4WD Robot Araba - Seri Monitör ile Kontrol

  Bu kodda robot araba Bluetooth ile değil,
  Arduino IDE içindeki Seri Monitör üzerinden kontrol edilir.

  Seri Monitör'e şu karakterler yazılır:

  F = İleri
  B = Geri
  L = Sola dön
  R = Sağa dön
  S = Dur

  Motor Shield bağlantısı:
  M1 = Ön Sol Motor
  M2 = Arka Sol Motor
  M3 = Ön Sağ Motor
  M4 = Arka Sağ Motor
*/

AF_DCMotor motor1(1);  // M1
AF_DCMotor motor2(2);  // M2
AF_DCMotor motor3(3);  // M3
AF_DCMotor motor4(4);  // M4

int hiz = 170;  // Motor hızı: 0 - 255 arası

void setup() {
  Serial.begin(9600);

  motorlariAyarla();
  dur();

  Serial.println("Seri Monitor ile 4WD robot kontrolu hazir.");
  Serial.println("Komutlar:");
  Serial.println("F = Ileri");
  Serial.println("B = Geri");
  Serial.println("L = Sol");
  Serial.println("R = Sag");
  Serial.println("S = Dur");
  Serial.println("-----------------------------");
}

void loop() {
  if (Serial.available()) {
    char komut = Serial.read();

    // Enter, bosluk veya satir sonu karakterlerini yok say
    if (komut == '\n' || komut == '\r' || komut == ' ') {
      return;
    }

    // Kucuk harf gelirse buyuk harfe cevir
    if (komut >= 'a' && komut <= 'z') {
      komut = komut - 32;
    }

    Serial.print("Gelen komut: ");
    Serial.println(komut);

    if (komut == 'F') {
      Serial.println("Robot ileri gidiyor.");
      ileri();
    }
    else if (komut == 'B') {
      Serial.println("Robot geri gidiyor.");
      geri();
    }
    else if (komut == 'L') {
      Serial.println("Robot sola donuyor.");
      solaDon();
    }
    else if (komut == 'R') {
      Serial.println("Robot saga donuyor.");
      sagaDon();
    }
    else if (komut == 'S') {
      Serial.println("Robot durdu.");
      dur();
    }
    else {
      Serial.println("Hatali komut. F, B, L, R veya S kullaniniz.");
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

  // Sol taraf ileri, sag taraf geri
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void solaDon() {
  motorlariAyarla();

  // Sol taraf geri, sag taraf ileri
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
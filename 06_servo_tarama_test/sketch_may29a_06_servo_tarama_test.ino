#include <Servo.h>

/*
  Servo Tarama Testi
  Bağlantı:
  Servo kahverengi/siyah kablo -> SERVO1 -
  Servo kırmızı kablo          -> SERVO1 +
  Servo turuncu/sarı kablo     -> SERVO1 S

  L293D Motor Shield üzerinde SERVO1 genellikle Arduino D10 pinine bağlıdır.
*/

Servo servoMotor;

int servoPin = 10;   // Motor Shield SERVO1 sinyal pini
int minAci = 20;     // En sol / başlangıç açısı
int maxAci = 160;    // En sağ / bitiş açısı
int bekleme = 15;    // Servo hareket hızı

void setup() {
  servoMotor.attach(servoPin);

  // Servo başlangıç konumu
  servoMotor.write(90);
  delay(1000);
}

void loop() {
  // 20 dereceden 160 dereceye git
  for (int aci = minAci; aci <= maxAci; aci++) {
    servoMotor.write(aci);
    delay(bekleme);
  }

  delay(300);

  // 160 dereceden 20 dereceye geri dön
  for (int aci = maxAci; aci >= minAci; aci--) {
    servoMotor.write(aci);
    delay(bekleme);
  }

  delay(300);
}
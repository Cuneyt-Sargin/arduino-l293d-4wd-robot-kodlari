#include <AFMotor.h>

AF_DCMotor motor1(1);  // M1
AF_DCMotor motor2(2);  // M2
AF_DCMotor motor3(3);  // M3
AF_DCMotor motor4(4);  // M4

int hiz = 150;  // 0-255 arası

void setup() {
  Serial.begin(9600);

  motor1.setSpeed(hiz);
  motor2.setSpeed(hiz);
  motor3.setSpeed(hiz);
  motor4.setSpeed(hiz);

  // Başlangıçta hepsini durdur
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  delay(1000);

  Serial.println("4 motor ileri gidiyor");

  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  delay(3000);

  Serial.println("Motorlar durdu");

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {
  // Boş. Sadece bir kere çalışacak.
}
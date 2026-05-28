//#define yanındaki sayıyı 1,2,3,4 olarak sırayla dene yönü ters ise shild den kablo yönünü değiştir.
#include <AFMotor.h>

AF_DCMotor motor1(1);  // M1
AF_DCMotor motor2(2);  // M2
AF_DCMotor motor3(3);  // M3
AF_DCMotor motor4(4);  // M4

// BURAYI DEĞİŞTİR:
// 1 yazarsan M1 çalışır
// 2 yazarsan M2 çalışır
// 3 yazarsan M3 çalışır
// 4 yazarsan M4 çalışır
#define TEST_MOTOR 2

int hiz = 150;   // 0 - 255 arası

void setup() {
  Serial.begin(9600);

  motor1.setSpeed(hiz);
  motor2.setSpeed(hiz);
  motor3.setSpeed(hiz);
  motor4.setSpeed(hiz);

  // Başlangıçta tüm motorları durdur
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  delay(1000);

  Serial.print("Test edilen motor: M");
  Serial.println(TEST_MOTOR);

#if TEST_MOTOR == 1
  motor1.run(FORWARD);
  delay(3000);
  motor1.run(RELEASE);

#elif TEST_MOTOR == 2
  motor2.run(FORWARD);
  delay(3000);
  motor2.run(RELEASE);

#elif TEST_MOTOR == 3
  motor3.run(FORWARD);
  delay(3000);
  motor3.run(RELEASE);

#elif TEST_MOTOR == 4
  motor4.run(FORWARD);
  delay(3000);
  motor4.run(RELEASE);

#endif

  Serial.println("Test bitti.");
}

void loop() {
  // Boş. Motor sadece bir kere çalışır.
}
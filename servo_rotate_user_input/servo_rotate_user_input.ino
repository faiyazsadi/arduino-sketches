#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(12);
}

void loop() {
  int pos = 0;
  myservo.write(pos);
  delay(1000);
  Serial.println("Enter Rotate Angle: ");
  while(Serial.available() == 0) {
  }
  pos = Serial.parseInt();
  myservo.write(pos);
  delay(1000);
  Serial.println("Entered Angle: ");
  delay(1000);
  Serial.println(myservo.read());
}

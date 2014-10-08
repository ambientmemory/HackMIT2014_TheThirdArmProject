#include <Servo.h>
Servo.finger1;
Servo.finger2;
Servo.finger3;
Servo.finger4;
Servo.finger5;
Servo.wrist2;
Servo.wrist;
Servo.arm;
Servo.arm2;

void setup() {
  finger1.attach(2);
  finger2.attach(3);
  finger3.attach(4);
  finger4.attach(5);
  finger5.attach(6);
  wrist2.attach(7);
  arm.attach(8);
  arm2.attach(9);
  Serial.begin(9600);
}

void loop() {
if (Serial.available()>0)
{
  int yawl = Serial.read();
  int pick = Serial.read();
  int row = Serial.read();
  int gesture = Serial.read();
  wrist.write(yawl),wrist2.write(pick), arm.write(row),arm2.write(180-row);
}

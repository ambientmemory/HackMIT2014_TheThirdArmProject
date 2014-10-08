#include <Servo.h>

Servo finger1;
Servo finger2;
Servo finger3;
Servo finger4;
Servo finger5;
Servo wrist2;
Servo wrist;
Servo arm;
Servo arm2;

Servo thumbFinger;
Servo indexFinger;
Servo middleFinger;
Servo ringFinger;
Servo pinkyFinger;

int restDegree= 40;
int contractDegree = 0;
int flexDegree = 180;

int thumbValue;
int indexValue;
int middleValue;
int ringValue;
int pinkyValue;

void setup() {
  finger1.attach(2);
  finger2.attach(3);
  finger3.attach(4);
  finger4.attach(5);
  finger5.attach(6);
  wrist2.attach(7);
  arm.attach(8);
  arm2.attach(9);
  
  thumbFinger.attach(2);
  indexFinger.attach(3);
  middleFinger.attach(4);
  ringFinger.attach(5);
  pinkyFinger.attach(6);
  Serial.begin(9600);
}

void loop() {
if (Serial.available()>0)
{
  int yaw = Serial.read();
  int pitch = Serial.read();
  int roll = Serial.read();
  int gesture = Serial.read();
  if (gesture==1){
    set_hand_rock();
  }
    else if (gesture == 4){
      set_hand_paper();
    }
    else if (gesture == 6){
      set_hand_scissors();
    }
  wrist.write(yaw),wrist2.write(pitch), arm.write(roll),arm2.write(180-roll);
  update_hand();
}
}

void update_hand(){
  indexFinger.write(indexValue);
  middleFinger.write(middleValue);
  ringFinger.write(ringValue);
  pinkyFinger.write(pinkyValue);
  delay(150);
  thumbFinger.write(thumbValue);
}

void set_hand_paper(){
  thumbValue=flexDegree; 
  indexValue=flexDegree;
  middleValue=flexDegree;
  ringValue=flexDegree;
  pinkyValue=flexDegree;
}

void set_hand_rock(){
  thumbValue=contractDegree;
  indexValue=contractDegree;
  middleValue=contractDegree;
  ringValue=contractDegree;
  pinkyValue=contractDegree;
}

void set_hand_scissors(){
  thumbValue=contractDegree;
  indexValue=flexDegree;
  middleValue=flexDegree;
  ringValue=contractDegree;
  pinkyValue=contractDegree;
}

void set_hand_rest(){
  thumbValue=restDegree;
  indexValue=restDegree;
  middleValue=restDegree;
  ringValue=restDegree;
  pinkyValue=restDegree;
}

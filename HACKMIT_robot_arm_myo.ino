#include <Servo.h>

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
  thumbFinger.attach(2);
  indexFinger.attach(3);
  middleFinger.attach(4);
  ringFinger.attach(5);
  pinkyFinger.attach(6);
}

void loop() {
  set_hand_paper();
  update_hand();
//  delay(1500);
//  set_hand_rock();
//  update_hand();
//  delay(1500);
//  set_hand_scissors();
//  update_hand();
//  delay(1500);
//  set_hand_rest();
//  update_hand();
//  delay(1500);
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

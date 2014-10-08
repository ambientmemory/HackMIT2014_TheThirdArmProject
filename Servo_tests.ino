#include <Servo.h>


int val ,val2,val3;
int pin =A5;
int pin2 =A0;
int pin3=A3;

Servo s,s2,s3,s4;
void setup()
{
Serial.begin(9600);
s.attach(6);
s2.attach(7);
s3.attach(5);
s4.attach(4);


}

void loop()
{
  val = analogRead(pin);
  val2 = analogRead(pin2);
  val3 = analogRead(pin3);
  val=map(val,0,1023,0,179);
  val2=map(val2,168,400, 0,179);
  val3=map(val3,0,1023,0,179);
  
  Serial.print(val);
  Serial.print(" : " );
  Serial.print(val2);
  Serial.print(" : " );
  Serial.println(val3);
  
 s2.write(val2),s3.write(val2);
  delay(15);
}





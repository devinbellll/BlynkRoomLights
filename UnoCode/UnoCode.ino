#include <Servo.h>
Servo lightswitch;
int servo_pin = 3;
int on = 700;
int idle = 1300;
int off = 2300;

unsigned int sw_pos = idle;

void setup() {
  Serial.begin(9600);
  pinMode(servo_pin, OUTPUT);
  lightswitch.attach(servo_pin);
  
  
}

void loop() {
  if (Serial.available())
  {
  sw_pos = Serial.parseInt();
  }
switch(sw_pos) 
{

  
  case 0:
  lightswitch.writeMicroseconds(off);
  delay(500);
  lightswitch.writeMicroseconds(idle);
  break;

  case 1:
  lightswitch.writeMicroseconds(on);
  delay(500);
  lightswitch.writeMicroseconds(idle);
  break;
  
  case 2:
  break;
}

sw_pos = 2;
}

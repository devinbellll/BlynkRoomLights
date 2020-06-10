#include <Servo.h>
Servo lightswitch;
int servo_pin = 3;
unsigned int sw_pos = idle;

void dataHandler(String command, String data);
void manual(void)



String mode = "";
String manualData = "";


void setup() 
{
  pinMode(servo_pin, OUTPUT);
  lightswitch.attach(servo_pin);
  Serial.begin(9600);
  
  UCSR0B |= (1 << RXCIE0);
  sei();
}

void loop() 
{
  dataHandler(mode);
}


void ISRwhatever(void)
{

}

void dataHandler(String mode)
{

  switch (mode)
  {
    case "off" :
      break;
      
    case "normal" :
      break;
      
    case "party" :
      break;
      
    case "theater" :
      break;
      
    case "sex" :
      break;
      
    case "manual" :
      break;
    default :
      break;
  }

}

void OnOff(String sw)
{
  unsigned int on = 700;
  unsigned int idle = 1300;
  unsigned int off = 2300;
  if (sw == "off")
  {
    lightswitch.writeMicroseconds(off);
    delay(500);
    lightswitch.writeMicroseconds(idle);
    setMode("off");
  }
  else if (sw == "on")
  {
    lightswitch.writeMicroseconds(off);
    delay(500);
    lightswitch.writeMicroseconds(idle);
    setMode("normal");
  }
}


void off(void)
{
  LEDs.something
  while(mode == "off") {}
}

void normal(void)
{
  LEDs.something
  while(mode == "normal") {}
}

void party(void)
{
  while(mode == "party")
  {
    
  }
}

void theater(void)
{
  LEDs.something
  while(mode == "theater")
  {
    
  }
}

void sex(void)
{
  while(mode == "sex")
  {
    
  }
}

void manual(void)
{
  while(mode == "manual")
  {
    
  }
}

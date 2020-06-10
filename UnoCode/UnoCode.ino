
#include <avr/io.h>
#include <avr/interrupt.h>

#define USART_BAUDRATE 9600
#define MYUBRR (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <Servo.h>

Servo lightswitch;
int servo_pin = 3;
unsigned int on = 700;
unsigned int idle = 1300;
unsigned int off = 2300;

int RedPin = 10; //Arduino driving pin for Red
int GreenPin = 11; //Arduino driving pin for Green
int BluePin = 9; //Arduino driving pin for Blue

// Colour setter
void setColour(int red, int green, int blue);

// Serial commander handler
void dataHandler(String command);

// Mode functions
void manual(void);
void sex(void);
void theater(void);
void party(void);
void off(void);
void normal(void);

// Lightswitch control functions
void LightsOff(void);
void LightsOn(void);

// Global variables
String mode = "";
String rxstring = "";
bool RECEIVEDLINE = false;

void setup()
{
  pinMode(RedPin, OUTPUT); //Init Arduino driving pins
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  pinMode(servo_pin, OUTPUT);
  lightswitch.attach(servo_pin);
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes

  UBRR0H = (MYUBRR >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
  UBRR0L = MYUBRR; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

  UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve Complete interrupt (USART_RXC)

  sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

void loop()
{
  if (RECEIVEDLINE)
  {
    String com = rxstring;
    RECEIVEDLINE = false;
    rxstring = "";
    dataHandler(com);
  }
}


//intrerupt on receive
ISR (USART_RX_vect)
{
  char ReceivedByte;
  ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"

  if (ReceivedByte == '\n')
  {
    RECEIVEDLINE = true;
    rxstring += ReceivedByte;
  }
  else
  {
    rxstring += ReceivedByte;
  }
  UDR0 = ReceivedByte; // Echo back the received byte back to the computer
  //digitalWrite(13, HIGH);

}

void dataHandler(String com)
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


void LightsOn(void)
{
  lightswitch.writeMicroseconds(on);
  delay(500);
  lightswitch.writeMicroseconds(idle);
}

void LightsOff(void)
{
  lightswitch.writeMicroseconds(off);
  delay(500);
  lightswitch.writeMicroseconds(idle);
}

void off(void)
{
  LightsOff();
  LEDs.something
  while (mode == "off") {}
}

void normal(void)
{
  LightsOn();
  LEDs.something
  while (mode == "normal") {}
}

void party(void)
{
  LightsOff();
  while (mode == "party")
  {
    for (int i = 0; i < 255; i++) //Changing Red brightness
    {
      setColor(i, 0, 0);
      delay (5);
    }
    for (int i = 0; i < 255; i++) //Changing Green brightness
    {
      setColor(0, i, 0);
      delay (5);
    }
    for (int i = 0; i < 255; i++) //Changing Blue brightness
    {
      setColor(0, 0, i);
      delay (5);
    }
    for (int i = 0; i < 255; i++)
    {
      setColor(i, 0, 255 - i);
      delay (5);
    }
    for (int i = 0; i < 255; i++)
    {
      setColor(255 - i, i, 0);
      delay (5);
    }
    for (int i = 0; i < 255; i++)
    {
      setColor(0, 255 - i, i);
      delay (5);
    }
  }
}

void theater(void)
{
  LightsOff();
  LEDs.something
  while (mode == "theater")
  {

  }
}

void sex(void)
{
  LightsOff();
  while (mode == "sex")
  {

  }
}

void manual(void)
{
  LightsOff();
  while (mode == "manual")
  {

  }
}


void setColour(int red, int green, int blue)
{
  analogWrite(RedPin, red);
  analogWrite(GreenPin, green);
  analogWrite(BluePin, blue);
}

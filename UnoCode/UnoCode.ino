//#include <Servo.h>


//#include <avr/io.h>
//#include <avr/interrupt.h>

#define USART_BAUDRATE 9600
#define MYUBRR (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


//int servo_pin = 3;
//unsigned int swon = 700;
//unsigned int idle = 1300;
//unsigned int swoff = 2300;
//bool LIGHTSON = false;
//
//Servo lightswitch;

int RedPin = 10; //Arduino driving pin for Red
int GreenPin = 11; //Arduino driving pin for Green
int BluePin = 9; //Arduino driving pin for Blue

// Colour setter
void setColour(int red, int green, int blue);

// Serial commander handler
void dataHandler(String command);

// Mode functions
void sex(void);
void theater(void);
void party(void);
void off(void);
void normal(void);

// Lightswitch control functions
void LightsOff(void);
void LightsOn(void);

// Global variables
volatile String mode = "";
String rxstring = "";
bool RECEIVEDLINE = false;


void setup()
{
  pinMode(RedPin, OUTPUT); //Init Arduino driving pins
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  
//  pinMode(servo_pin, OUTPUT);
//  lightswitch.attach(servo_pin);

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes

  UBRR0H = (MYUBRR >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
  UBRR0L = MYUBRR; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

  UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve Complete interrupt (USART_RXC)

  sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

void loop()
{
  if (mode == "off")
  {
    off();
  }
  else if (mode == "normal")
  {
    normal();
  }
  else if (mode == "party")
  {

    party();
  }

  else if (mode == "theater")
  {
    theater();
  }
  else
  {
    sex();
  }


}


//intrerupt on receive
ISR (USART_RX_vect)
{
  char ReceivedByte;
  ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"

  if (ReceivedByte == ' ')
  {
    RECEIVEDLINE = true;
  }
  else
  {
    rxstring += ReceivedByte;
  }
  UDR0 = ReceivedByte; // Echo back the received byte back to the computer
  //digitalWrite(13, HIGH);

  if (RECEIVEDLINE)
  {
    RECEIVEDLINE = false;
    mode = rxstring;
    rxstring = "";
  }

}





void setColour(int red, int green, int blue)
{
  analogWrite(RedPin, red);
  analogWrite(GreenPin, green);
  analogWrite(BluePin, blue);
}


//void LightsOn(void)
//{
////  lightswitch.attach(servo_pin);
//  lightswitch.writeMicroseconds(swon);
//  delay(500);
//  lightswitch.writeMicroseconds(idle);
////  delay(50);
////  lightswitch.detach();
//}
//
//void LightsOff(void)
//{
////  lightswitch.attach(servo_pin);
//  lightswitch.writeMicroseconds(swoff);
//  delay(500);
//  lightswitch.writeMicroseconds(idle);
////  delay(50);
////  lightswitch.detach();
//}

void off(void)
{
//  if (LIGHTSON)
//  {
//    LightsOff();
//  }
//  LIGHTSON = false;
  setColour(0, 0, 0);
  
}

void normal(void)
{
//  if (!LIGHTSON)
//  {
//    LightsOn();
//  }
//  LIGHTSON = true;
  setColour(255, 125, 45);
}

void party(void)
{
//  if (LIGHTSON)
//  {
//    LightsOff();
//  }
//  LIGHTSON = false;
  while (mode == "party")
  {
    for (int i = 0; i < 255; i++)
    {
      setColour(i, 0, 255 - i);
      delay (1);
    }
    for (int i = 0; i < 255; i++)
    {
      setColour(255 - i, i, 0);
      delay (1);
    }
    for (int i = 0; i < 255; i++)
    {
      setColour(0, 255 - i, i);
      delay (1);
    }
  }
}

void theater(void)
{
  //  LightsOff();
  while (mode == "theater")
  {

  }
}

void sex(void)
{
  //  LightsOff();
  while (mode == "sex")
  {

  }
}


#include <avr/io.h>
#include <avr/interrupt.h>

#define USART_BAUDRATE 9600
#define MYUBRR (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void setup() {

  pinMode(10, OUTPUT);
  analogWrite(10, 255);
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes

  UBRR0H = (MYUBRR >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
  UBRR0L = MYUBRR; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register



  UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve Complete interrupt (USART_RXC)

  sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed

}


String rxstring = "";
bool RECEIVEDLINE = false;

//intrerupt on receive
ISR (USART_RX_vect)
{
  char ReceivedByte;
  ReceivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"

  if (ReceivedByte == '\n')
  {
    RECEIVEDLINE = true;
  }
  else 
  {
    rxstring += ReceivedByte;
  }
  UDR0 = ReceivedByte; // Echo back the received byte back to the computer
  //digitalWrite(13, HIGH);

}

void loop() {
  if(RECEIVEDLINE) 
  {
    RECEIVEDLINE = false;
    analogWrite(10, 0);

    if(rxstring == "test")
    {
      analogWrite(10, 255);
    }
    rxstring = "";
  }

  
  
}

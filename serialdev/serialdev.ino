String mode = "";
String manualData = "";


void setup() 
{
  Serial.begin(9600);
  
  UCSR0B |= (1 << RXCIE0);
  sei();
}

void loop() 
{
}


void ISRwhatever(void)
{

}

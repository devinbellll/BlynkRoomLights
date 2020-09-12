#define BLYNK_PRINT Serial
#include <Servo.h>


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "qbEUab-D9UwxWm_pv_SeTABxrK62HnEi";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "StroudHome";
char pass[] = "Cloud2017";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ca.pool.ntp.org", -14400, 60000);
WidgetTerminal terminal(V5);

unsigned long alarm_time;
unsigned long current_time;
int master; 
String mode = "";
String prevMode = "";
int AlarmOnOff;
int alarmHours;
int alarmMin;

///// Lightswitch and LED Section /////

// Mode functions
void romantic(void);
void theater(void);
void party(void);
void off(void);
void normal(void);
void setColour(int red, int green, int blue);

int RedPin = D5; //Arduino driving pin for Red, Pin 10 on LED board
int GreenPin = D6; //Arduino driving pin for Green, Pin 11 on LED board
int BluePin = D8; //Arduino driving pin for Blue, Pin 9 on LED board

int servo_pin = D2;
unsigned int swon = 700;
unsigned int idle = 1300;
unsigned int swoff = 2300;
bool LIGHTSON = false;

Servo lightswitch;

void LightsOn(void)
{
  lightswitch.writeMicroseconds(swon);
  delay(500);
  lightswitch.writeMicroseconds(idle);
  delay(50);
}

void LightsOff(void)
{
  lightswitch.writeMicroseconds(swoff);
  delay(500);
  lightswitch.writeMicroseconds(idle);
  delay(50);
}


void setColour(int red, int green, int blue)
{
  analogWrite(RedPin, red);
  analogWrite(GreenPin, green);
  analogWrite(BluePin, blue);
}

void callMode(void)
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
    romantic();
  }
}
//Master On/Off switch

BLYNK_WRITE(V0)
{
  terminal.clear();
  
  master = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  terminal.print("Master: ");
  if (master == 1) {
    if(mode == "off")
    {
      mode = prevMode;
    }
    callMode();
    terminal.println("On");
  }
  if (master == 2) {
    prevMode = mode;
    mode = "off";
    callMode();
    terminal.println("Off");
  } 
  terminal.println();
  terminal.flush();
}

//Alarm On/Off Switch
BLYNK_WRITE(V1)
{
  terminal.clear();
  
  AlarmOnOff = param.asInt(); // assigning incoming value from pin V1 to a variable


  terminal.print("Alarm: ");
  if (AlarmOnOff == 1) {
    terminal.println("On");
    terminal.println(String("Alarm set for: ") +
                 alarmHours + ":" +
                 alarmMin);
  }
  if (AlarmOnOff == 2) {
    terminal.println("Off");
  }
  
  
  terminal.println();
  terminal.flush();
}

// Alarm time setter
BLYNK_WRITE(V2) {
  terminal.clear();
  TimeInputParam t(param);

  // Process start time

  if (t.hasStartTime())
  {
    alarmHours = t.getStartHour();
    alarmMin = t.getStartMinute();

    
    terminal.println(String("Alarm Set: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute());
                   
    alarm_time = (t.getStartHour())*100 + t.getStartMinute();
  }
  else
  {
    // Do nothing
  }

  terminal.println();
  terminal.flush();  
}

// Mode setter switch
BLYNK_WRITE(V3)
{
  int modeSet;
  terminal.clear();
  
  modeSet = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  terminal.print("Mode set to: ");
  if (modeSet == 1) {
    mode = "normal";
    terminal.println("Normal");
  }
  else if (modeSet == 2) {
    mode = "party";
    terminal.println("Party");
  }
  else if (modeSet == 3) {
    mode = "theater";
    terminal.println("Theater");
  }
  else {
    mode = "romantic";
    terminal.println("Romantic");
  }

  if (master == 1) {
    callMode();
  }
  
  
  terminal.println();
  terminal.flush();
}

void off(void)
{
  if (LIGHTSON)
  {
    LightsOff();
  }
  LIGHTSON = false;
  setColour(0, 0, 0);
  
}

void normal(void)
{
  Serial.println("Set to Normal");
  if (!LIGHTSON)
  {
    LightsOn();
  }
  LIGHTSON = true;
  setColour(255, 125, 45);
}

void party(void)
{
  Serial.println("Set to Party");
  if (LIGHTSON)
  {
    LightsOff();
  }
  LIGHTSON = false;
}

void theater(void)
{
  Serial.println("Set to Theater");
  if (LIGHTSON)
  {
    LightsOff();
  }
  LIGHTSON = false;
}

void romantic(void)
{
  Serial.println("Set to Romantic");
  if (LIGHTSON)
  {
    LightsOff();
  }
  LIGHTSON = false;
}



void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  timeClient.begin();

  pinMode(RedPin, OUTPUT); //Init Arduino driving pins
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(servo_pin, OUTPUT);
  lightswitch.attach(servo_pin);
}

void loop()
{
  Blynk.run();
  
  timeClient.update();
  
  current_time = (timeClient.getHours())*100 + timeClient.getMinutes();
  if ((current_time == alarm_time) && (AlarmOnOff == 1))
  {
    mode = "normal";
    callMode();
    AlarmOnOff = 2;
    Serial.println("ALARM");
  }

  if (mode == "party" && master == 1)
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
  else if (mode == "romantic" && master == 1)
  {
    for (int i = 0; i <= 185; i++)
    {
      setColour(255, 0, 185 - i);
      delay(20);
    }
    for (int i = 0; i <= 185; i++)
    {
      setColour(255, 0, i);
      delay(20);
    }
  }
  else if (mode == "theater" && master == 1)
  {
    for (int i = 0; i <= 185; i++)
    {
      setColour(0, 185 - i, 255);
      delay(30);
    }
    for (int i = 0; i <= 185; i++)
    {
      setColour(0, i, 255);
      delay(30);
    }
  }
}

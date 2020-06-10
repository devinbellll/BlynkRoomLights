#define BLYNK_PRINT Serial


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
String mode;
int AlarmOnOff;
int alarmHours;
int alarmMin;



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
    
    Serial.print(mode + " 0");
    terminal.println("On");
  }
  if (master == 2) {
    
    Serial.print("off 0");
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
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
//  Serial.print("Alarm On/Off value is: ");
//  if (AlarmOnOff == 1) {
//    Serial.println("Alarm On");
//    Serial.println(String("Alarm Time: ") + alarm_time);
//    Serial.println(String("Current Time: ") + current_time);
//  }
//  if (AlarmOnOff == 2) {
//    Serial.println("Alarm Off");
//  }

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
    //Serial.println(String("Alarm Time Set: ") + alarm_time);
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
  else if (modeSet == 4) {
    mode = "sex";
    terminal.println("Sex");
  }
  else {
    mode = "manual";
    terminal.println("Manual");
  }

  if (master == 1) {
    Serial.print(mode + " 0");
  }
  
  
  terminal.println();
  terminal.flush();
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

}

void loop()
{
  Blynk.run();
  
  timeClient.update();
  
  current_time = (timeClient.getHours())*100 + timeClient.getMinutes();
  if ((current_time == alarm_time) && (AlarmOnOff == 1))
  {
    Serial.print("normal 0");
    AlarmOnOff = 2;
  }
}

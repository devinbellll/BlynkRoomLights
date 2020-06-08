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
int OnOff;
int AlarmOnOff;
int alarmHours;
int alarmMin;


//Master On/Off switch

BLYNK_WRITE(V0)
{
  terminal.clear();
  
  OnOff = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("Master On/Off value is: ");
  if (OnOff == 1) {
    Serial.println("On");
  }
  if (OnOff == 2) {
    Serial.println("Off");
  } 
  terminal.print("Master: ");
  if (OnOff == 1) {
    terminal.println("On");
  }
  if (OnOff == 2) {
    terminal.println("Off");
  } 
  terminal.println();
  terminal.flush();
  
  Serial.println();
}

//Alarm On/Off Switch
BLYNK_WRITE(V1)
{
  terminal.clear();
  
  AlarmOnOff = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("Alarm On/Off value is: ");
  if (AlarmOnOff == 1) {
    Serial.println("Alarm On");
    Serial.println(String("Alarm Time: ") + alarm_time);
    Serial.println(String("Current Time: ") + current_time);
  }
  if (AlarmOnOff == 2) {
    Serial.println("Alarm Off");
  }

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
  
  Serial.println();
}


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
    Serial.println(String("Alarm Time Set: ") + alarm_time);
  }
  else
  {
    // Do nothing
  }

  terminal.println();
  terminal.flush();
  Serial.println();
  
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
    Serial.println("ALARM ALARM ALARM");
  }
}


#include <avr/sleep.h>
#include <avr/power.h>
#include <DS3232RTC.h>
#include <Time.h>
#include <Wire.h>


int pin3 = 3;
int seconds = 0;

void pin3Interrupt(void)
{
  detachInterrupt(1);
  
}

void enterSleep(void)
{
  attachInterrupt(1, pin3Interrupt, LOW);
  delay(100);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
}


void setup()
{
  Serial.begin(9600);
  pinMode(pin3, INPUT_PULLUP);
  setSyncProvider(RTC.get);
  RTC.alarmInterrupt(ALARM_1, false);
  RTC.alarmInterrupt(ALARM_2, false);
  RTC.squareWave(SQWAVE_NONE);
  RTC.setAlarm(ALM1_MATCH_MINUTES, 0, 0,0, 0 ); //ALM1_MATCH_MINUTES for once an hour, ALM1_MATCH_SECONDS for once every minute
  RTC.alarmInterrupt(ALARM_1, true);
  Serial.println(String("System date = ") + day() + "/" + month() + "/" + year() + " " + hour() + ":" + minute() + ":" + second() + "\n");
  Serial.println("Initialisation complete.");
}

void loop()
{

    if ( RTC.alarm( ALARM_1 ) )
    {
      Serial.println("hello world");}
  delay(1000);
  seconds++;
  Serial.print("Awake for ");
  Serial.print(seconds, DEC);
  Serial.println(" second");

  if (seconds == 3)
  {
    Serial.println("Entering sleep");
    Serial.flush();
    seconds = 0;
    delay(200);
    enterSleep();
  }
    
}



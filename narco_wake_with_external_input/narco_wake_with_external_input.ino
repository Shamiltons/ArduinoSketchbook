// external wake with narco
#include <avr/sleep.h>

const int lepPin = 13;
const int inputPin = 2;

volatile boolean flag

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT_PULLUP);
  goTOSleep();
}

void loop()
{
  if (flag)
  {
    doSomthing();
    flag = false;
    goToSleep();
  }
}

void setFlag()
{
  flag = true;
}

void goToSleep()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(0, setFlag, LOW); // pin D2
  sleep_mode(); // sleep now
  // now sleep until LOW interrupt, then ...
  sleep_disable();
  detachInterrupt(0);
}

void doSomething()
{
  for (int i = 0; i < 20; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
    )
  }

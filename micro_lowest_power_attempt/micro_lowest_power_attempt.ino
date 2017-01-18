#include "LowPower.h"
#include <prescaler.h>
//#include <Narcoleptic.h>
#include <avr/power.h>
//#include <avr/sleep.h>

 
void setup() {
  // put your setup code here, to run once:
  setClockPrescaler(CLOCK_PRESCALER_16);
  //power_all_disable();

}

void loop() {
  // put your main code here, to run repeatedly:

   LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);


}

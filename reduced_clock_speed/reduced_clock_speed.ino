// sketch to reduce clock speed and reduce power consumption

#include <prescaler.h>
#include <Narcoleptic.h>
#include <avr/power.h>

void setup()
{
 
  setClockPrescaler(CLOCK_PRESCALER_1);
  power_all_disable();// bring power consumption down by 2-3 mA
    // power_adc_disable(); //analog inputs
  // power_spi_disable(); 
  // power_twi_disable(); // 12c
  // power_usart0_disable(); // uart serial
  // power_timer0_disable();
  // power_timer1_disable();
 //power_timer2_disable();
   
  
}

void loop()
{
  
}

//CLOCK_PRESCALER_1 / 16 MHz / 7.8mA / 20ma micro
//CLOCK_PRESCALER_2 / 8 Mhz / 5.4mA / 
//CLOCK_PRESCALER_4 / 4Mhz / 4.0mA
//CLOCK_PRESCALER_8 / 2Mhz / 3.2ma
//CLOCK_PRESCALER_16 / 1 / 2.6
//CLOCK_PRESCALER_32 / 500kHz/ 2.3
//CLOCK_PRESCALER_64 / 250 / 2.2
//CLOCK_PRESCALER_128 / 125 / 2.1
//CLOCK_PRESCALER_256 / 62.5kHz / 2.1 ma


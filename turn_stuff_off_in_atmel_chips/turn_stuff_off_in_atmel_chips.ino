// turning off features in an atmel chip to save power

#include <avr/power.h>

void setup()
{
  pinMode(13, OUTPUT);
   power_adc_disable(); //analog inputs
   power_spi_disable(); 
   power_twi_disable(); // 12c
   power_usart0_disable(); // uart serial
   power_timer0_disable();
   power_timer1_disable();
   power_timer2_disable();
   //power_all_disable();// bring power consumption down by 2-3 mA
}

void loop()
{
}



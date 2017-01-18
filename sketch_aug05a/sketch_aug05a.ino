// RN2483_temperature.ino - Simple LoRaWAN temperature sensor using Microchip RN2483 module
#include "SoftwareSerial.h"
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "Timer.h"
#include <Vcc.h>
#include <util/atomic.h>
#include <Wire.h>
#include "RTClib.h"

SoftwareSerial lora(10, 11); // RX, TX

void sendCmd( char *cmd) 
{
  Serial.write( cmd );
  Serial.write("\n");
  lora.write(cmd);
  lora.write("\r\n");
  while (!lora.available() ) 
  {
    delay(100);
  }
  while (lora.available())
  Serial.write(lora.read());
}


void setup()
{
  Serial.begin(57600);
  lora.begin(57600);
  Serial.println("RN2483 Test");

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(50);
  digitalWrite(12, LOW);
  delay(50);
  digitalWrite(12, HIGH);
  delay(50);

 

  sendCmd("sys factoryRESET");
  sendCmd("sys get hweui");
  sendCmd("mac get deveui");

  // For TTN
    sendCmd("mac set deveui 8000AA00C000010A");
    sendCmd("mac set appeui FEDCBA9876543210");
    sendCmd("mac set appkey 00112233445566778899AABBCCDDEEFF" );
//  sendCmd("mac set devaddr 05060708");  // Set own address
//  sendCmd("mac set appskey 000102030405060708090a0b0c0d0e0f");
//  sendCmd("mac set nwkskey 01020304050607080910111213141516");
  sendCmd("mac set adr on");
// sendCmd("mac set dr 5");
// sendCmd("mac set pwridx 1");
 sendCmd("mac join otaa");

Wire.begin();
 

  
}

void loop() {
  Serial.write( "mac tx cnf 1 " );
    lora.write( "mac tx cnf 1 " );
    lora.write("0550");
    Serial.write("0550");
    lora.write("\r\n");
    Serial.write("\n");
    while (!lora.available() ) 
  {
    delay(100);
  }
  while (lora.available())
  Serial.write(lora.read());
    delay(10000);
  

}

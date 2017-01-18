/*  
 *  ------ LoRaWAN Code Example -------- 
 *  
 *  Explanation: This example shows how to configure the channels settings.
 *  There are 16 channels. The first three of them are always preconfigured 
 *  and cannot be changed: 868.1 MHz, 868.3 MHz and 868.5 MHz. Besides other
 *  parameters can be changed in all channels: Duty Cycle, Data rate range
 *  and channel status. This is not supported in 900.0 MHz (RN2903) modules.
 *  
 *  Copyright (C) 2015 Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify  
 *  it under the terms of the GNU General Public License as published by  
 *  the Free Software Foundation, either version 3 of the License, or  
 *  (at your option) any later version.  
 *   
 *  This program is distributed in the hope that it will be useful,  
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of  
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
 *  GNU General Public License for more details.  
 *   
 *  You should have received a copy of the GNU General Public License  
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  
 *  
 *  Version:           1.2
 *  Design:            David Gascon
 *  Implementation:    Luismi Marti, Ruben Martin
 */

#include <Wire.h>

// Cooking API libraries
#include <arduinoUART.h>
#include <arduinoUtils.h>

// LoRaWAN library
#include <arduinoLoRaWAN.h>

// Pin definition for LoRaWAN module error LED:
const int error_led =  13;

//////////////////////////////////////////////
uint8_t socket = SOCKET1;
//////////////////////////////////////////////

// variable
uint8_t error;


void setup() 
{
  //LoRaWAN example - Channels configuration
  pinMode(error_led, OUTPUT);
  digitalWrite(error_led, LOW);

  //////////////////////////////////////////////
  // 1. switch on
  //////////////////////////////////////////////

  error = LoRaWAN.ON(socket);

  // Check status
  if( error == 0 ) 
  {
    //1. Switch ON OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //1. Switch ON error 
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 2. Set frequency for specific channel
  //////////////////////////////////////////////

  error = LoRaWAN.setChannelFreq(3, 865000000);

  // Check status
  if( error == 0 ) 
  {
    //2. Frequency set OK. 
    //Frequency in LoRaWAN._freq[3]
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //2. Enable data rate error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 3. Set Duty Cycle for specific channel
  //////////////////////////////////////////////

  error = LoRaWAN.setChannelDutyCycle(3, 999);

  // Check status
  if( error == 0 ) 
  {
    //3. Adaptive Data Rate disabled OK.
    //Duty Cycle in LoRaWAN._dCycle[3]
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //3. Data rate set error 
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 4. Set Data rate range for specific channel
  //////////////////////////////////////////////

  error = LoRaWAN.setChannelDRRange(3, 0, 2);

  // Check status
  if( error == 0 ) 
  {
    //4. Data Rate range set OK.
    //Data Rate min in LoRaWAN._drrMin[3]
    //Data Rate max in LoRaWAN._drrMax[3]
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //4. Data rate set error 
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 5. Set Data rate range for specific channel
  //////////////////////////////////////////////

  error = LoRaWAN.setChannelStatus(3, "on");

  // Check status
  if( error == 0 ) 
  {
    //5. Channel status set OK in LoRaWAN._status[3]
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //5. Data rate set error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 6. Save configuration
  //////////////////////////////////////////////

  error = LoRaWAN.saveConfig();

  // Check status
  if( error == 0 ) 
  {
    //4. Save configuration OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //4. Save configuration error
    digitalWrite(error_led, HIGH);
  }


  ///////////////////////////////////////////////////////////
  // show configuration for all channels available
  ///////////////////////////////////////////////////////////


  for( int i=0; i<16; i++)
  {
    LoRaWAN.getChannelFreq(i);
    LoRaWAN.getChannelDutyCycle(i);
    LoRaWAN.getChannelDRRange(i);
    LoRaWAN.getChannelStatus(i);

    //Channel: i 
    //  Freq: LoRaWAN._freq[i]
    //  Duty cycle: LoRaWAN._dCycle[i]
    //  DR min: LoRaWAN._drrMin[i]
    //  DR max: LoRaWAN._drrMax[i]
    //  Status: LoRaWAN._status[i]
  } 
  

}


void loop() 
{


}






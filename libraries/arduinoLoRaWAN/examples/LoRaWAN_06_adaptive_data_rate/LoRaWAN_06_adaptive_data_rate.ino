/*  
 *  ------ LoRaWAN Code Example -------- 
 *  
 *  Explanation: This example shows how to enable / disable the 
 *  adaptive data rate.
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
  //LoRaWAN example - Data Rate configuration

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
  // 2. Enable Adaptive Data Rate (ADR)
  //////////////////////////////////////////////

  error = LoRaWAN.setADR("on");

  // Check status
  if( error == 0 ) 
  {
    //2. Adaptive Data Rate enabled OK. 
    //ADR in LoRaWAN._adr
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //2. Enable data rate error 
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 3. Disable Adaptive Data Rate (ADR)
  //////////////////////////////////////////////

  error = LoRaWAN.setADR("off");

  // Check status
  if( error == 0 ) 
  {
    //3. Adaptive Data Rate disabled OK. 
    //ADR in LoRaWAN._adr
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //3. Data rate set error 
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 4. Save configuration
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

}


void loop() 
{

}





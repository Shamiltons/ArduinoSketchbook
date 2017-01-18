/*  
 *  ------ LoRaWAN Code Example -------- 
 *  
 *  Explanation: This example shows how to configure the power level
 *  LoRaWAN interface:
 *    900/868 MHz   433 MHz
 *    0:  N/A        10 dBm
 *    1:  14 dBm      7 dBm
 *    2:  11 dBm      4 dBm 
 *    3:   8 dBm      1 dBm
 *    4:   5 dBm     -2 dBm 
 *    5:   2 dBm     -5 dBm
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
  //LoRaWAN example - Power configuration

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
  // 2. Set Power level
  //////////////////////////////////////////////

  error = LoRaWAN.setPower(1);

  // Check status
  if( error == 0 ) 
  {
    //2. Power level set OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //2. Power level set error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 3. Get Device EUI
  //////////////////////////////////////////////

  error = LoRaWAN.getPower();

  // Check status
  if( error == 0 ) 
  {
    //3. Power level get OK
    //Power index in LoRaWAN._powerIndex
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //3. Power level set error 
    digitalWrite(error_led, HIGH);
  }

  //------------------------------------
  //Keep in mind the power setting cannot
  //be saved in the module's memory. Every
  //time the module is powered on, the user
  //must set the parameter again
  //------------------------------------

}


void loop() 
{

}




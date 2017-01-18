/*  
 *  ------ P2P Code Example -------- 
 *  
 *  Explanation: This example shows how to configure the module
 *  for P2P mode and the corresponding parameters. The user must 
 *  keep in mind that every time the module is switched on, 
 *  the radio settings MUST be set again
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

// define radio settings
//////////////////////////////////////////////
uint8_t power = 15;
uint32_t frequency = 868100000;
char spreading_factor[] = "sf12";
char coding_rate[] = "4/5";
uint16_t bandwidth = 125;
char crc_mode[] = "on";
//////////////////////////////////////////////


// variable
uint8_t error;


void setup() 
{
  //Radio P2P example - Module configuration
  pinMode(error_led, OUTPUT);
  digitalWrite(error_led, LOW);

  //////////////////////////////////////////////
  // 1. switch on
  //////////////////////////////////////////////

  error = LoRaWAN.ON(socket);

  // Check status
  if (error == 0)
  {
    //1. Switch ON OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //1. Switch ON error
    digitalWrite(error_led, HIGH);
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 2. Enable P2P mode
  //////////////////////////////////////////////

  error = LoRaWAN.macPause();

  // Check status
  if (error == 0)
  {
    //2. P2P mode enabled OK
  }
  else 
  {
    //2. Enable P2P mode error 
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 3. Set/Get Radio Power
  //////////////////////////////////////////////

  // Set power
  error = LoRaWAN.setRadioPower(power);

  // Check status
  if (error == 0)
  {
    //3.1. Set Radio Power OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //3.1. Set Radio Power error 
    digitalWrite(error_led, HIGH);
  }

  // Get power
  error = LoRaWAN.getRadioPower();

  // Check status
  if (error == 0) 
  {
    //3.2. Get Radio Power OK.
    //Power in LoRaWAN._radioPower
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //3.2. Get Radio Power error 
    digitalWrite(error_led, HIGH);
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 4. Set/Get Radio Frequency
  //////////////////////////////////////////////

  // Set frequency
  error = LoRaWAN.setRadioFreq(frequency);

  // Check status
  if (error == 0)
  {
    //4.1. Set Radio Frequency OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //4.1. Set Radio Frequency error
    digitalWrite(error_led, HIGH);
  }

  // Get frequency
  error = LoRaWAN.getRadioFreq();

  // Check status
  if (error == 0) 
  {
    //4.2. Get Radio Frequency OK
    //Frequency in LoRaWAN._radioFreq
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //4.2. Get Radio Frequency error
    digitalWrite(error_led, HIGH);
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 5. Set/Get Radio Spreading Factor (SF)
  //////////////////////////////////////////////

  // Set SF
  error = LoRaWAN.setRadioSF(spreading_factor);

  // Check status
  if (error == 0)
  {
    //5.1. Set Radio SF OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //5.1. Set Radio SF error 
    digitalWrite(error_led, HIGH);
  }

  // Get SF
  error = LoRaWAN.getRadioSF();

  // Check status
  if (error == 0) 
  {
    //5.2. Get Radio SF OK.
    //Spreading Factor in LoRaWAN._radioSF
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //5.2. Get Radio SF error
    digitalWrite(error_led, HIGH);
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 6. Set/Get Radio Coding Rate (CR)
  //////////////////////////////////////////////

  // Set CR
  error = LoRaWAN.setRadioCR(coding_rate);

  // Check status
  if (error == 0)
  {
    //6.1. Set Radio CR OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //6.1. Set Radio CR error
    digitalWrite(error_led, HIGH);
  }

  // Get CR
  error = LoRaWAN.getRadioCR();

  // Check status
  if (error == 0) 
  {
    //6.2. Get Radio CR OK. 
    //Coding Rate in LoRaWAN._radioCR
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //6.2. Get Radio CR error
    digitalWrite(error_led, HIGH);
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 7. Set/Get Radio Bandwidth (BW)
  //////////////////////////////////////////////

  // Set BW
  error = LoRaWAN.setRadioBW(bandwidth);

  // Check status
  if (error == 0)
  {
    //7.1. Set Radio BW OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //7.1. Set Radio BW error
    digitalWrite(error_led, HIGH);
  }

  // Get BW
  error = LoRaWAN.getRadioBW();

  // Check status
  if (error == 0) 
  {
    //7.2. Get Radio BW OK.
    //Bandwidth in LoRaWAN._radioBW
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //7.2. Get Radio BW error
    digitalWrite(error_led, HIGH);
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 8. Set/Get Radio CRC mode
  //////////////////////////////////////////////

  // Set CRC
  error = LoRaWAN.setRadioCRC(crc_mode);

  // Check status
  if (error == 0)
  {
    //8.1. Set Radio CRC mode OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //8.1. Set Radio CRC mode error
    digitalWrite(error_led, HIGH);
  }

  // Get CRC
  error = LoRaWAN.getRadioCRC();

  // Check status
  if (error == 0) 
  {
    //8.2. Get Radio CRC mode OK. 
    //CRC status in LoRaWAN._crcStatus
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //8.2. Get Radio CRC mode error 
    digitalWrite(error_led, HIGH);
  }
  //-------------------------------------------------------


  //-------------------------------------------------------
  //Now the LoRaWAN module is ready for P2P communications.
  //The user must keep in mind that every time the module is
  //switched on, the radio settings MUST be set again.
  //Please check the next examples...
  //-------------------------------------------------------


}


void loop() 
{

}




/*
 *  ------ LoRaWAN Code Example --------
 *
 *  Explanation: This example shows how to configure the module
 *  and all general settings related to back-end registration
 *  process.
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

// Device parameters for Back-End registration
////////////////////////////////////////////////////////////
char DEVICE_EUI[]  = "0102030405060708";
char DEVICE_ADDR[] = "05060708";
char NWK_SESSION_KEY[] = "01020304050607080910111213141516";
char APP_SESSION_KEY[] = "000102030405060708090A0B0C0D0E0F";
char APP_KEY[] = "000102030405060708090A0B0C0D0E0F";
////////////////////////////////////////////////////////////

// variable
uint8_t error;



void setup()
{
  //LoRaWAN example - Module configuration

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
  // 2. Reset to factory default values
  //////////////////////////////////////////////

  error = LoRaWAN.factoryReset();

  // Check status
  if( error == 0 )
  {
    //2. Reset to factory default values OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //2. Reset to factory error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 3. Set/Get Device EUI
  //////////////////////////////////////////////

  // Set Device EUI
  error = LoRaWAN.setDeviceEUI(DEVICE_EUI);

  // Check status
  if( error == 0 )
  {
    //3.1. Set Device EUI OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //3.1. Set Device EUI error 
    digitalWrite(error_led, HIGH);
  }

  // Get Device EUI
  error = LoRaWAN.getDeviceEUI();

  // Check status
  if( error == 0 )
  {
    //3.2. Get Device EUI OK.
    //Device EUI in LoRaWAN._devEUI
    digitalWrite(error_led, LOW);
  }
  else
  {
    //3.2. Get Device EUI error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 4. Set/Get Device Address
  //////////////////////////////////////////////

  // Set Device Address
  error = LoRaWAN.setDeviceAddr(DEVICE_ADDR);

  // Check status
  if( error == 0 )
  {
    //4.1. Set Device address OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //4.1. Set Device address error
    digitalWrite(error_led, HIGH);
  }

  // Get Device Address
  error = LoRaWAN.getDeviceAddr();

  // Check status
  if( error == 0 )
  {
    //4.2. Get Device address OK.
    //Device address in LoRaWAN._devAddr
    digitalWrite(error_led, LOW);
  }
  else
  {
    //4.2. Get Device address error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 5. Set Network Session Key
  //////////////////////////////////////////////

  error = LoRaWAN.setNwkSessionKey(NWK_SESSION_KEY);

  // Check status
  if( error == 0 )
  {
    //5. Set Network Session Key OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //5. Set Network Session Key error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 6. Set Application Session Key
  //////////////////////////////////////////////

  error = LoRaWAN.setAppSessionKey(APP_SESSION_KEY);

  // Check status
  if( error == 0 )
  {
    //6. Set Application Session Key OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //6. Set Application Session Key error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 7. Set retransmissions for uplink confirmed packet
  //////////////////////////////////////////////

  // set retries
  error = LoRaWAN.setRetries(7);

  // Check status
  if( error == 0 )
  {
    //7.1. Set Retransmissions for uplink confirmed packet OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //7.1. Set Retransmissions for uplink confirmed packet error
    digitalWrite(error_led, HIGH);
  }

  // Get retries
  error = LoRaWAN.getRetries();

  // Check status
  if( error == 0 )
  {
    //7.2. Get Retransmissions for uplink confirmed packet OK.
    //TX retries in LoRaWAN._retries
    digitalWrite(error_led, LOW);
  }
  else
  {
    //7.2. Get Retransmissions for uplink confirmed packet error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 8. Set application key
  //////////////////////////////////////////////

  error = LoRaWAN.setAppKey(APP_KEY);

  // Check status
  if( error == 0 )
  {
    //8. Application key set OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //8. Application key set error
    digitalWrite(error_led, HIGH);
  }

  //////////////////////////////////////////////
  // 9. Channel configuration. (Recomemnded)
  // Consult your Network Operator and Backend Provider
  //////////////////////////////////////////////

  // Set channel 3 -> 867.1 MHz
  // Set channel 4 -> 867.3 MHz
  // Set channel 5 -> 867.5 MHz
  // Set channel 6 -> 867.7 MHz
  // Set channel 7 -> 867.9 MHz

  uint32_t freq = 867100000;

  for (int ch = 3; ch <= 7; ch++)
  {
    error |= LoRaWAN.setChannelFreq(ch, freq);
    freq += 200000;
  }
  
  // Check status
  if( error == 0 ) 
  {
    //9. Frequency set OK. 
    //Frequency in LoRaWAN._freq[3]
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //9. Enable Frequency error
    digitalWrite(error_led, HIGH);
  }

  //////////////////////////////////////////////
  // 10. Set Duty Cycle for specific channel. (Recomemnded)
  // Consult your Network Operator and Backend Provider
  //////////////////////////////////////////////

  for (int ch = 0; ch <= 2; ch++)
  {
    error |= LoRaWAN.setChannelDutyCycle(ch, 33333);
  }

  for (int ch = 3; ch <= 7; ch++)
  {
    error |= LoRaWAN.setChannelDutyCycle(ch, 40000);
  }

  // Check status
  if( error == 0 ) 
  {
    //10. Duty cycle channel set OK.
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //10. Data rate set error 
    digitalWrite(error_led, HIGH);
  }
  
  //////////////////////////////////////////////
  // 11. Set Data Range for specific channel. (Recomemnded)
  // Consult your Network Operator and Backend Provider
  //////////////////////////////////////////////

  for (int ch = 0; ch <= 7; ch++)
    error |= LoRaWAN.setChannelDRRange(ch, 0, 5);

  // Check status
  if( error == 0 ) 
  {
    //11. Data rate range channel set OK.
    //Data Rate min in LoRaWAN._drrMin[3]
    //Data Rate max in LoRaWAN._drrMax[3]
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //11. Data rate set error
    digitalWrite(error_led, HIGH);
  }

  //////////////////////////////////////////////
  // 12. Set Data rate range for specific channel. (Recomemnded)
  // Consult your Network Operator and Backend Provider
  //////////////////////////////////////////////

  for (int ch = 0; ch <= 7; ch++)
    error |= LoRaWAN.setChannelStatus(ch, "on");

  // Check status
  if( error == 0 ) 
  {
    //12. Channel status set OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //12. Data rate set error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 13. Save configuration
  //////////////////////////////////////////////

  error = LoRaWAN.saveConfig();

  // Check status
  if( error == 0 )
  {
    //13. Save configuration OK
    digitalWrite(error_led, LOW);
  }
  else
  {
   //13. Save configuration error
    digitalWrite(error_led, HIGH);
  }


//------------------------------------
//Now the LoRaWAN module is ready for
//joining networks and send messages.
//Please check the next examples...
//------------------------------------

}


void loop()
{
  // do nothing
}

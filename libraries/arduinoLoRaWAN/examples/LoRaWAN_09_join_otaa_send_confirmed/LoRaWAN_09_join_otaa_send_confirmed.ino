/*  
 *  ------ LoRaWAN Code Example -------- 
 *  
 *  Explanation: This example shows how to configure the module and
 *  send packets to a LoRaWAN gateway with ACK after join a network
 *  using OTAA
 *  
 *  Copyright (C) 2016 Libelium Comunicaciones Distribuidas S.L. 
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
char APP_EUI[] = "1112131415161718";
char APP_KEY[] = "01020304050607080910111213141516";
////////////////////////////////////////////////////////////

// Define port to use in Back-End: from 1 to 223
uint8_t PORT = 3;

// Define data payload to send (maximum is up to data rate)
char data[] = "0102030405060708090A0B0C0D0E0F";

// variable
uint8_t error;



void setup() 
{
  //LoRaWAN example - Send Confirmed packets (with ACK)
  pinMode(error_led, OUTPUT);
  digitalWrite(error_led, LOW);


  //------------------------------------
  //Module configuration
  //------------------------------------


  //////////////////////////////////////////////
  // 1. Switch on
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
  // 2. Set Device EUI
  //////////////////////////////////////////////

  error = LoRaWAN.setDeviceEUI(DEVICE_EUI);

  // Check status
  if( error == 0 ) 
  {
    //2. Device EUI set OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //2. Device EUI set error
    digitalWrite(error_led, LOW);
  }


  //////////////////////////////////////////////
  // 3. Set Application EUI
  //////////////////////////////////////////////

  error = LoRaWAN.setAppEUI(APP_EUI);

  // Check status
  if( error == 0 ) 
  {
    //3. Application EUI set OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //3. Application EUI set error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 4. Set Application Session Key
  //////////////////////////////////////////////
 
  error = LoRaWAN.setAppKey(APP_KEY);

  // Check status
  if( error == 0 ) 
  {
    //4. Application Key set OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //4. Application Key set error
    digitalWrite(error_led, HIGH);
  }


  //////////////////////////////////////////////
  // 5. Save configuration
  //////////////////////////////////////////////
  
  error = LoRaWAN.saveConfig();

  // Check status
  if( error == 0 ) 
  {
    //5. Save configuration OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //5. Save configuration error
    digitalWrite(error_led, HIGH);
  }


  //------------------------------------
  //Module configured
  //------------------------------------
  
  LoRaWAN.getDeviceEUI();
  //Device EUI in LoRaWAN._devEUI
  
  LoRaWAN.getDeviceAddr();
  //Device Addres in LoRaWAN._devAddr
  
}



void loop() 
{
  
  //////////////////////////////////////////////
  // 1. Switch on
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
  // 2. Join network
  //////////////////////////////////////////////

  error = LoRaWAN.joinOTAA();

  // Check status
  if( error == 0 ) 
  {
    //2. Join network OK
    digitalWrite(error_led, LOW);

  
    //////////////////////////////////////////////
    // 3. Send unconfirmed packet 
    //////////////////////////////////////////////
  
    error = LoRaWAN.sendConfirmed(PORT, data);
  
    // Error messages:
    /*
     * '6' : Module hasn't joined a network
     * '5' : Sending error
     * '4' : Error with data length
     * '2' : Module didn't response
     * '1' : Module communication error
     */
    // Check status
    if( error == 0 )
    {
      //3. Send Unconfirmed packet OK
      if (LoRaWAN._dataReceived == true)
      {
        //There's data on
        //port number: LoRaWAN._port
        //and Data in: LoRaWAN._data
        digitalWrite(error_led, LOW);
      }
    }
    else
    {
      //3. Send Confirmed packet error
      digitalWrite(error_led, HIGH);
    }
  }
  else
  {
    //2. Join network error
    digitalWrite(error_led, HIGH);
  }

    
  //////////////////////////////////////////////
  // 4. Switch off
  //////////////////////////////////////////////

  error = LoRaWAN.OFF(socket);

  // Check status
  if( error == 0 ) 
  {
    //4. Switch OFF OK
    digitalWrite(error_led, LOW);
  }
  else 
  {
    //4. Switch OFF error
    digitalWrite(error_led, HIGH);
  }
  
  
  delay(10000);
  
  

}




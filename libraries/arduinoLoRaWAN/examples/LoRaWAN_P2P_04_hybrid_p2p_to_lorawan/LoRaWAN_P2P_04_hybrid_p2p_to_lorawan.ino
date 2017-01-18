/*
 *  ------ P2P Code Example --------
 *
 *  Explanation: This example shows how to configure the module
 *  for P2P mode and LoRaWAN mode too. In this code, the Waspmote
 *  waits for new incoming P2P packets. Then routes the information
 *  received to the LoRaWAN gateway.
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

// define radio settings (P2P interface)
//////////////////////////////////////////////
uint8_t power = 15;
uint32_t frequency = 868100000;
char spreading_factor[] = "sf12";
char coding_rate[] = "4/5";
uint16_t bandwidth = 125;
char crc_mode[] = "on";
//////////////////////////////////////////////


// Define LoRaWAN settings (LoRaWAN interface)
////////////////////////////////////////////////////////////
uint8_t PORT = 3;
char DEVICE_EUI[]  = "0102030405060708";
char DEVICE_ADDR[] = "05060708";
char NWK_SESSION_KEY[] = "01020304050607080910111213141516";
char APP_SESSION_KEY[] = "000102030405060708090A0B0C0D0E0F";
////////////////////////////////////////////////////////////

// define
char packet[256];

// variable
uint8_t error;



void setup()
{
  //P2P to LoRaWAN gateway

  pinMode(error_led, OUTPUT);
  digitalWrite(error_led, LOW);

  // module setup
  error = lorawanModuleSetup();

  // Check status
  if (error == 0)
  {
    //LoRaWAN interface configured OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //LoRaWAN interface configured ERROR
    digitalWrite(error_led, HIGH);
  }


  // module setup
  error = radioModuleSetup();

  // Check status
  if (error == 0)
  {
    //Radio interface configured OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //Radio interface configured ERROR
    digitalWrite(error_led, HIGH);
  }

}


void loop()
{

  //-------------------------------------------------------
  //Listening to packets:
  //-------------------------------------------------------

  // Set receive mode
  error = LoRaWAN.receiveRadio(10000);

  // Check status
  if (error == 0)
  {
    //--> Packet received

    //data in LoRaWAN._buffer
    //length in LoRaWAN._length

    // copy packet contents into a global buffer
    strncpy( packet, (char*) LoRaWAN._buffer, sizeof(packet));

    //-------------------------------------------------------
    //Route data to LoRaWAN gateway:
    //-------------------------------------------------------

    // switch to LoRaWAN mode
    LoRaWAN.macResume();

    // join
    error = LoRaWAN.joinABP();

    // Check status
    if( error == 0 )
    {
      //Join network OK
    digitalWrite(error_led, LOW);
    }
    else
    {
      //Join network error
    digitalWrite(error_led, HIGH);
    }


    // send received packet to LoRaWAN gateway
    error = LoRaWAN.sendConfirmed(PORT, packet);

    // Check status
    if( error == 0 )
    {
      //Send Confirmed packet OK
      digitalWrite(error_led, LOW);
    }
    else
    {
      //Send Confirmed packet error
      digitalWrite(error_led, HIGH);
    }

    // module setup
    error = lorawanModuleSetup();

    // Check status
    if (error == 0)
    {
      //LoRaWAN interface configured OK
      digitalWrite(error_led, LOW);
    }
    else
    {
      //LoRaWAN interface configured ERROR
      digitalWrite(error_led, HIGH);
    }

    // module setup
    error = radioModuleSetup();

    // Check status
    if (error == 0)
    {
      //Radio interface configured OK
      digitalWrite(error_led, LOW);
    }
    else
    {
      //Radio interface configured ERROR
      digitalWrite(error_led, HIGH);
    }

  }
  else
  {
    // error code
    //  1: error
    //  2: no incoming packet
    //Error waiting for packets. error
    digitalWrite(error_led, LOW);
  }
}




/***********************************************************************************
*
* radioModuleSetup()
*
*   This function includes all functions related to the module setup and configuration
*   The user must keep in mind that each time the module powers on, all settings are set
*   to default values. So it is better to develop a specific function including all steps
*   for setup and call it everytime the module powers on.
*
*
***********************************************************************************/
uint8_t radioModuleSetup()
{

  uint8_t status = 0;
  uint8_t e = 0;

  //////////////////////////////////////////////
  // 1. switch on
  //////////////////////////////////////////////

  e = LoRaWAN.ON(socket);

  // Check status
  if (e == 0)
  {
    //1. Switch ON OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //1. Switch ON error
    digitalWrite(error_led, HIGH);
    status = 1;
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 2. Enable P2P mode
  //////////////////////////////////////////////

  e = LoRaWAN.macPause();

  // Check status
  if (e == 0)
  {
    //2. P2P mode enabled OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //2. Enable P2P mode error
    digitalWrite(error_led, HIGH);
    status = 1;
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 3. Set/Get Radio Power
  //////////////////////////////////////////////

  // Set power
  e = LoRaWAN.setRadioPower(power);

  // Check status
  if (e == 0)
  {
    //3.1. Set Radio Power OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //3.1. Set Radio Power error
    digitalWrite(error_led, HIGH);
    status = 1;
  }

  // Get power
  e = LoRaWAN.getRadioPower();

  // Check status
  if (e == 0)
  {
    //3.2. Get Radio Power OK.
    //"Power in LoRaWAN._radioPower
    digitalWrite(error_led, LOW);
  }
  else
  {
    //3.2. Get Radio Power error
    digitalWrite(error_led, HIGH);
    status = 1;
  }
  //-------------------------------------------------------


  //////////////////////////////////////////////
  // 4. Set/Get Radio Frequency
  //////////////////////////////////////////////

  // Set frequency
  e = LoRaWAN.setRadioFreq(frequency);

  // Check status
  if (e == 0)
  {
    //4.1. Set Radio Frequency OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //4.1. Set Radio Frequency error
    digitalWrite(error_led, LOW);
    status = 1;
  }

  // Get frequency
  e = LoRaWAN.getRadioFreq();

  // Check status
  if (e == 0)
  {
    //4.2. Get Radio Frequency OK
    //Frequency in LoRaWAN._radioFreq
    digitalWrite(error_led, LOW);
  }
  else
  {
    //4.2. Get Radio Frequency error
    digitalWrite(error_led, HIGH);
    status = 1;
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 5. Set/Get Radio Spreading Factor (SF)
  //////////////////////////////////////////////

  // Set SF
  e = LoRaWAN.setRadioSF(spreading_factor);

  // Check status
  if (e == 0)
  {
    //5.1. Set Radio SF OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //5.1. Set Radio SF error
    digitalWrite(error_led, HIGH);
    status = 1;
  }

  // Get SF
  e = LoRaWAN.getRadioSF();

  // Check status
  if (e == 0)
  {
    //5.2. Get Radio SF OK
    //Spreading Factor in LoRaWAN._radioSF
    digitalWrite(error_led, LOW);
  }
  else
  {
    //5.2. Get Radio SF error
    digitalWrite(error_led, HIGH);
    status = 1;
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 6. Set/Get Radio Coding Rate (CR)
  //////////////////////////////////////////////

  // Set CR
  e = LoRaWAN.setRadioCR(coding_rate);

  // Check status
  if (e == 0)
  {
    //6.1. Set Radio CR OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //6.1. Set Radio CR error
    digitalWrite(error_led, HIGH);
    status = 1;
  }

  // Get CR
  e = LoRaWAN.getRadioCR();

  // Check status
  if (e == 0)
  {
    //6.2. Get Radio CR OK.
    //Coding Rate in LoRaWAN._radioCR
    digitalWrite(error_led, LOW);
  }
  else
  {
    //6.2. Get Radio CR error
    digitalWrite(error_led, HIGH);
    status = 1;
  }
  //-------------------------------------------------------



  //////////////////////////////////////////////
  // 7. Set/Get Radio Bandwidth (BW)
  //////////////////////////////////////////////

  // Set BW
  e = LoRaWAN.setRadioBW(bandwidth);

  // Check status
  if (e == 0)
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
  e = LoRaWAN.getRadioBW();

  // Check status
  if (e == 0)
  {
    //7.2. Get Radio BW OK.
    //Bandwidth in LoRaWAN._radioBW
    digitalWrite(error_led, LOW);
  }
  else
  {
    //7.2. Get Radio BW error
    digitalWrite(error_led, HIGH);
    status = 1;
  }
  //-------------------------------------------------------


  //////////////////////////////////////////////
  // 8. Set/Get Radio CRC mode
  //////////////////////////////////////////////

  // Set CRC
  e = LoRaWAN.setRadioCRC(crc_mode);

  // Check status
  if (e == 0)
  {
    //8.1. Set Radio CRC mode OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //8.1. Set Radio CRC mode error
    digitalWrite(error_led, HIGH);
    status = 1;
  }

  // Get CRC
  e = LoRaWAN.getRadioCRC();

  // Check status
  if (e == 0)
  {
    //8.2. Get Radio CRC mode OK.
    //CRC status in LoRaWAN._crcStatus
    digitalWrite(error_led, LOW);
  }
  else
  {
    //8.2. Get Radio CRC mode error
    digitalWrite(error_led, HIGH);
    status = 1;
  }
  //-------------------------------------------------------


  return status;
}







/***********************************************************************************
 *
 * lorawanModuleSetup()
 *
 *   This function includes all functions related to the module setup for LoRaWAN
 *   performance.
 *
 *
 ***********************************************************************************/
uint8_t lorawanModuleSetup()
{

  uint8_t status = 0;
  uint8_t e = 0;


  //-------------------------------------------------------
  //LoRaWAN mode configuration:
  //-------------------------------------------------------

  //////////////////////////////////////////////
  // 1. Switch on
  //////////////////////////////////////////////

  e = LoRaWAN.ON(socket);

  // Check status
  if( e == 0 )
  {
    //1. Switch ON OK"
    digitalWrite(error_led, LOW);
  }
  else
  {
    //1. Switch ON error
    digitalWrite(error_led, HIGH);
    status = 1;
  }

  LoRaWAN.factoryReset();

  //////////////////////////////////////////////
  // 2. Set Device EUI
  //////////////////////////////////////////////

  e = LoRaWAN.setDeviceEUI(DEVICE_EUI);

  // Check status
  if( e == 0 )
  {
    //2.1. Device EUI set OK"));
    digitalWrite(error_led, LOW);
  }
  else
  {
    //2.1. Device EUI set error
    digitalWrite(error_led, HIGH);
    status = 1;
  }


  e = LoRaWAN.getDeviceEUI();

  // Check status
  if( e == 0 )
  {
    //2.2. Device EUI get OK.
    //Device EUI in LoRaWAN._devEUI
    digitalWrite(error_led, LOW);
  }
  else
  {
    //2.2. Device EUI get error
    digitalWrite(error_led, HIGH);
    status = 1;
  }


  //////////////////////////////////////////////
  // 3. Set Device Address
  //////////////////////////////////////////////

  e = LoRaWAN.setDeviceAddr(DEVICE_ADDR);

  // Check status
  if( e == 0 )
  {
    //3.1. Device address set OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //3.1. Device address set error
    digitalWrite(error_led, HIGH);
    status = 1;
  }

  e = LoRaWAN.getDeviceAddr();

  // Check status
  if( e == 0 )
  {
    //3.2. Device address get OK.
    //Device address is LoRaWAN._devAddr
    digitalWrite(error_led, LOW);
  }
  else
  {
    //3.2. Device address get error
    digitalWrite(error_led, HIGH);
    status = 1;
  }


  //////////////////////////////////////////////
  // 4. Set Network Session Key
  //////////////////////////////////////////////

  error = LoRaWAN.setNwkSessionKey(NWK_SESSION_KEY);

  // Check status
  if( error == 0 )
  {
    //4. Network Session Key set OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //4. Network Session Key set error
    digitalWrite(error_led, HIGH);
    status = 1;
  }


  //////////////////////////////////////////////
  // 5. Set Application Session Key
  //////////////////////////////////////////////

  error = LoRaWAN.setAppSessionKey(APP_SESSION_KEY);

  // Check status
  if( error == 0 )
  {
    //5. Application Session Key set OK"
    digitalWrite(error_led, LOW);
  }
  else
  {
    //5. Application Session Key set error
    digitalWrite(error_led, HIGH);
    status = 1;
  }


  //////////////////////////////////////////////
  // 6. Save configuration
  //////////////////////////////////////////////

  error = LoRaWAN.saveConfig();

  // Check status
  if( error == 0 )
  {
    //6. Save configuration OK
    digitalWrite(error_led, LOW);
  }
  else
  {
    //6. Save configuration error
    digitalWrite(error_led, HIGH);
    status = 1;
  }

  //-------------------------------------------------------

  return status;
}

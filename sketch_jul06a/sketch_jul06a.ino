// RN2483_temperature.ino - Simple LoRaWAN temperature sensor using Microchip RN2483 module
#include "SoftwareSerial.h"
#include <avr/sleep.h>
#include "Timer.h"


SoftwareSerial lora(10, 11); // RX, TX

const int rainTipperPin = 2;              //The reed switch outputs to digital pin 2
int rainTipperState = 0;                    //Current value of reed switch
int lastRainTipperState = 0;                //Old value of reed switch
int rainTipperCounter = 0;              //This is the variable that hold the count of switching
long waitingTime = 10000;   // the waiting time before goes to sleep
long interval = 5000;         //Waiting time before sends data and sets counter to 0
unsigned long previousMillis = 0; //last time before updated
unsigned long rainTipperTimer = 0;  //Time elapsed since last status update
char msgBuf[40];
Timer t;

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

/*void waitForResponse()
  {
  while (!lora.available() );
  Serial.write(lora.read());
  Serial.println("Ok");

  }*/

char getHexHi( char ch ) {
  char nibble = ch >> 4;
  return (nibble > 9) ? nibble + 'A' - 10 : nibble + '0';
}
char getHexLo( char ch ) {
  char nibble = ch & 0x0f;
  return (nibble > 9) ? nibble + 'A' - 10 : nibble + '0';
}

void sendData( char *data)
{
  Serial.write( "mac tx uncnf 1 " );
  lora.write( "mac tx uncnf 1 " );
  // Write data as hex characters
  char *ptr = data;
  int idiotCount = 50;
  while (*ptr && idiotCount )
  {
    lora.write( getHexHi( *ptr ) );
    lora.write( getHexLo( *ptr ) );

    Serial.write( getHexHi( *ptr ) );
    Serial.write( getHexLo( *ptr ) );

    ptr++;
    idiotCount--;
  }
  Serial.println("ta mandando");
  lora.write("\r\n");
  Serial.write("\n");
  delay(100);
  while (lora.available())
    Serial.write(lora.read());

}

void pin2Interrupt()
{
  detachInterrupt(0);
}

void enterSleep(void)
{
  /*  Setup pin2 as an interrupt and attach handler.*/
  attachInterrupt(0, pin2Interrupt, LOW);

  delay(100);

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  sleep_enable();

  sleep_mode();

  sleep_disable();
  Serial.println("Waking up");

}

void setup()
{

  Serial.begin(9600);
  while (!Serial);
  lora.begin(9600);

  
    
  

  Serial.println("RN2483 Test");

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(50);
  digitalWrite(12, LOW);
  delay(50);
  digitalWrite(12, HIGH);
  delay(50);

  //waitForResponse();
  /*while (!lora.available() );
    Serial.write(lora.read());
    Serial.println("Ok");*/
  if (lora.available() > 0)
  {
    Serial.write(lora.read());
  }

  sendCmd("sys factoryRESET");
  sendCmd("sys get hweui");
  sendCmd("mac get deveui");
  sendCmd("sys sleep 10000");

  // For TTN
  sendCmd("mac set devaddr 06060708");  // Set own address
  sendCmd("mac set appskey 000202030405060708090a0b0c0d0e0f");
  sendCmd("mac set nwkskey 02020304050607080910111213141516");
  sendCmd("mac set adr off");
  sendCmd("mac set dr 0");
  sendCmd("mac set pwridx 1");
  sendCmd("mac join abp");
  t.every(10000, sendMessage);
  
}

void loop()
{

  
   
  // put your main code here, to run repeatedly:
  // Serial.println("Reading Data");
  /*int mv = getRealBatteryVoltage() * 1000.0;
    Serial.print("Battery Voltage (mV) = ");
    Serial.println(mv);*/
  rainTipper();

  sprintf(msgBuf, "%d", (int)rainTipperCounter);

  t.update();

}
void rainTipper()
{
  rainTipperState = digitalRead(rainTipperPin);      //Read the status of the Reed swtich

  if (rainTipperState != lastRainTipperState)    //Check to see if the status has changed
  {
    if (rainTipperState == HIGH)
    {
      delay(10);
      rainTipperCounter++;   //Add 1 to the count of bucket tips
      rainTipperTimer = millis();  //Start to count time again
      Serial.print("Count = ");
      Serial.println(rainTipperCounter);  //Output the count to the serial monitor
    }

  }
  lastRainTipperState = rainTipperState;              //Make the old value equal to the current value


  if (rainTipperState = lastRainTipperState && millis() - rainTipperTimer > waitingTime) //Check the time elapsed since last status change
  {
    Serial.print("Entering sleep ");

    enterSleep();  //Call sleep function
  }

}
void sendMessage()
{
  led_on();
  sendData(msgBuf);
  led_off();
}
void led_on()
{
  digitalWrite(13, 1);
}

void led_off()
{
  digitalWrite(13, 0);
}





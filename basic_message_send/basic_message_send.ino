
#include "SoftwareSerial.h"

bool DEBUG = true;

SoftwareSerial lora(10, 11); // TX,RX

void setup() {
  // put your setup code here, to run once:

  Serial.begin(57600);
  lora.begin(57600);

   rst();
  abp();

}

void loop() {
  // put your main code here, to run repeatedly:



    delay(10000);

}

void sendData(char *data) 
{
  if(DEBUG){
    Serial.println ("im sending a message now");
    Serial.write( "mac tx uncnf 10 " );
    lora.write( "mac tx uncnf 10 " );
    lora.write(data);
    Serial.write(data);
    lora.write("\r\n");
    Serial.write("\n");
    while (lora.available()){
    Serial.write(lora.read());}
    Serial.println("ive sent the message");
    }

  if (!DEBUG){
    lora.write( "mac tx uncnf 10 " );
    lora.write(data);
    lora.write("\r\n");
   
  }
}



void sendCmd( char *cmd) 
{

if (DEBUG){
  Serial.write( cmd );
  Serial.write("\n");
  lora.write(cmd);
  lora.write("\r\n");
    while (!lora.available() ) 
  {
    delay(100);
  }
  while (lora.available()){
  Serial.write(lora.read());
  Serial.write("\n");}
  }

if (!DEBUG){
  lora.write(cmd);
  lora.write("\r\n");
 

}

}

void rst()
{
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(50);
  digitalWrite(12, LOW);
  delay(50);
  digitalWrite(12, HIGH);
  delay(50);
}

void otaa(){
  sendCmd("sys factoryRESET");
  sendCmd("sys get hweui");
  sendCmd("mac get deveui");
  sendCmd("mac set deveui 8000AA00C000010A");
  sendCmd("mac set appeui FEDCBA9876543210");
  sendCmd("mac set appkey 00112233445566778899AABBCCDDEEFF" );
  adr_on();
  sendCmd("mac join otaa");
}

void abp(){
  sendCmd("sys factoryRESET");
  sendCmd("sys get hweui");
  sendCmd("mac get deveui");
  sendCmd("mac set devaddr 05060708");  // Set own address
  sendCmd("mac set appskey 000102030405060708090a0b0c0d0e0f");
  sendCmd("mac set nwkskey 01020304050607080910111213141516");
  adr_on();
  sendCmd("mac join abp");
}

void adr_off(){
  sendCmd("mac set adr on");
  sendCmd("mac set dr 0");
  sendCmd("mac set pwridx 1");
}

void adr_on(){
  sendCmd("mac set adr on");
}

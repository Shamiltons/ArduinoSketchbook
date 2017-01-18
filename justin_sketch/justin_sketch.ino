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

    sendCmd("radio tx 00010203040506070809101112");
  

    delay(1000);



}

void abp(){
  sendCmd("sys factoryRESET");
  sendCmd("sys get hweui");
  sendCmd("mac pause");
  sendCmd("radio set mod lora");
  sendCmd("radio set freq 869000000");
  sendCmd("radio set pwr 10");
  sendCmd("radio set sf sf7");
  sendCmd("radio set bw 125");
  sendCmd("radio set crc on");
  sendCmd("radio set cr 4/8");
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
//    Serial.write("\n\r");
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
        Serial.write("\r");
        lora.write(cmd);
        lora.write("\r\n");
          while (!lora.available() ) 
        {
          delay(100);
        }
        while (lora.available()){
        Serial.write(lora.read());
        Serial.write("\r");}
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

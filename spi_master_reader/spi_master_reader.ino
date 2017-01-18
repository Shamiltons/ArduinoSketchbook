#include <Wire.h>
const int slavePowerPin = 4;
int slavePowerState = LOW;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
}

void loop() {
  slavePowerState = HIGH;
  digitalWrite(slavePowerPin, slavePowerState);
   delay(5000);
  

  delay(100);
  Wire.requestFrom(8, 18);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    
  }
   Serial.print("\n");

  slavePowerState = LOW;
  digitalWrite(slavePowerPin, slavePowerState);

  delay(5000);
  
}

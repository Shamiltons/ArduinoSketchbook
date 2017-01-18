/*
  Arduino sketch to record the switching of the reed switch in the rain gauge
  The sketch works by counting the number of times the reed switch changes status (HIGH or LOW)*/

#include <avr/interrupt.h>

#include <avr/sleep.h>

const int rainTipperPin = 2;              //The reed switch outputs to digital pin 2
int rainTipperState = 0;                    //Current value of reed switch
int lastRainTipperState = 0;                //Old value of reed switch
int rainTipperCounter = 0;              //This is the variable that hold the count of switching
long waitingTime = 10000;   // the waiting time before goes to sleep
long interval = 600000;         //Waiting time before sends data and sets counter to 0
unsigned long previousMillis = 0; //last time before updated
unsigned long rainTipperTimer = 0;  //Time elapsed since last status update

void setup() {
  Serial.begin(9600);
  pinMode (rainTipperPin, INPUT);
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

void loop() {
  
  rainTipperState = digitalRead(rainTipperPin);      //Read the status of the Reed swtich

  if (rainTipperState != lastRainTipperState) {   //Check to see if the status has changed
    if(rainTipperState == HIGH){
      delay(50);
      rainTipperCounter++;   //Add 1 to the count of bucket tips
      rainTipperTimer = millis();  //Start to count time again
      Serial.print("Count = ");
      Serial.println(rainTipperCounter);  //Output the count to the serial monitor
      }
    delay(50);
  }
    lastRainTipperState = rainTipperState;              //Make the old value equal to the current value
  if(rainTipperState = lastRainTipperState && millis() - rainTipperTimer > waitingTime){  //Check the time elapsed since last status change
    
      Serial.print("Entering sleep ");
      
      enterSleep();  //Call sleep function
    }
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {   //Wait 10 min to send information and set counter back to zero
     previousMillis = currentMillis;
     rainTipperCounter = 0; 
  }
}






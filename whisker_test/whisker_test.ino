
#include <Servo.h> //include libraries
#include <stdio.h>
#include <stdlib.h>

//Global Variable Declarations

int speakerPin = 11;   // Digital pin number for the speaker
int whiskerPin = 7;    


// Setup function

void setup() {
  // put your setup code here, to run once:

  // Assign pin modes
  pinMode(whiskerPin,INPUT);
  
  // play tone on speaker to indicate setup
  tone(speakerPin, 2500, 100);
  delay(100);
  tone(speakerPin, 3000, 100);
  delay(100);
  tone(speakerPin, 3500, 100);
  delay(500);

}

// Main loop

void loop() {
  
  byte whisker = digitalRead(whiskerPin);     // read the value on the whisker pin (because of our circuit: FALSE = press, TRUE = no press)

  if( !whisker )
  {
    tone(speakerPin,3000,100);
  }
  
}

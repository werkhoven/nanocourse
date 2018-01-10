
#include <Servo.h> //include libraries
#include <stdio.h>
#include <stdlib.h>

//Global Variable Declarations

int speakerPin = 11;   // Digital pin number for the speaker
int L_whiskerPin = 7;
int R_whiskerPin = 6;    
    


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
  
  byte L_whisker = digitalRead(L_whiskerPin);     // read the value on the whisker pin (because of our circuit: FALSE = press, TRUE = no press)
  byte R_whisker = digitalRead(R_whiskerPin);     // read the value on the whisker pin (because of our circuit: FALSE = press, TRUE = no press)

  if( !L_whisker )
  {
    tone(speakerPin,3000,100);
    Serial.println("LEFT");
  }

  if( !R_whisker ){
    tone(speakerPin,2000,100);
    Serial.println("RIGHT");
  }
  
}

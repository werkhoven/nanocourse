
#include <Servo.h> //include libraries
#include <stdio.h>
#include <stdlib.h>

//Global Variable Declarations

int speakerPin = 11;   // Digital pin number for the speaker
int duration = 1000;   // Duration of the tone (ms)
int frequency = 2500;  // Frequency of the tone (Hz)


// Setup function

void setup() {
  // put your setup code here, to run once:

  tone(speakerPin, frequency, duration);    // Play the tone using the built-in tone function

}

// Main loop

void loop() {
  
  // Do nothing forever and ever
  
}

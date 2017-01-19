/* This is a simple script to help you empirically determine the approximate 
 * amount of time it will take your bot to perform a 360 spin when spinning
 * at full speed. Simply set the spin_time variable to a test duration and
 * compile the script to the script to the bot. Make sure the power switch
 * is set to the 1 position (breadboard only) before compiling. Once the 
 * script is uploaded, unplug the USB cable and flip the power switch to
 * position 2 power both the breadboard and servos. Repeat until desired time
 * is found.
  */

#include <Servo.h> //include libraries
#include <stdio.h>
#include <stdlib.h>

Servo servoLeft;      // Declare servo objects
Servo servoRight;

int spin_time = 2100;   // Time to spin the robot in ms, 


void setup() {
  // put your setup code here, to run once:

  servoLeft.attach(13);          // Attach left signal to pin 13
  servoRight.attach(12);         // Attach right signal to pin 12
  delay(500);                    // Pause 500ms

  maneuver('r');                 // Initiate right turn with maneuver function (see below for more details)      
  delay(spin_time);              // Pause spin_time ms
  maneuver('s');                 // send stop motors command
}

void loop() {
  // Do nothing after setup
}



// Custom function definitions

// Here we define a simple function to send simple commands to the motors
void maneuver(char c)                              
{
  switch(c)                                  // Switch based on c
  {
    case 'f':                                // c contains 'f'
      servoLeft.writeMicroseconds(1700);     // Full speed forward
      servoRight.writeMicroseconds(1300);
      break;
    case 'b':                                // c contains 'b'
      servoLeft.writeMicroseconds(1300);     // Full speed backward
      servoRight.writeMicroseconds(1700);
      break;
    case 'l':                                // c contains 'l'
      servoLeft.writeMicroseconds(1300);     // Rotate left in place
      servoRight.writeMicroseconds(1300);
     break;
   case 'r':                                // c contains 'r'
     servoLeft.writeMicroseconds(1700);     // Rotate right in place
     servoRight.writeMicroseconds(1700);
     break;
   case 's':                                // c contains 's'
     servoLeft.writeMicroseconds(1500);     // Stop
     servoRight.writeMicroseconds(1500);
     break;
 }
}

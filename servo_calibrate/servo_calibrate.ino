#include <Servo.h> //include servo library

Servo servoLeft;    // declare servo objects
Servo servoRight;

void setup() {
  // put your setup code here, to run once:
    // put your setup code here, to run once:
  servoLeft.attach(13);                      // Attach left servo signal to pin 13
  servoRight.attach(12);                     // Attach right servo signal to pin 12

}

void loop() {

  // Write stop command to both motors
     servoLeft.writeMicroseconds(1500);
     servoRight.writeMicroseconds(1500);
}

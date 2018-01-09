// THIS IS A DUMB BOT
// Suffice it to say, this bot has MAJOR ISSUES.
// That being said, it's got a lot of raw components to be something truly special.
// It's you're job to help it refine those components to overcome it's limitations and ascend to greatness.
// I can already tell you've got some elements of greatness too.
// I'm reassured that, together, you are your bot can reach for the stars and make your dreams come true.
// Good luck. 

#include <Servo.h>   //include servo library
#include <stdio.h>
#include <stdlib.h>

Servo servoLeft;
Servo servoRight;

// pin assignments
int whiskerPin=7;
int F_irLED=6;
int R_irLED=5;
int R_irSensor=3;
int L_irSensor=9;
int speakerPin = 11;
byte whisker = 1;
bool findAngle = false;
long tTest[2];
byte man_ct = 0;
long ang2ms = 2385/360;


// border detection variables
float bottomDetector=0;                                   // current value on the phototransistor                   
float bottomThresh=1.1;                                   // threshold for detection


// maneuver variables
char dir = 'f';             // direction of the maneuver (initialized to forward)
char prev_dir = 's';        // direction of the previous maneuver (initialized to stop)
long manDur = 800;          // duration of the current maneuver 
long minDur = 500;
long boutLength = 5000;     // maximum length of forward run
long fullSpin = 2190;       // duration of a full 360 degree spin (determined emperically)
long smallSweep = 450;      // small angle correction sweep

// IR detection variables


// global script timestamps
long tCurrent=0;
long tPrevious=0;
long tElapsed=0;




// ******************************************************* //
// ************** MICROCONTROLLER SETUP ****************** //
// ******************************************************* //


// Setup runs once before execution of the main loop
void setup() {

  // initialize serial and display initialization msg
  Serial.begin(9600);
  Serial.println("Beep!");

  // play tone on speaker to indicate setup
  tone(speakerPin, 2500, 100);
  delay(100);
  tone(speakerPin, 3000, 100);
  delay(100);
  tone(speakerPin, 3500, 100);
  delay(500);

  // configure pins
  pinMode(whiskerPin, INPUT);                         // Set whisker pin to input
  pinMode(L_irSensor, INPUT);
  pinMode(R_irSensor, INPUT);
  pinMode(F_irLED, INPUT);
  pinMode(R_irLED, INPUT);
  servoLeft.attach(13);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12

  // start bot moving forward
  maneuver(dir);

  // initialize luminance threshold
  bottomDetector=volts(A0);
  bottomThresh = bottomDetector * 1.5;


  // Take first time stamp
  tPrevious=micros();

}



// ******************************************************* //
// ******************* MAIN LOOP ************************* //
// ******************************************************* //



void loop() {


  //**************** RECORD TIME STAMPS *************//
  
  tCurrent=micros();                        // timestamp in microseconds
  tElapsed=tCurrent-tPrevious+tElapsed;
  tPrevious=tCurrent;
  Serial.println(man_ct);
  

  // ****************************************************************** //
  // *********************** BORDER DETECTION ************************* //
  // ****************************************************************** //

  // check whiskers
  //byte whisker = digitalRead(whiskerPin);              //  LOW = whisker pressed
  
  // read from the phototransitor
  bottomDetector = volts(A0);

  // reorient if photosensor value exceeds threshold or whisker press is detected
  if((bottomDetector > bottomThresh || !whisker ) && tElapsed > minDur*1000){  

      if(dir=='f'){
        
        dir = 'b';
        
        if(findAngle){
          tTest[man_ct] = tElapsed;
          manDur = tElapsed/1000;
        }
        else{
          findAngle = true;
          manDur = minDur;
          man_ct = 0;
        }
      }
      else{
        dir = switchDir(dir);
        manDur = random(0,800);                  // limit reoriention time between 400-1200ms for small angle turns
        manDur = manDur + 400;
      }

      tPrevious=micros();                        // Grab a new timestamp and reset the maneuver clock
      tElapsed=0;

      tone(speakerPin,3500,150);
  }


  // play warning if phototransitor is saturated
  if( bottomThresh > 5){
    bottomThresh = 5;
    tone(speakerPin,3500,300);
    delay(300);
    tone(speakerPin,2500,300);
    delay(300);
    tone(speakerPin,3500,300);
    delay(300);
    tone(speakerPin,2500,300);
  }


  // ************** IR DETECTION ****************** //

      // make your own code!

  
  // ****************************************************************** //
  // ********************* IR DETECTION DECISION MAKING *************** //
  // ****************************************************************** //
    
  
        // make your own code!


  // *************************************** //
  // ************** MANEUVERS ************** //
  // *************************************** //


  // assign a new maneuver if the maneuver duration is exceeded
   if ( tElapsed > manDur*1000 ){

    // previous maneuver was FORWARD
    if( prev_dir == 'f' ){
      
      findAngle = false;
      //man_ct = 0;
        
    }

    // previous maneuver was BACKWARD
    if( prev_dir == 'b' ){
      
      if(findAngle){
        switch(man_ct){
          
          case 0: 
            dir = 'r';
            manDur = 20*ang2ms;
            break;
            
          case 1: 
            dir = 'l';
            manDur = 40*ang2ms;
            break;
            
          case 2:
            findAngle = false;
            Serial.print("Right: ");
            Serial.println(tTest[0]);
            Serial.print("Left: ");
            Serial.println(tTest[1]);
            if(tTest[0]>tTest[1]){
              dir = 'r';
              manDur = 40*ang2ms + 25*ang2ms;
              Serial.println("RIGHT");
            }
            else{
              dir='l';
              manDur = 25*ang2ms;
              Serial.println("LEFT");
            }
            break;
        }      
        man_ct++;
      } 
      else{
        dir = randDir();                         // randomly choose a left-right direction
        manDur = random(0,300);                  // limit spin time to 300-600s
        manDur = manDur + 300;
      }
      
    }

    // previous maneuver was a TURN
    else if( prev_dir == 'r' || prev_dir == 'l' ){

        dir = 'f';
        manDur = boutLength;
      
    }
    
  }

  // execute maneuver if direction assignment has changed
  if( dir != prev_dir ){
/*
    Serial.print("MAN: ");                   // print the direction and it's duration to the serial monitor if the direction changes
    Serial.println(dir);
    Serial.print("DUR: ");
    Serial.println(manDur);
    Serial.println(" ");
    Serial.println(man_ct);
    */
    
    maneuver('s');                             // stop the servos before initiating new command
    maneuver(dir);                             // execute new maneuver
    prev_dir = dir;                            // set previous direction to the direction of the new maneuver
    tPrevious=micros();                        // Grab a more accurate tStamp for time of maneuver
    tElapsed=0;                                // Re-initialize timer to 0
    
  }


}




// ********************************************************** //
// ******************* END OF MAIN LOOP ********************* //
// ********************************************************** //





// ************************************************************** //
// ****************** FUNCTION DEFINITIONS ********************** //
// ************************************************************** //


/* Here is where we define our own functions. You can customize these or create your
   own to do anything you might call in the main loop above!
 */



// Measures volts at adPin and converts the voltage measured as a 10bit integer to a number 0-5 volts
float volts(int adPin)                       
{                                            
 return float(analogRead(adPin)) * 5.0 / 1024.0;
}


// This function takes direction (dir) as an input and switches it the the opposite direction
char switchDir(char c)
{
  switch(c){
    case 'f':
        c = 'b';      // switch forward to backward
        break;
    case 'b':
        c = 'f';      // switch backward to forward
        break;
    case 'r':
        c = 'l';      // switch right to left
        break;
    case 'l':
        c = 'r';      // switch left to right
        break;
  }
  return c;           // output the new direction
}

// Randomly generates a left-right direction to turn
char randDir()
{
  char turnDir = ' ';
  long randNum = random(0,2);       // generate a random number
  if( randNum ){ turnDir = 'r'; }
  else turnDir = 'l';
  return turnDir;
}


// function to send simple commands to the motors
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




byte detectIR(int sensor)          // Strobe the IR LEDs and read the value on the sensor pin of the IR detector
{
  byte ledStatus=digitalRead(sensor);       // Read the value on the signal pin of the sensor (by default, 0=IR detected, 1=not detected)
  delay(1);
  return !ledStatus;                        // Return the inverse to make 1=PREY, 0=NO PREY
}

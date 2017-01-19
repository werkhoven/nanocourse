// assign pin numbers
int LED_pin = 6;         
int R_irSens = 3;
int L_irSens = 9;
int speaker_pin = 11;

int receiver_freq = 57600;    // peak frequency of the IR sensors (Prey sensors = 30kHz, Predator sensors = 57.6kHz)


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);             // begin serial session
  Serial.println("BEEP");

  tone(speaker_pin,1500,100);     // play a unique tone to signify setup
  delay(100);
  tone(speaker_pin,2000,100);
  delay(100);
  tone(speaker_pin,2500,100);
  delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:

  strobe_IR(LED_pin, receiver_freq);                                 // strobe the IR LEDs (defined below)
  
  byte R_irSens_val = detectIR(R_irSens);      // read the current values on the IR receivers
  byte L_irSens_val = detectIR(L_irSens);
  
  Serial.println(L_irSens_val);             // print the sensor value to the serial port, specifying the print mode as decimal to prevent value from being truncated

}


// Function definitions

// Measures volts at adPin and converts the voltage measured as a 10bit integer to a number 0-5 volts
float volts(int adPin)                       
{                          
                    
 return float(analogRead(adPin)) * 5.0 / 1024.0;
 
}


void strobe_IR(int LED_pin, int freq)
{

  tone(LED_pin, freq, 8);
  delay(1);
  
}


byte detectIR(int sensor)          // Strobe the IR LEDs and read the value on the sensor pin of the IR detector
{
  byte ledStatus=digitalRead(sensor);       // Read the value on the signal pin of the sensor (by default, 0=IR detected, 1=not detected)
  return !ledStatus;                        // Return the inverse to make 1=PREY, 0=NO PREY
}

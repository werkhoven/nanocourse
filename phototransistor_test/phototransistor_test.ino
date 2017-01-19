
int pause_duration = 400;       // wait time each iteration (ms)
int speaker_pin = 11;           


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

  float sensor_value = volts(A3);               // call our function (defined below) to read the current value on the sensor and store in local float named sensor_value
  Serial.println(sensor_value,DEC);             // print the sensor value to the serial port, specifying the print mode as decimal to prevent value from being truncated

  delay(pause_duration);                        // insert a pause to prevent the serial monitor from being flooded with values so quickly that we can't read them

}


// Function definitions

// Measures volts at adPin and converts the voltage measured as a 10bit integer to a number 0-5 volts
float volts(int adPin)                       
{                          
                    
 return float(analogRead(adPin)) * 5.0 / 1024.0;
 
}

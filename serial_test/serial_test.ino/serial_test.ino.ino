/* An annoying version of "Hello World" where your robot talks back
  */

// Variable declarations

char flag[] ="You're a robot.";                        // Declare character array with flagged statement
char response[] = "I know you are, but what am I?";     // Declare character array containing the robot's response





void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);           // Initialize serial session w/ baud rate 9600 (this value is standard and will always work for our purposes)
}



void loop() {


  if( Serial.available() )                              // check to see if bytes are available on serial port
  {
      delay(50);                                         // wait for all bytes to arrive in buffer before reading them in
      uint8_t counter = 0;                               // local variable to score number of matching values
      int num_bytes = Serial.available();                // fetch the number of bytes (characters) available on the port
      char string_in[num_bytes];                         // declare an empty string of size num_bytes
      
      Serial.readBytes((char*)string_in,num_bytes);      // read in num_byte characters from serial port and store them in your string

      for( int i=0; i < num_bytes; i++)                   // initiate a for loop with num_byte iterations
      {
        
        if( string_in[i] == flag[i] )                     // if the input matches to your the flagged string, increment the counter
        {
          counter++;
        }
        
      }


      if( counter == sizeof(flag)/sizeof(char)-1 )        // display the response if the string is a complete match
      {
          Serial.println(response);                       // print the response and start a new line
      }
      else
      {
          Serial.println("Sorry, you're not making any sense.");    // otherwise, indicate that the input doesn't make any sense
      }
      
  }
  

  
}

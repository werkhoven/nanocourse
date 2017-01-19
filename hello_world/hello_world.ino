/* An annoying version of "Hello World" where your robot talks back
  */

// Variable declarations

char greeting[] = "HELLO WORLD";                        // Declare character array with flagged statement

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);           // Initialize serial session w/ baud rate 9600 (this value is standard and will always work for our purposes)
  Serial.println(greeting);     // print the greeting and start a new line

  Serial.print("We can print messages on");
  Serial.print(" the same line with Serial.print(),");
  Serial.println(" or we can print values followed by a ");
  Serial.print(" new line with Serial.println()");
}



void loop() {
  
  // Do nothing after setup
  
}

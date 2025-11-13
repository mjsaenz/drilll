/*
  Basic LED Blink Test
  This sketch blinks the built-in LED on and off repeatedly.
  Use this to verify your Arduino board is working correctly.
*/

// The built-in LED pin number (usually 13 on Uno, or LED_BUILTIN on newer boards)
// LED_BUILTIN is automatically defined for most Arduino boards
int ledPin = LED_BUILTIN;

// The setup function runs once when you press reset or power the board
void setup() {
  // Initialize the digital pin as an output
  pinMode(ledPin, OUTPUT);
}

// The loop function runs over and over again forever
void loop() {
  // Turn the LED on (HIGH is the voltage level)
  digitalWrite(ledPin, HIGH);
  
  // Wait for 1 second (1000 milliseconds)
  delay(1000);
  
  // Turn the LED off by making the voltage LOW
  digitalWrite(ledPin, LOW);
  
  // Wait for 1 second
  delay(1000);
}


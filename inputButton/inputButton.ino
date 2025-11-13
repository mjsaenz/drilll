/*
  Button Press Serial Output
  This sketch reads a momentary push button connected to pin 2
  and outputs button press events to the serial monitor.
  
  Wiring:
  - Button pin 1 -> Digital Pin 2
  - Button pin 2 -> GND
  - Internal pull-up resistor is used (no external resistor needed)
*/

const int buttonPin = 2;        // Pin connected to button
int lastButtonState = HIGH;     // Previous button state (HIGH = not pressed with pull-up)
int currentButtonState;         // Current button state
unsigned long lastDebounceTime = 0;  // Last time button state changed
unsigned long debounceDelay = 50;    // Debounce delay in milliseconds

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  
  // Configure button pin as input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Read initial button state
  lastButtonState = digitalRead(buttonPin);
  
  Serial.println("Button monitor started!");
  Serial.println("Press the button to see output...");
}

void loop() {
  // Read the current state of the button
  int reading = digitalRead(buttonPin);
  
  // Check if button state has changed (for debouncing)
  if (reading != lastButtonState) {
    // Reset the debounce timer
    lastDebounceTime = millis();
  }
  
  // If enough time has passed since last state change, update button state
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If button state has changed, process it
    if (reading != currentButtonState) {
      currentButtonState = reading;
      
      // Button is pressed when state is LOW (with pull-up configuration)
      if (currentButtonState == LOW) {
        Serial.println("Button pressed!");
      } else {
        Serial.println("Button released!");
      }
    }
  }
  
  // Save the current reading for next loop iteration
  lastButtonState = reading;
}


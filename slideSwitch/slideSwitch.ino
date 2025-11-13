/*
  Slide Switch Serial Output
  This sketch reads a slide switch connected to pin 8
  and outputs the switch state to the serial monitor.
  
  Wiring:
  - Switch terminal 1 -> Digital Pin 8
  - Switch terminal 2 -> GND
  - Internal pull-up resistor is used (no external resistor needed)
  
  Note: With INPUT_PULLUP configuration:
  - Switch OFF (open) = HIGH
  - Switch ON (closed) = LOW
*/

const int switchPin = 8;        // Pin connected to slide switch
int lastSwitchState = HIGH;     // Previous switch state
int currentSwitchState;          // Current switch state
unsigned long lastDebounceTime = 0;  // Last time switch state changed
unsigned long debounceDelay = 50;    // Debounce delay in milliseconds

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  
  // Configure switch pin as input with internal pull-up resistor
  pinMode(switchPin, INPUT_PULLUP);
  
  // Read initial switch state
  lastSwitchState = digitalRead(switchPin);
  currentSwitchState = lastSwitchState;
  
  Serial.println("Slide switch monitor started!");
  Serial.print("Initial switch state: ");
  Serial.println(currentSwitchState == LOW ? "ON" : "OFF");
}

void loop() {
  // Read the current state of the switch
  int reading = digitalRead(switchPin);
  
  // Check if switch state has changed (for debouncing)
  if (reading != lastSwitchState) {
    // Reset the debounce timer
    lastDebounceTime = millis();
  }
  
  // If enough time has passed since last state change, update switch state
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If switch state has changed, process it
    if (reading != currentSwitchState) {
      currentSwitchState = reading;
      
      // Output the new state
      if (currentSwitchState == LOW) {
        Serial.println("Switch: ON");
      } else {
        Serial.println("Switch: OFF");
      }
    }
  }
  
  // Save the current reading for next loop iteration
  lastSwitchState = reading;
}


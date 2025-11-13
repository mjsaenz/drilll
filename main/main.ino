/*
  Main Input Monitor
  This sketch combines all game inputs and outputs value on change:
  [inputButton/slideSwitch/forceSensor0/forceSensor1],[on/off/value]
  
  Wiring:
  - Button: Pin 2 -> Button -> GND (INPUT_PULLUP)
  - Slide Switch: Pin 8 -> Switch -> GND (INPUT_PULLUP)
  - Force Sensor 0: A0 -> 10kΩ -> 5V, A0 -> Sensor -> GND
  - Force Sensor 1: A1 -> 10kΩ -> 5V, A1 -> Sensor -> GND
*/

// Pin definitions
const int buttonPin = 2;        // Button pin
const int switchPin = 8;        // Slide switch pin
const int forceSensor0Pin = A0; // Force sensor 0 pin
const int forceSensor1Pin = A1; // Force sensor 1 pin

// Button state variables
int buttonReading = HIGH;
int lastStableButtonState = HIGH;  // Last confirmed stable state
unsigned long lastButtonDebounceTime = 0;
const unsigned long buttonDebounceDelay = 1;

// Switch state variables
int switchReading = HIGH;
int lastSwitchState = HIGH;
int currentSwitchState = HIGH;
unsigned long lastSwitchDebounceTime = 0;
const unsigned long switchDebounceDelay = 5;

// Force sensor variables
int forceSensor0Value = 0;
int forceSensor1Value = 0;
int lastForceSensor0Value = 0;
int lastForceSensor1Value = 0;
const int forceSensorChangeThreshold = 200;

void setup() {
  // Initialize serial communication at 115200 baud
  Serial.begin(115200);
  
  // Configure button pin as input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Configure switch pin as input with internal pull-up resistor
  pinMode(switchPin, INPUT_PULLUP);
  
  // Configure analog pins (analog pins are analog by default)
  pinMode(forceSensor0Pin, INPUT);
  pinMode(forceSensor1Pin, INPUT);
  
  // Read initial states
  lastStableButtonState = digitalRead(buttonPin);
  
  lastSwitchState = digitalRead(switchPin);
  currentSwitchState = lastSwitchState;
  
  lastForceSensor0Value = analogRead(forceSensor0Pin);
  lastForceSensor1Value = analogRead(forceSensor1Pin);
  
  Serial.println("Control ready!");
}

void loop() {
  // Read button state
  buttonReading = digitalRead(buttonPin);
  
  // Check if button state has changed from last stable state
  if (buttonReading != lastStableButtonState) {
    // State changed, start debounce timer
    if (lastButtonDebounceTime == 0) {
      lastButtonDebounceTime = millis();
    }
    
    // If debounce delay has passed, confirm the state change
    if ((millis() - lastButtonDebounceTime) >= buttonDebounceDelay) {
      // State is stable, output the change
      if (buttonReading == LOW) {
        Serial.println("inputButton,on");
      } else {
        Serial.println("inputButton,off");
      }
      
      // Update stable state and reset debounce timer
      lastStableButtonState = buttonReading;
      lastButtonDebounceTime = 0;
    }
  } else {
    // State matches stable state, reset debounce timer
    lastButtonDebounceTime = 0;
  }
  
  // Read switch state
  switchReading = digitalRead(switchPin);
  
  // Check if switch state has changed (for debouncing)
  if (switchReading != lastSwitchState) {
    lastSwitchDebounceTime = millis();
  }
  
  // If enough time has passed since last switch state change, update switch state
  if ((millis() - lastSwitchDebounceTime) > switchDebounceDelay) {
    if (switchReading != currentSwitchState) {
      currentSwitchState = switchReading;
      
      // Switch is ON when state is LOW (with pull-up configuration)
      if (currentSwitchState == LOW) {
        Serial.println("slideSwitch,on");
      } else {
        Serial.println("slideSwitch,off");
      }
    }
  }
  lastSwitchState = switchReading;
  
  // Read force sensor values
  forceSensor0Value = analogRead(forceSensor0Pin);
  forceSensor1Value = analogRead(forceSensor1Pin);
  
  // Check if force sensor 0 has changed significantly (>= 200)
  if (abs(forceSensor0Value - lastForceSensor0Value) >= forceSensorChangeThreshold) {
    Serial.print("forceSensor0,");
    Serial.println(forceSensor0Value);
    lastForceSensor0Value = forceSensor0Value;
  }
  
  // Check if force sensor 1 has changed significantly (>= 200)
  if (abs(forceSensor1Value - lastForceSensor1Value) >= forceSensorChangeThreshold) {
    Serial.print("forceSensor1,");
    Serial.println(forceSensor1Value);
    lastForceSensor1Value = forceSensor1Value;
  }
  
  // Button state is checked every loop iteration for maximum responsiveness
}


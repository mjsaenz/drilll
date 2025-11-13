/*
  DF9-16 Force Sensor Test (Dual Sensor)
  This sketch reads two force sensors connected to analog pins A0 and A1
  and outputs the sensor readings to the serial monitor.
  
  Wiring:
  Sensor 1 (A0):
  - Force sensor terminal 1 -> 10kΩ resistor -> 5V
  - Force sensor terminal 1 -> Analog Pin A0
  - Force sensor terminal 2 -> GND
  
  Sensor 2 (A1):
  - Force sensor terminal 1 -> 10kΩ resistor -> 5V
  - Force sensor terminal 1 -> Analog Pin A1
  - Force sensor terminal 2 -> GND
  
  Circuit: Voltage divider
  - When no force: sensor resistance is high, voltage at analog pin is high
  - When force applied: sensor resistance decreases, voltage at analog pin decreases
*/

const int sensorPin1 = A0;      // Analog pin connected to first force sensor
const int sensorPin2 = A1;      // Analog pin connected to second force sensor
int sensorValue1 = 0;           // Raw analog reading for sensor 1 (0-1023)
int sensorValue2 = 0;           // Raw analog reading for sensor 2 (0-1023)
int lastSensorValue1 = 0;       // Previous sensor 1 reading for change detection
int lastSensorValue2 = 0;       // Previous sensor 2 reading for change detection
float voltage1 = 0.0;           // Calculated voltage for sensor 1 (0-5V)
float voltage2 = 0.0;           // Calculated voltage for sensor 2 (0-5V)
const int changeThreshold = 200; // Only output when value changes by this amount

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  
  // Configure analog pins (analog pins are analog by default, but explicit for clarity)
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  
  Serial.println("Dual force sensor test started!");
  Serial.println("Output will only appear when either sensor changes by 200 or more...");
  Serial.println("----------------------------------------------------------------------------");
  Serial.println("Sensor 1 (A0)          |  Sensor 2 (A1)");
  Serial.println("Raw | Voltage | Level   |  Raw | Voltage | Level");
  Serial.println("----------------------------------------------------------------------------");
  
  // Read initial sensor values
  lastSensorValue1 = analogRead(sensorPin1);
  lastSensorValue2 = analogRead(sensorPin2);
}

void loop() {
  // Read the analog values (0-1023)
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  
  // Check if either sensor has changed significantly (>= 200)
  bool sensor1Changed = abs(sensorValue1 - lastSensorValue1) >= changeThreshold;
  bool sensor2Changed = abs(sensorValue2 - lastSensorValue2) >= changeThreshold;
  
  if (sensor1Changed || sensor2Changed) {
    // Convert to voltage (0-5V)
    voltage1 = (sensorValue1 / 1023.0) * 5.0;
    voltage2 = (sensorValue2 / 1023.0) * 5.0;
    
    // Output sensor 1 readings
    Serial.print("  ");
    Serial.print(sensorValue1);
    Serial.print("  |  ");
    Serial.print(voltage1, 2);
    Serial.print("  |  ");
    Serial.print(getForceLevel(sensorValue1));
    Serial.print("   |  ");
    
    // Output sensor 2 readings
    Serial.print("  ");
    Serial.print(sensorValue2);
    Serial.print("  |  ");
    Serial.print(voltage2, 2);
    Serial.print("  |  ");
    Serial.println(getForceLevel(sensorValue2));
    
    // Update the last sensor values
    if (sensor1Changed) {
      lastSensorValue1 = sensorValue1;
    }
    if (sensor2Changed) {
      lastSensorValue2 = sensorValue2;
    }
  }
  
  // Small delay to reduce CPU usage
  delay(50);
}

// Helper function to get force level description
String getForceLevel(int value) {
  // Note: These thresholds may need adjustment based on your sensor
  if (value > 900) {
    return "None";
  } else if (value > 700) {
    return "Light";
  } else if (value > 500) {
    return "Medium";
  } else if (value > 300) {
    return "Strong";
  } else {
    return "Max";
  }
}


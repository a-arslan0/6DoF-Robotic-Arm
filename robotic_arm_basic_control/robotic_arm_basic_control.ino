#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo Pin Definitions
#define BASE_PIN        0
#define SHOULDER_PIN    1
#define ELBOW1_PIN      3
#define ELBOW2_PIN      4
#define WRIST_PIN       5
#define GRIPPER_PIN     6

void setup() {
  Serial.begin(9600);
  pwm.begin();
  
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50); 
  
  // Starting Positions (For the beginning of the video frame)
  pwm.writeMicroseconds(BASE_PIN, 1600);     // Base at center
  pwm.writeMicroseconds(SHOULDER_PIN, 1800); // Shoulder slightly down (to show initial movement)
  pwm.writeMicroseconds(ELBOW1_PIN, 1500);   // Elbow1 fully raised
  writeAngle(ELBOW2_PIN, 90);                // Elbow2 at center
  pwm.writeMicroseconds(WRIST_PIN, 1450);    // Wrist at center (fixed in this scenario)
  pwm.writeMicroseconds(GRIPPER_PIN, 1800);  // Gripper fully open (Updated)
  

  delay(4000); 
}

void loop() {
  // 1. SHOULDER: Move to fully raised position
  // Start (1800) -> Fully Raised (1400)
  smoothMoveUs(SHOULDER_PIN, 1800, 1400, 12); 
  delay(2000); // Wait 2 seconds after each movement

  // 2. BASE: Center -> Far Right -> Far Left -> Center
  smoothMoveUs(BASE_PIN, 1600, 2200, 10); // Center to right
  smoothMoveUs(BASE_PIN, 2200, 1000, 10); // Right to left
  smoothMoveUs(BASE_PIN, 1000, 1600, 10); // Left to center
  delay(2000);

  // 3. SHOULDER: Top -> Down -> Top Again
  smoothMoveUs(SHOULDER_PIN, 1400, 2300, 10); // Move down
  smoothMoveUs(SHOULDER_PIN, 2300, 1400, 10); // Move up
  delay(2000);

  // 4. ELBOW 1: Top (1500) -> Bottom (400) -> Top (1500)
  smoothMoveUs(ELBOW1_PIN, 1500, 400, 10); // Move down
  smoothMoveUs(ELBOW1_PIN, 400, 1500, 10); // Move up
  delay(2000);

  // 5. ELBOW 2: Center (90) -> Top (150) -> Bottom (30) -> Center (90)
  smoothMoveAngle(ELBOW2_PIN, 90, 150, 30); // Move up
  smoothMoveAngle(ELBOW2_PIN, 150, 30, 30); // Move down
  smoothMoveAngle(ELBOW2_PIN, 30, 90, 30);  // Return to center
  delay(2000);

  // 6. BASE (2nd Time): Center -> Far Right -> Far Left -> Center
  smoothMoveUs(BASE_PIN, 1600, 2200, 10); // Center to right
  smoothMoveUs(BASE_PIN, 2200, 1000, 10); // Right to left
  smoothMoveUs(BASE_PIN, 1000, 1600, 10); // Left to center
  delay(2000);

  // 7. BASE: Center -> Far Left (Position before gripper closes)
  smoothMoveUs(BASE_PIN, 1600, 1000, 10); // Move left
  delay(2000);

  // 8. GRIPPER: Fully Close -> Fully Open -> Fully Close
  smoothMoveUs(GRIPPER_PIN, 1800, 2200, 10); // Fully close (Updated)
  smoothMoveUs(GRIPPER_PIN, 2200, 1800, 10); // Fully open (Updated)
  smoothMoveUs(GRIPPER_PIN, 1800, 2200, 10); // Fully close again (Updated)
  
  delay(6000); 
  
  // --- RESET SYSTEM TO INITIAL STATE BEFORE LOOP RESTARTS ---
  // If you want to re-record, the robot slowly returns to its initial position.
  smoothMoveUs(GRIPPER_PIN, 2200, 1800, 10); // Open gripper again
  smoothMoveUs(BASE_PIN, 1000, 1600, 10);    // Move base to center
  smoothMoveUs(SHOULDER_PIN, 1400, 1800, 10); // Lower shoulder to start position
  delay(3000); 
}

// =========================================================================
// HELPER FUNCTIONS (Smooth Movement with Delay)
// =========================================================================

void smoothMoveUs(uint8_t pin, uint16_t startUs, uint16_t endUs, int speedDelay) {
  if (startUs < endUs) {
    for (uint16_t currentUs = startUs; currentUs <= endUs; currentUs += 5) {
      pwm.writeMicroseconds(pin, currentUs);
      delay(speedDelay);
    }
  } else {
    for (uint16_t currentUs = startUs; currentUs >= endUs; currentUs -= 5) {
      pwm.writeMicroseconds(pin, currentUs);
      delay(speedDelay);
    }
  }
}

void writeAngle(uint8_t pin, int angle) {
  uint16_t mappedUs = map(angle, 0, 180, 500, 2500);
  pwm.writeMicroseconds(pin, mappedUs);
}

void smoothMoveAngle(uint8_t pin, int startAngle, int endAngle, int speedDelay) {
  if (startAngle < endAngle) {
    for (int currentAngle = startAngle; currentAngle <= endAngle; currentAngle++) {
      writeAngle(pin, currentAngle);
      delay(speedDelay);
    }
  } else {
    for (int currentAngle = startAngle; currentAngle >= endAngle; currentAngle--) {
      writeAngle(pin, currentAngle);
      delay(speedDelay);
    }
  }
}
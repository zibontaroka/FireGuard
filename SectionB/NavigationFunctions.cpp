#include "NavigationFunctions.h"
#include <Arduino.h>
#include "RoomNavigation.h"

// Motor Speed Settings
int baseSpeed = 150;
int turnSpeed = 70;

extern uint8_t targetRoom;

volatile int left = 0, cenLeft = 0, center = 0, cenRight = 0, right = 0;

void updateIRSensorsTask(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    left     = digitalRead(LEFT);
    cenLeft  = digitalRead(CEN_LEFT);
    center   = digitalRead(CENTER);
    cenRight = digitalRead(CEN_RIGHT);
    right    = digitalRead(RIGHT);

    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

// === Navigation Logic ===
void smartForward() {

  if (left == 1 && cenLeft == 1 && center == 1 && cenRight == 1 && right == 1) {
    stopMotors();
    delay(700);
  }

      //(center == 1) || 

  if ((cenLeft == 0 && center == 1 && cenRight == 0) ||
      (left == 0 && cenLeft == 1 && center == 1 && cenRight == 1 && right == 0) ||
      (left == 1 && cenLeft == 0 && center == 0 && cenRight == 0 && right == 1) ||
      (left == 1 && cenLeft == 1 && center == 1 && cenRight == 1 && right == 0) ||
      (left == 0 && cenLeft == 1 && center == 1 && cenRight == 1 && right == 1)) {
    moveForward();
  }
  else if ((center == 0 && cenRight == 1)||
           (cenLeft == 0 && center == 0 && cenRight == 1) ||
           (cenLeft == 0 && center == 1 && cenRight == 1)) {
    slightRight();
  }
  else if ((cenLeft == 1 && center == 0 )||
           (cenLeft == 1 && center == 1 && cenRight == 0) ||
           (cenLeft == 1 && center == 0 && cenRight == 0)) {
    slightLeft();
  }
  else if ((left == 1 && right == 0) ||
           (left == 1 && cenLeft == 1 && cenRight == 0 && right == 0)) {
    turnLeft();
  
  }
  else if ((left == 0 && right == 1) ||
           (left == 0 && cenLeft == 0 && cenRight == 1 && right == 1)) {
   turnRight();

  }

  else if (left == 0 && cenLeft == 0 && center == 0 && cenRight == 0 && right == 0){
    stopMotors();
    delay(800);
  }


  else{
    turnRight();
  }

}
 
// === Movement Functions ===

void moveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);  // Left motor forward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);  // Right motor forward
  analogWrite(ENA, baseSpeed);  // Right motor
  analogWrite(ENB, baseSpeed);  // Left motor
}

void moveReverse() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, 60);
  analogWrite(ENB, 60);
}

void slightRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, turnSpeed);    // Right motor slower
  analogWrite(ENB, baseSpeed);    // Left motor normal
}

void slightLeft() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, baseSpeed);    // Right motor normal
  analogWrite(ENB, turnSpeed);    // Left motor slower
}

void turnLeft() {
  stopMotors();
  delay(100);
  while (center == 0) {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // Left forward
    digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);  // Right backward
    analogWrite(ENA, baseSpeed);  // Right
    analogWrite(ENB, baseSpeed);  // Left
  }
  stopMotors();
 delay(50);
}

void turnRight() {
  stopMotors();
  delay(100);
  while (center == 0) {
    digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  // Left backward
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // Right forward
    analogWrite(ENA, baseSpeed);
    analogWrite(ENB, baseSpeed);
  }
  stopMotors();
  delay(50);
}


void turnL() {
  stopMotors();
  delay(100);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // Left forward
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);  // Right backward
  analogWrite(ENA, baseSpeed);  // Right
  analogWrite(ENB, turnSpeed);  // Left

}


void turnR() {
  stopMotors();
  delay(100);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  // Left backward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // Right forward
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, baseSpeed);

}

void junctionLeft(){
  stopMotors();
  delay(100);

  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // Left forward
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);  // Right backward
  analogWrite(ENA, baseSpeed);  // Right
  analogWrite(ENB, turnSpeed);  // Left

  delay(1450);

}

void junctionRight() {
  stopMotors();
  delay(100);  // Small pause before turning

  // Start turning
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  // Left motor backward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // Right motor forward
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, baseSpeed);

  delay(1450);  // ← This is how long the turn should last

  stopMotors(); // Stop after turn completes
}



void makeUTurn() {
  stopMotors();
  delay(100);
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  // Left backward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // Right forward
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);

  delay(1000);

  // turnRight or turnLeft in place
  turnRight();  // or turnLeft(); depending on which way is easier

  stopMotors();
  delay(100);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(1); // Ensure PWM drops before brake
  digitalWrite(IN1, HIGH); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, HIGH);
}



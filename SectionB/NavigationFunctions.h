#ifndef NAVIGATION_FUNCTIONS_H
#define NAVIGATION_FUNCTIONS_H

#include <cstddef> 

// Motor Control Pins (ESP32) and TB6612FNG

#define ENA 14   // PWMA 
#define IN1 13   // AIN2 
#define IN2 12   // AIN1 

#define STBY 5

#define IN3 18   // BIN1 
#define IN4 19   // BIN2 
#define ENB 4    // PWMB 

// IR Sensor Pins (ESP32)
#define LEFT 32
#define CEN_LEFT 33
#define CENTER 25
#define CEN_RIGHT 26
#define RIGHT 27

extern int targetRoom;  
// Motor Speed Settings
extern int baseSpeed;
extern int turnSpeed;

// Function Prototypes
void smartForward();
void moveForward();

void moveReverse();

void slightRight();
void slightLeft();

void turnLeft();
void turnRight();

void stopMotors();

void turnL();
void turnR();

void junctionRight();
void junctionLeft();

void makeUTurn();

extern volatile int left, cenLeft, center, cenRight, right;

//---- FreeRTOS Task Prototypes
//extern void (*junctionAction)();

//void junctionDetectionTask(void *pvParameters);
void updateIRSensorsTask(void *pvParameters);


#endif // NAVIGATION_FUNCTIONS_H

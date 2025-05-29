#ifndef FIRE_STATUS_MANAGER_H
#define FIRE_STATUS_MANAGER_H

#include <Arduino.h>

// Fire sensor input pin mapping
#define FIRE_PIN_ROOM_11 34
#define FIRE_PIN_ROOM_12 35
#define FIRE_PIN_ROOM_30 36
#define FIRE_PIN_ROOM_31 39

// External variable declarations
extern bool fireRoom11;
extern bool fireRoom12;
extern bool fireRoom30;
extern bool fireRoom31;

extern bool fireStatus;
extern int currentFireRoom;

// Function declarations
void setupFireInputs();
void updateFireStatus();

#endif

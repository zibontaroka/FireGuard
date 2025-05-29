#include "FireStatusManager.h"

// Global flags
bool fireRoom11 = false;
bool fireRoom12 = false;
bool fireRoom30 = false;
bool fireRoom31 = false;

bool fireStatus = false;

int currentFireRoom = 0;

void setupFireInputs() {
  pinMode(FIRE_PIN_ROOM_11, INPUT);
  pinMode(FIRE_PIN_ROOM_12, INPUT);
  pinMode(FIRE_PIN_ROOM_30, INPUT);
  pinMode(FIRE_PIN_ROOM_31, INPUT);
}



void updateFireStatus() {
  // Read sensor inputs
  fireRoom11 = digitalRead(FIRE_PIN_ROOM_11) == HIGH;
  fireRoom12 = digitalRead(FIRE_PIN_ROOM_12) == HIGH;
  fireRoom30 = digitalRead(FIRE_PIN_ROOM_30) == HIGH;
  fireRoom31 = digitalRead(FIRE_PIN_ROOM_31) == HIGH;

  // Update fireStatus based on any fire
  fireStatus = fireRoom11 || fireRoom12 || fireRoom30 || fireRoom31;

  // If currentFireRoom is still active, keep it locked
  if (currentFireRoom != 0) {
    bool stillBurning = false;
    switch (currentFireRoom) {
      case 11: stillBurning = fireRoom11; break;
      case 12: stillBurning = fireRoom12; break;
      case 30: stillBurning = fireRoom30; break;
      case 31: stillBurning = fireRoom31; break;
    }

    if (!stillBurning) {
      currentFireRoom = 0; // release lock if fire gone
    }
  }

  // If currentFireRoom is 0, choose the highest-priority burning room
  if (currentFireRoom == 0) {
    if (fireRoom31) currentFireRoom = 31;
    else if (fireRoom12) currentFireRoom = 12;
    else if (fireRoom30) currentFireRoom = 30;
    else if (fireRoom11) currentFireRoom = 11;
  }
}

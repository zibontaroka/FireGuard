#ifndef SIM800L_MANAGER_H
#define SIM800L_MANAGER_H

#include <Arduino.h>

extern HardwareSerial sim800l;
void playOwnerAudio();
void playFireAudio();
void initSIM800L();
void checkSIM800L();
void callOwner();
void callFireService();
void updateCallHandling();
enum CallState {
  CALL_IDLE,
  CALLING_OWNER,
  WAITING_OWNER_RESPONSE,
  OWNER_CALL_ENDED,
  WAITING_BEFORE_FIRE_CALL,
  CALLING_FIRE,
  WAITING_FIRE_RESPONSE,
  FIRE_CALL_ENDED,
  DONE
};

extern String fireRoom;

extern CallState callState;
extern const char* ownerNumber;
extern const char* fireServiceNumber;
extern String currentCallNumber;
extern bool receivedPrinted;
extern unsigned long waitStartTime;

#endif

#ifndef RFID_READER_H
#define RFID_READER_H

#include <Arduino.h>

// Define a function type for tag callbacks
typedef void (*RFIDCallback)(unsigned long tagID);

// Setup function that accepts a callback
void setupRFIDReader(RFIDCallback callback);

#endif

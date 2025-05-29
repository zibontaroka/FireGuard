#include "FireStatusManager.h"
#include "SIM800LManager.h"
#include "DFPlayerHandler.h"
#include "PhoneEditor.h"

HardwareSerial sim800l(2);  // UART2 for SIM800L
const char* ownerNumber = "01827398815";
const char* fireServiceNumber = "01309179212";

CallState callState = CALL_IDLE;
String currentCallNumber = "";
unsigned long waitStartTime = 0;
bool receivedPrinted = false;

String fireRoom = ""; 


void updateCallHandling() {

  if (!fireStatus && callState != CALL_IDLE) {
    callState = CALL_IDLE;
    currentFireRoom = 0;
    fireRoom = "";
    Serial.println("🔥 Fire cleared. System reset for next detection.");
  }

  // Step 1: Check real fire data and set currentFireRoom once
  if (fireStatus ) { 
  
    if (fireRoom31) currentFireRoom = 31;
    else if (fireRoom12) currentFireRoom = 12;
    else if (fireRoom30) currentFireRoom = 30;
    else if (fireRoom11) currentFireRoom = 11;

    if (currentFireRoom != 0 && callState == CALL_IDLE) {
      fireRoom = "room" + String(currentFireRoom);
      callOwner();
    }
  }

  // Wait before calling fire service
  if (callState == WAITING_BEFORE_FIRE_CALL) {
    unsigned long elapsed = millis() - waitStartTime;
    if (elapsed >= 5000) {
       Announcement();
      callFireService();
    }
  }

  // Final state cleanup
  if (callState == FIRE_CALL_ENDED) {
    callState = DONE;
    Serial.println("✔️ Both calls completed.");
    fireRoom = "";  // Clear fire room
  }



}



/*

void updateCallHandling() {
  // Test input for fire simulation
  if (Serial.available()) {
    char c = Serial.read();
    if (callState == CALL_IDLE) {
      if (c == 'a') {
        fireRoom = "room11";
        callOwner();
      } else if (c == 'b') {
        fireRoom = "room12";
        callOwner();
      } else if (c == 'c') {
        fireRoom = "room30";
        callOwner();
      } else if (c == 'd') {
        fireRoom = "room31";
        callOwner();
      }
    }
  }

  // Wait before calling fire service
  if (callState == WAITING_BEFORE_FIRE_CALL) {
    unsigned long elapsed = millis() - waitStartTime;
    if (elapsed >= 5000) {
      callFireService();
    }
  }

  // Final state cleanup
  if (callState == FIRE_CALL_ENDED) {
    callState = DONE;
    Serial.println("✔️ Both calls completed.");
    fireRoom = "";  // Clear fire room
  }
}
*/


void initSIM800L() {
  sim800l.begin(9600, SERIAL_8N1, 16, 17);  // TX=16, RX=17
  delay(1000);
  Serial.println("Initializing SIM800L...");
  sim800l.println("AT");
  delay(500);
  while (sim800l.available()) {
    Serial.println("SIM800L: " + sim800l.readString());
  }
  sim800l.println("AT+CLCC=1");
  delay(500);
  while (sim800l.available()) {
    Serial.println("SIM800L: " + sim800l.readString());
  }
  sim800l.println("ATE0");
  delay(500);
  while (sim800l.available()) {
    Serial.println("SIM800L: " + sim800l.readString());
  }

}




void callOwner() {
  currentCallNumber = ownerNumber;
  sim800l.println("ATD" + String(ownerNumber) + ";");
  Serial.println("Calling owner...");
  callState = WAITING_OWNER_RESPONSE;
  receivedPrinted = false;
}

void callFireService() {
  delay(2000);
  Serial.println("Preparing to call fire service...");
  while (sim800l.available()) {
    sim800l.read(); // Clear buffer
  }
  sim800l.println("ATH");
  delay(1000);
  sim800l.println("AT");
  delay(500);
  String atResponse = "";
  while (sim800l.available()) {
    atResponse += sim800l.readString();
  }
  Serial.println("AT Response: " + atResponse);
  if (atResponse.indexOf("OK") == -1) {
    Serial.println("SIM800L not ready, retrying initialization...");
    sim800l.println("AT+CLCC=1");
    delay(500);
    while (sim800l.available()) {
      Serial.println("SIM800L: " + sim800l.readString());
    }
  }
  currentCallNumber = fireServiceNumber;
  sim800l.println("ATD" + String(fireServiceNumber) + ";");
  Serial.println("Calling fire service...");
  callState = WAITING_FIRE_RESPONSE;
  receivedPrinted = false;
}
void checkSIM800L() {
  static String response = "";
  while (sim800l.available()) {
    char c = sim800l.read();
    response += c;
    if (c == '\n') {
      response.trim();
      Serial.println("SIM800L Response: " + response);
      
      // Call Received
      if (response.startsWith("+CLCC:") && response.indexOf(",0,0,0,0") != -1) {
        if (!receivedPrinted) {
          if (currentCallNumber == ownerNumber) {
            Serial.println("📞 Owner call received");
            playOwnerAudio();  // অডিও চালাও
          } else if (currentCallNumber == fireServiceNumber) {
            Serial.println("🚒 Fire service call received");
            playFireAudio();   // অডিও চালাও
          }
          receivedPrinted = true;
        }
      }

      // Call Ended
      if (response.indexOf("NO CARRIER") != -1 || response.indexOf("BUSY") != -1 || 
          response.indexOf("ERROR") != -1 || response.indexOf("NO ANSWER") != -1) {
        Serial.println("❌ Call ended with: " + response);
        if (callState == WAITING_OWNER_RESPONSE) {
          callState = WAITING_BEFORE_FIRE_CALL;
          waitStartTime = millis();
        } else if (callState == WAITING_FIRE_RESPONSE) {
          callState = FIRE_CALL_ENDED;
        }
      }

      response = "";
    }
  }
}


void playOwnerAudio() {
  if (fireRoom == "room11") room11Owner();
  else if (fireRoom == "room12") room12Owner();
  else if (fireRoom == "room30") room30Owner();
  else if (fireRoom == "room31") room31Owner();
}

void playFireAudio() {
  if (fireRoom == "room11") room11fireservice();
  else if (fireRoom == "room12") room12fireservice();
  else if (fireRoom == "room30") room30fireservice();
  else if (fireRoom == "room31") room31fireservice();
}


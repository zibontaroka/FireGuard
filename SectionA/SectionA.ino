#include <Keypad.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ESPNowCommA.h>
#include <SIM800LManager.h>
#include <DFPlayerHandler.h>
#include "PhoneEditor.h"
#include "FireStatusManager.h"

// Global variables
char key = '\0';
String mode = "IDLE";
String lastEvent = "No Fire";
String gsm = "OK";
String esp = "OK";
String dfp = "OK";
int batteryPercent = 0;
int waterPercent = 0;
bool fireDetected = false;

String commandBuffer = "";
uint16_t NAVY = 0; // Initialized in setup()
bool commandActivated = false;
bool isEditing = false;
String editingField = "";
String tempNumber = "";

// Previous state variables
int prevBatteryPercent = -1;
int prevWaterPercent = -1;
bool prevFireStatus = false;
String prevMode = "";
int prevCurrentFireRoom = -1;
String prevLastEvent = "";
String prevGsm = "";
String prevEsp = "";
String prevDfp = "";
String prevFooterMsg = "";
uint16_t prevFooterColor = 0;




void setup() {
  Serial.begin(115200);
  delay(1000); // Ensure stable serial initialization

  // TFT and Keypad initialization
  NAVY = tft.color565(0, 0, 128); // Initialize NAVY color
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(NAVY);

  showStartupScreen();
  tft.fillScreen(NAVY);
  
  drawTopBar(batteryPercent, waterPercent, fireStatus);
  drawMiddleSection(mode, ownerNumber, fireServiceNumber, currentFireRoom, lastEvent, gsm, esp, dfp);
  setupKeypadAndBuzzer();

  // Fire, ESPNow, SIM800L, and DFPlayer initialization
  setupFireInputs();
  setupESPNow();
  initSIM800L();
  setupDFPlayer();
}

void loop() {
  // Keypad and display handling
  handleKeypad();

  // Update top bar if values changed
  if (batteryPercent != prevBatteryPercent || waterPercent != prevWaterPercent || fireStatus != prevFireStatus) {
    updateTopBar(batteryPercent, waterPercent, fireStatus);
    prevBatteryPercent = batteryPercent;
    prevWaterPercent = waterPercent;
    prevFireStatus = fireStatus;
  }

  // Update middle section if something changed
  if (mode != prevMode) {
    updateMode(mode);
    prevMode = mode;
  }
  if (currentFireRoom != prevCurrentFireRoom) {
    updateRoom(currentFireRoom);
    prevCurrentFireRoom = currentFireRoom;
  }
  if (lastEvent != prevLastEvent) {
    updateLastEvent(lastEvent);
    prevLastEvent = lastEvent;
  }
  if (gsm != prevGsm) {
    updateGSM(gsm);
    prevGsm = gsm;
  }
  if (esp != prevEsp) {
    updateESP(esp);
    prevEsp = esp;
  }
  if (dfp != prevDfp) {
    updateDFP(dfp);
    prevDfp = dfp;
  }

  // Fire status and communication handling
  updateFireStatus(); // Update all fire flags and currentFireRoom
  sendFireCommand(currentFireRoom, fireStatus);
  updateCallHandling();
  checkSIM800L();
}
#ifndef PHONE_EDITOR_H
#define PHONE_EDITOR_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Pin definitions for TFT
#define TFT_CS     18
#define TFT_RST    21
#define TFT_DC     19
#define TFT_MOSI   22
#define TFT_SCLK   23

// Pin definitions for Keypad
#define ROWS 4
#define COLS 4
#define BUZZER_PIN 2

// Screen dimensions
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128
#define TOP_BAR_HEIGHT 17

// External variables
extern Adafruit_ST7735 tft;
extern char key;
extern String mode;
extern int currentFireRoom;
extern String lastEvent;
extern String gsm;
extern String esp;
extern String dfp;
extern bool fireStatus;
extern int batteryPercent;
extern int waterPercent;
extern bool fireDetected;
extern const char* ownerNumber;
extern const char* fireServiceNumber;
extern String commandBuffer;
extern uint16_t NAVY;
extern bool commandActivated;
extern bool isEditing;
extern String editingField;
extern String tempNumber;
extern int prevBatteryPercent;
extern int prevWaterPercent;
extern bool prevFireStatus;
extern String prevMode;
extern int prevCurrentFireRoom;
extern String prevLastEvent;
extern String prevGsm;
extern String prevEsp;
extern String prevDfp;
extern String prevFooterMsg;
extern uint16_t prevFooterColor;

// Keypad configuration
extern char keys[ROWS][COLS];
extern byte rowPins[ROWS];
extern byte colPins[COLS];

// Function declarations
void drawTopBar(int batteryPercent, int waterPercent, bool fireStatus);
void updateTopBar(int batteryPercent, int waterPercent, bool fireStatus); // Added
void drawMiddleSection(String mode, const char* ownerNumber, const char* fireServiceNumber, int currentFireRoom, String lastEvent, String gsm, String esp, String dfp);
void updateMode(String mode); // Added
void updateRoom(int currentFireRoom); // Added
void updateLastEvent(String lastEvent); // Added
void updateGSM(String gsm); // Added
void updateESP(String esp); // Added
void updateDFP(String dfp); // Added
void updateOwnerNumber(const char* ownerNumber); // Added
void updateFireNumber(const char* fireServiceNumber); // Added
void drawFooter(String statusMsg, uint16_t color);
void showStartupScreen();
void showHomeScreen();
void setupKeypadAndBuzzer();
void beep();
void handleKeypad();
void showEditingScreen();
void updateNumberDisplay();
void showPhoneNumberEditor();
void handleKeypadInput(char key);
void startEditing(String fieldName);

#endif
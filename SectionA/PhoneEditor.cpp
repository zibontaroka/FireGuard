#include "PhoneEditor.h"
#include <Keypad.h>

// Pin definitions for TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Keypad configuration
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {32, 33, 14, 12};
byte colPins[COLS] = {13, 5, 4, 15};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void drawTopBar(int batteryPercent, int waterPercent, bool fireStatus) {
  tft.fillRect(0, 0, SCREEN_WIDTH, TOP_BAR_HEIGHT, NAVY);
  tft.drawLine(44, 2, 44, 14, ST7735_WHITE);
  tft.drawLine(45, 2, 45, 14, ST7735_WHITE);
  tft.drawLine(114, 2, 114, 14, ST7735_WHITE);
  tft.drawLine(115, 2, 115, 14, ST7735_WHITE);

  for (int i = 0; i < 2; i++) {
    tft.drawRect(i, i, SCREEN_WIDTH - (i * 2), TOP_BAR_HEIGHT - (i * 2), ST7735_WHITE);
  }

  tft.setCursor(5, 5);
  tft.setTextColor(ST7735_CYAN);
  tft.setTextSize(1);
  tft.print("W:"); tft.print(waterPercent); tft.print("%");

  String fireText = fireStatus ? "FIRE: ON" : "FIRE: OFF";
  int16_t x1, y1; uint16_t w, h;
  tft.getTextBounds(fireText, 0, 0, &x1, &y1, &w, &h);
  tft.setCursor((SCREEN_WIDTH - w) / 2, 5);
  tft.setTextColor(ST7735_YELLOW);
  tft.print(fireText);

  tft.setCursor(SCREEN_WIDTH - 40, 5);
  tft.setTextColor(ST7735_GREEN);
  tft.print("B:"); tft.print(batteryPercent); tft.print("%");
}

void updateTopBar(int batteryPercent, int waterPercent, bool fireStatus) {
  // Update waterPercent
  tft.fillRect(5, 5, 40, 10, NAVY);
  tft.setCursor(5, 5);
  tft.setTextColor(ST7735_CYAN);
  tft.setTextSize(1);
  tft.print("W:"); tft.print(waterPercent); tft.print("%");

  // Update fireStatus
  String fireText = fireStatus ? "FIRE: ON" : "FIRE: OFF";
  int16_t x1, y1; uint16_t w, h;
  tft.getTextBounds(fireText, 0, 0, &x1, &y1, &w, &h);
  tft.fillRect((SCREEN_WIDTH - w) / 2, 5, w, 10, NAVY);
  tft.setCursor((SCREEN_WIDTH - w) / 2, 5);
  tft.setTextColor(ST7735_YELLOW);
  tft.print(fireText);

  // Update batteryPercent
  tft.fillRect(SCREEN_WIDTH - 40, 5, 35, 10, NAVY);
  tft.setCursor(SCREEN_WIDTH - 40, 5);
  tft.setTextColor(ST7735_GREEN);
  tft.print("B:"); tft.print(batteryPercent); tft.print("%");
}

void drawMiddleSection(String mode, const char* ownerNumber, const char* fireServiceNumber, int currentFireRoom, String lastEvent, String gsm, String esp, String dfp) {
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.fillRect(0, TOP_BAR_HEIGHT, SCREEN_WIDTH, 86, NAVY);
  tft.setCursor(5, 22); tft.print("Mode: "); tft.print(mode);
  tft.setCursor(5, 32); tft.print("Room: "); tft.print(currentFireRoom);
  tft.setCursor(5, 42); tft.print("Last: "); tft.print(lastEvent);
  tft.setCursor(5, 52); tft.print("GSM : "); tft.print(gsm);
  tft.setCursor(92, 52); tft.print("DFP : "); tft.print(dfp);
  tft.setCursor(5, 62); tft.print("Connect:"); tft.print(esp);
  tft.setCursor(5, 80); tft.print("Owner Cell: "); tft.print(ownerNumber);
  tft.setCursor(5, 90); tft.print("Emergency : "); tft.print(fireServiceNumber);
}

void updateMode(String mode) {
  tft.fillRect(35, 22, SCREEN_WIDTH - 35, 10, NAVY);
  tft.setCursor(35, 22);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(mode);
}

void updateRoom(int currentFireRoom) {
  tft.fillRect(35, 32, SCREEN_WIDTH - 35, 10, NAVY);
  tft.setCursor(35, 32);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(currentFireRoom);
}

void updateLastEvent(String lastEvent) {
  tft.fillRect(35, 42, SCREEN_WIDTH - 35, 10, NAVY);
  tft.setCursor(35, 42);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(lastEvent);
}

void updateGSM(String gsm) {
  tft.fillRect(35, 52, 50, 10, NAVY);
  tft.setCursor(35, 52);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(gsm);
}

void updateDFP(String dfp) {
  tft.fillRect(122, 52, 35, 10, NAVY);
  tft.setCursor(122, 52);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(dfp);
}

void updateESP(String esp) {
  tft.fillRect(45, 62, SCREEN_WIDTH - 45, 10, NAVY);
  tft.setCursor(45, 62);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(esp);
}

void updateOwnerNumber(const char* ownerNumber) {
  tft.fillRect(65, 80, SCREEN_WIDTH - 65, 10, NAVY);
  tft.setCursor(65, 80);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(ownerNumber);
}

void updateFireNumber(const char* fireServiceNumber) {
  tft.fillRect(65, 90, SCREEN_WIDTH - 65, 10, NAVY);
  tft.setCursor(65, 90);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print(fireServiceNumber);
}

void drawFooter(String statusMsg, uint16_t color) {
  tft.fillRect(0, SCREEN_HEIGHT - 25, SCREEN_WIDTH, 25, NAVY);
  tft.drawLine(0, SCREEN_HEIGHT - 24, SCREEN_WIDTH, SCREEN_HEIGHT - 24, ST7735_WHITE);

  int16_t x1, y1; uint16_t w, h;
  tft.getTextBounds(statusMsg, 0, 0, &x1, &y1, &w, &h);
  tft.setCursor((SCREEN_WIDTH - w) / 2, SCREEN_HEIGHT - 16);
  tft.setTextColor(color);
  tft.setTextSize(1);
  tft.print(statusMsg);
}

void showStartupScreen() {
  tft.fillScreen(NAVY);
  delay(500);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(3);
  tft.setCursor((SCREEN_WIDTH - 4 * 18) / 2, 24);
  tft.print("AGNI");

  delay(1000);
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.setCursor((SCREEN_WIDTH - 18 * 6) / 2, 110);
  tft.print("Made In Bangladesh");

  delay(500);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  String text = "Smart Fire Fighter Robot";
  int textWidth = text.length() * 6;
  int x = (SCREEN_WIDTH - textWidth) / 2;
  tft.setCursor(x, 60);
  tft.print(text);

  delay(1000);
  tft.setTextColor(ST7735_CYAN);
  tft.setTextSize(1);
  tft.setCursor((SCREEN_WIDTH - 13 * 6) / 2, 80);
  tft.print("Starting");

  for (int i = 0; i < 5; i++) {
    tft.print(".");
    delay(1000);
  }

  delay(1000);
}

void showHomeScreen() {
  drawTopBar(batteryPercent, waterPercent, fireStatus);
  drawMiddleSection(mode, ownerNumber, fireServiceNumber, currentFireRoom, lastEvent, gsm, esp, dfp);
  drawFooter("System Normal", ST7735_GREEN);

  prevBatteryPercent = batteryPercent;
  prevWaterPercent = waterPercent;
  prevFireStatus = fireStatus;
  prevMode = mode;
  prevCurrentFireRoom = currentFireRoom;
  prevLastEvent = lastEvent;
  prevGsm = gsm;
  prevEsp = esp;
  prevDfp = dfp;
  prevFooterMsg = "System Normal";
  prevFooterColor = ST7735_GREEN;
}

void setupKeypadAndBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void beep() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);
}

void handleKeypad() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    beep();
    handleKeypadInput(key);
  }
}

void showEditingScreen() {
  tft.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, ST7735_BLACK);

  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(20, 20);
  tft.print("EDITING ");
  if (editingField == "owner") tft.print("OWNER");
  else if (editingField == "fire") tft.print("Emergency");

  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(10, 50);
  tft.print("Number: ");
  tft.print(tempNumber);

  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(10, 110);
  tft.print("*Save");

  tft.setTextColor(ST7735_RED);
  tft.setCursor(45, 110);
  tft.print("#Cancel");

  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(115, 110);
  tft.print("*D Del");
}

void updateNumberDisplay() {
  tft.fillRect(50, 50, SCREEN_WIDTH - 50, 10, ST7735_BLACK);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(1);
  tft.setCursor(50, 50);
  tft.print(tempNumber);
}

void showPhoneNumberEditor() {
  tft.fillScreen(ST7735_BLACK);
  isEditing = false;
  editingField = "";
  tempNumber = "";

  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(1);
  tft.setCursor(20, 25);
  tft.print("PHONE NUMBER SETUP");

  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10, 45);
  tft.print("Owner Number: [A]");
  tft.setCursor(20, 55);
  tft.print(ownerNumber);

  tft.setCursor(10, 75);
  tft.print("Emergency   : [B]");
  tft.setCursor(20, 85);
  tft.print(fireServiceNumber);

  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(10, 115);
  tft.print("* Save");

  tft.setTextColor(ST7735_RED);
  tft.setCursor(100, 115);
  tft.print("# Cancel");
}

void handleKeypadInput(char key) {
  static char tempBuffer[12];
  if (!commandActivated) {
    if (key == '*' || key == '#' || (key >= '0' && key <= '9')) {
      commandBuffer += key;
      if (commandBuffer.length() > 5) commandBuffer.remove(0, 1);
    }
    if (commandBuffer == "*153#") {
      commandActivated = true;
      commandBuffer = "";
      showPhoneNumberEditor();
      Serial.println("Edit mode triggered by *153#");
    }
    return;
  }

  if (!isEditing) {
    if (key == 'A') {
      editingField = "owner";
      strcpy(tempBuffer, ownerNumber);
      tempNumber = tempBuffer;
      isEditing = true;
      Serial.println("Editing Owner Number");
      showEditingScreen();
    } else if (key == 'B') {
      editingField = "fire";
      strcpy(tempBuffer, fireServiceNumber);
      tempNumber = tempBuffer;
      isEditing = true;
      Serial.println("Editing Fire Service Number");
      showEditingScreen();
    }
  } else {
    if (key == '#') {
      isEditing = false;
      showPhoneNumberEditor();
      commandActivated = false;
      Serial.println("Edit cancelled");
      showHomeScreen();
    } else if (key == '*') {
      if (editingField == "owner") {
        ownerNumber = strdup(tempNumber.c_str());
        updateOwnerNumber(ownerNumber); // Update display
      } else if (editingField == "fire") {
        fireServiceNumber = strdup(tempNumber.c_str());
        updateFireNumber(fireServiceNumber); // Update display
      }
      isEditing = false;
      showHomeScreen();
      commandActivated = false;
      Serial.println("Number saved: " + tempNumber);
    } else if (key >= '0' && key <= '9') {
      if (tempNumber.length() < 11) tempNumber += key;
      Serial.println("Current number: " + tempNumber);
      updateNumberDisplay();
    } else if (key == 'D') {
      if (tempNumber.length() > 0) tempNumber.remove(tempNumber.length() - 1);
      Serial.println("Backspace, current number: " + tempNumber);
      updateNumberDisplay();
    }
  }
}

void startEditing(String fieldName) {
  editingField = fieldName;
  tempNumber = "";
  commandActivated = true;
  showEditingScreen();
}
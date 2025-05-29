#include "RFID_reader.h"
#include <HardwareSerial.h>

// Create a HardwareSerial instance on UART1
HardwareSerial RFIDSerial(1);
TaskHandle_t rfidTaskHandle = NULL;

// Internal variable to store callback
static RFIDCallback rfidCallback = NULL;

// FreeRTOS task to read RFID data
void rfidTask(void *pvParameters) {
  static byte buffer[14];
  static byte index = 0;

  for (;;) {
    while (RFIDSerial.available()) {
      byte b = RFIDSerial.read();

      if (b == 0x02) index = 0;  // Start byte
      if (index < sizeof(buffer)) {
        buffer[index++] = b;
      }

      if (b == 0x03 && index == 14) {  // End byte and full packet
        char tagHex[7] = {0};  // +1 for null terminator
        for (int i = 0; i < 6; i++) {
          tagHex[i] = buffer[i + 5];
        }

        unsigned long tagID = strtoul(tagHex, NULL, 16);

        // Invoke the callback if set
        if (rfidCallback) {
          rfidCallback(tagID);
        }

        index = 0;  // Ready for next tag
      }

      if (index >= sizeof(buffer)) {
        index = 0;  // Reset on overflow
      }
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);  // Yield to other tasks
  }
}

// Setup function with callback
void setupRFIDReader(RFIDCallback callback) {
  rfidCallback = callback;
  RFIDSerial.begin(9600, SERIAL_8N1, 23, -1); // RX = GPIO 23, no TX

  xTaskCreatePinnedToCore(
    rfidTask,
    "RFID Reader",
    2048,
    NULL,
    1,
    &rfidTaskHandle,
    1
  );
}

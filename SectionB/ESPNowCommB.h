#ifndef ESPNOW_COMMB_H
#define ESPNOW_COMMB_H

#include <esp_now.h>
#include <WiFi.h>

// Define packet types
#define PACKET_TYPE_COMMAND 1
#define PACKET_TYPE_STATUS 2

// Robot state definitions
#define STATE_IDLE 0
#define STATE_MOVING 1
#define STATE_EXTINGUISHING 2
#define STATE_REFILLING 3
#define STATE_RETURNING 4
#define STATE_ERROR 5
#define STATE_CHECKING 6
#define STATE_NAVIGATING 7
#define STATE_REFILLED 8

// Error codes
#define ERROR_NONE 0
#define ERROR_SENSOR 1
#define ERROR_MOTOR 2
#define ERROR_LOW_WATER 3
#define ERROR_COMMUNICATION 4

// Structure for Fire Command Packet (Section A -> Section B)
struct FireCommandPacket {
  uint8_t packetType;   // Packet type (1 = Command)
  uint8_t roomID;       // Room ID (1-255, 0 = Refill Station)
  uint8_t fireStatus;   // Fire status (0 = No fire, 1 = Fire detected)
  uint32_t timestamp;   // Unix timestamp
};

// Structure for Robot Status Packet (Section B -> Section A)
struct RobotStatusPacket {
  uint8_t packetType;   // Packet type (2 = Status)
  uint8_t roomID;       // Current room ID (0 = Refill Station)
  float waterLevel;     // Water level (%)
  uint8_t fireStatus;   // Fire status (0 = Extinguished, 1 = Burning, 2 = Checking)
  uint8_t robotState;   // Robot state (see STATE_ definitions)
  uint8_t errorCode;    // Error code (see ERROR_ definitions)
  uint32_t timestamp;   // Unix timestamp
};

// Global variables
extern FireCommandPacket fireCommand;
extern RobotStatusPacket robotStatus;

// Function prototypes
void setupESPNow();
void sendRobotStatus(uint8_t roomID, float waterLevel, uint8_t fireStatus, uint8_t robotState, uint8_t errorCode);
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len);

#endif
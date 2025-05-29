// Section B

#include "ESPNowCommB.h"

// ESP32 A MAC Address
uint8_t peerAddress[6] = {0x94, 0x54, 0xC5, 0xA8, 0x3D, 0x04};

// Data instances
FireCommandPacket fireCommand;
RobotStatusPacket robotStatus;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent: OK" : "Sent: Fail");
}

void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
  if (len == sizeof(FireCommandPacket)) {
    memcpy(&fireCommand, incomingData, sizeof(fireCommand));
    if (fireCommand.packetType == PACKET_TYPE_COMMAND) {
      Serial.println("Received Fire Command:");
      Serial.print("Room ID: "); Serial.println(fireCommand.roomID);
      Serial.print("Fire Status: "); Serial.println(fireCommand.fireStatus);
      Serial.print("Timestamp: "); Serial.println(fireCommand.timestamp);
    }
  }
}

void setupESPNow() {
  WiFi.mode(WIFI_STA);
  WiFi.setChannel(1);
  WiFi.begin();
  delay(500);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    while (1);
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Peer add failed");
    while (1);
  }
}

void sendRobotStatus(uint8_t roomID, float waterLevel, uint8_t fireStatus, uint8_t robotState, uint8_t errorCode) {
  robotStatus.packetType = PACKET_TYPE_STATUS;
  robotStatus.roomID = roomID;
  robotStatus.waterLevel = waterLevel;
  robotStatus.fireStatus = fireStatus;
  robotStatus.robotState = robotState;
  robotStatus.errorCode = errorCode;
  robotStatus.timestamp = millis() / 1000; // Simplified timestamp

  esp_now_send(peerAddress, (uint8_t *)&robotStatus, sizeof(robotStatus));
}
// Section A

#include "ESPNowCommA.h"

// ESP32 B MAC Address
uint8_t peerAddress[6] = {0x94, 0x54, 0xC5, 0xA8, 0x3D, 0x04};

// Data instances
FireCommandPacket fireCommand;
RobotStatusPacket robotStatus;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent: OK" : "Sent: Fail");
}

void OnDataRecv(const esp_now_recv_info *recv_info, const uint8_t *incomingData, int len) {
  if (len == sizeof(RobotStatusPacket)) {
    memcpy(&robotStatus, incomingData, sizeof(robotStatus));
    if (robotStatus.packetType == PACKET_TYPE_STATUS) {
      Serial.println("Received Robot Status:");
      Serial.print("Room ID: "); Serial.println(robotStatus.roomID);
      Serial.print("Water Level: "); Serial.println(robotStatus.waterLevel);
      Serial.print("Fire Status: "); Serial.println(robotStatus.fireStatus);
      Serial.print("Robot State: "); Serial.println(robotStatus.robotState);
      Serial.print("Error Code: "); Serial.println(robotStatus.errorCode);
      Serial.print("Timestamp: "); Serial.println(robotStatus.timestamp);
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

void sendFireCommand(uint8_t roomID, uint8_t fireStatus) {
  fireCommand.packetType = PACKET_TYPE_COMMAND;
  fireCommand.roomID = roomID;
  fireCommand.fireStatus = fireStatus;
  fireCommand.timestamp = millis() / 1000; // Simplified timestamp

  esp_now_send(peerAddress, (uint8_t *)&fireCommand, sizeof(fireCommand));
}
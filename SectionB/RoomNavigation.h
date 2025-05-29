#ifndef ROOM_NAVIGATION_H
#define ROOM_NAVIGATION_H

#include <Arduino.h> // For digitalWrite, delay, and pin definitions
#include <freertos/FreeRTOS.h> // For vTaskDelay and pdMS_TO_TICKS
#include "ESPNowCommB.h" // For FireCommandPacket definition

// Enum for room states (matches fireCommand.roomID)
enum RoomState : uint8_t {
    ROOM_0 = 0, // Refill Station
    ROOM_1 = 1,
    ROOM_2 = 2,
    ROOM_3 = 3,
    ROOM_4 = 4
};

// Enum for tag IDs (matches RFID tag values from SectionB_Robot.ino)
enum TagID : unsigned long {
    TAG_ROOM_0 = 959778,  // Room 0 (Refill Station)
    TAG_ROOM_1 = 574773,  // Room 1
    TAG_ROOM_2 = 306179,  // Room 2
    TAG_ROOM_3 = 548852,  // Room 3
    TAG_ROOM_4 = 240824,  // Room 4
    JUNCTION_1 = 675576,  // Junction 1
    JUNCTION_2 = 951479   // Junction 2
};

// External variable declarations
extern unsigned long Tag_no; // Current tag being read
extern bool tag0Read; // Flag for ROOM_0 tag
extern bool tag1Read; // Flag for ROOM_1 tag
extern bool tag2Read; // Flag for ROOM_2 tag
extern bool tag3Read; // Flag for ROOM_3 tag
extern bool tag4Read; // Flag for ROOM_4 tag
extern bool tagJ1Read; // Flag for Junction_1 tag
extern bool tagJ2Read; // Flag for Junction_2 tag
extern RoomState currentRoom; // Current room the robot is in
extern RoomState targetRoom; // Target room to navigate to
extern const int LED_PIN; // LED pin for feedback
extern FireCommandPacket fireCommand; // Use struct from ESPNowCommB.h

// Motor control function declarations (assumed to be defined elsewhere)
void smartForward();
void junctionRight();
void junctionLeft();
void turnR();
void turnL();
void moveForward();
void stopMotors();
void makeUTurn();

// Navigation function prototypes
void resetTagFlags();
void Room0_To_Room1();
void Room1_To_Room0();
void Room0_To_Room2();
void Room0_To_Room3();
void Room0_To_Room4();
void Room1_To_Room2();
void Room1_To_Room3();
void Room1_To_Room4();
void Room2_To_Room0();
void Room2_To_Room1();
void Room2_To_Room3();
void Room2_To_Room4();
void Room3_To_Room0();
void Room3_To_Room1();
void Room3_To_Room2();
void Room3_To_Room4();
void Room4_To_Room0();
void Room4_To_Room1();
void Room4_To_Room2();
void Room4_To_Room3();
void navigate();

#endif // ROOM_NAVIGATION_H
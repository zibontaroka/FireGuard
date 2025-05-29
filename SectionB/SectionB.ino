#include "RoomNavigation.h"
#include "ESPNowCommB.h"
#include "NavigationFunctions.h" // Adjust based on your project structure

// Define global variables (only if not defined in another .cpp file)
unsigned long Tag_no = 0;
bool tag0Read = false;
bool tag1Read = false;
bool tag2Read = false;
bool tag3Read = false;
bool tag4Read = false;
bool tagJ1Read = false;
bool tagJ2Read = false;
RoomState currentRoom = ROOM_0;
RoomState targetRoom = ROOM_0;
const int LED_PIN = 2; // Adjust to your actual LED pin
FireCommandPacket fireCommand;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    // Other setup code (e.g., Serial, ESP-Now, RFID initialization)
}

void loop() {
    navigate();
    // Other loop code
}

void navigate() {
    if (fireCommand.fireStatus == 1) {
        targetRoom = static_cast<RoomState>(fireCommand.roomID); // Cast roomID to RoomState
        if (currentRoom == ROOM_0 && targetRoom == ROOM_1) {
            Room0_To_Room1();
        }
        else if (currentRoom == ROOM_0 && targetRoom == ROOM_2) {
            Room0_To_Room2();
        }
        else if (currentRoom == ROOM_0 && targetRoom == ROOM_3) {
            Room0_To_Room3();
        }
        else if (currentRoom == ROOM_0 && targetRoom == ROOM_4) {
            Room0_To_Room4();
        }
        else if (currentRoom == ROOM_1 && targetRoom == ROOM_0) {
            Room1_To_Room0();
        }
        else if (currentRoom == ROOM_1 && targetRoom == ROOM_2) {
            Room1_To_Room2();
        }
        else if (currentRoom == ROOM_1 && targetRoom == ROOM_3) {
            Room1_To_Room3();
        }
        else if (currentRoom == ROOM_1 && targetRoom == ROOM_4) {
            Room1_To_Room4();
        }
        else if (currentRoom == ROOM_2 && targetRoom == ROOM_0) {
            Room2_To_Room0();
        }
        else if (currentRoom == ROOM_2 && targetRoom == ROOM_1) {
            Room2_To_Room1();
        }
        else if (currentRoom == ROOM_2 && targetRoom == ROOM_3) {
            Room2_To_Room3();
        }
        else if (currentRoom == ROOM_2 && targetRoom == ROOM_4) {
            Room2_To_Room4();
        }
        else if (currentRoom == ROOM_3 && targetRoom == ROOM_0) {
            Room3_To_Room0();
        }
        else if (currentRoom == ROOM_3 && targetRoom == ROOM_1) {
            Room3_To_Room1();
        }
        else if (currentRoom == ROOM_3 && targetRoom == ROOM_2) {
            Room3_To_Room2();
        }
        else if (currentRoom == ROOM_3 && targetRoom == ROOM_4) {
            Room3_To_Room4();
        }
        else if (currentRoom == ROOM_4 && targetRoom == ROOM_0) {
            Room4_To_Room0();
        }
        else if (currentRoom == ROOM_4 && targetRoom == ROOM_1) {
            Room4_To_Room1();
        }
        else if (currentRoom == ROOM_4 && targetRoom == ROOM_2) {
            Room4_To_Room2();
        }
        else if (currentRoom == ROOM_4 && targetRoom == ROOM_3) {
            Room4_To_Room3();
        }
        else {
            stopMotors();
        }
    }
    else {
        stopMotors();
    }
}
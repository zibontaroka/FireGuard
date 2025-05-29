#include "RoomNavigation.h"

void resetTagFlags() {
  tag0Read = false;
  tag1Read = false;
  tag2Read = false;
  tag3Read = false;
  tag4Read = false;
  tagJ1Read = false;
  tagJ2Read = false;
}

//================================ Room 0 TO Room 1 ===================================
void Room0_To_Room1() {
  if (Tag_no == TAG_ROOM_0 && !tag0Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag0Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag0Read && !tagJ1Read) {
    junctionRight();

    tagJ1Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == TAG_ROOM_1 && tag0Read && tagJ1Read && !tag1Read) {
    stopMotors();
    delay(4000);

    tag1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(3000));
    digitalWrite(LED_PIN, LOW);

    makeUTurn();
    
    currentRoom = ROOM_1;
    targetRoom = ROOM_0;

    resetTagFlags();
  }
  else {
    smartForward();
  }
}

//================================ Room 1 TO Room 0 ===================================
void Room1_To_Room0() {
  if (Tag_no == TAG_ROOM_1 && !tag1Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag1Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag1Read && !tagJ1Read) {
    junctionLeft();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_0 && tag1Read && tagJ1Read && !tag0Read) {
    stopMotors();
    tag0Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_0;
    targetRoom = ROOM_1;

    resetTagFlags();

    makeUTurn();
  }
  else {
    smartForward();
  }
}

//================================ Room 0 TO Room 2 ===================================
void Room0_To_Room2() {
  if (Tag_no == TAG_ROOM_0 && !tag0Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag0Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag0Read && !tagJ1Read) {
    moveForward();
    delay(1000);

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_2 && tag0Read && tagJ1Read && !tagJ2Read) {
    turnR();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_2 && tag0Read && tagJ1Read && tagJ2Read && !tag2Read) {
    stopMotors();
    tag2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_2;
    targetRoom = ROOM_0;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 0 TO Room 3 ===================================
void Room0_To_Room3() {
  if (Tag_no == TAG_ROOM_0 && !tag0Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag0Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag0Read && !tagJ1Read) {
    moveForward();
    delay(1000);

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_2 && tag0Read && tagJ1Read && !tagJ2Read) {
    turnL();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_3 && tag0Read && tagJ1Read && tagJ2Read && !tag3Read) {
    stopMotors();
    tag3Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_3;
    targetRoom = ROOM_0;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 0 TO Room 4 ===================================
void Room0_To_Room4() {
  if (Tag_no == TAG_ROOM_0 && !tag0Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag0Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag0Read && !tagJ1Read) {
    turnL();
    delay(1300);
    moveForward();
    delay(400);

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_4 && tag0Read && tagJ1Read && !tag4Read) {
    stopMotors();
    tag4Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_4;
    targetRoom = ROOM_0;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 1 TO Room 2 ===================================
void Room1_To_Room2() {
  if (Tag_no == TAG_ROOM_1 && !tag1Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag1Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag1Read && !tagJ1Read) {
    junctionRight();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_2 && tag1Read && tagJ1Read && !tagJ2Read) {
    turnR();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_2 && tag1Read && tagJ1Read && tagJ2Read && !tag2Read) {
    stopMotors();
    tag2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_2;
    targetRoom = ROOM_1;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 1 TO Room 3 ===================================
void Room1_To_Room3() {
  if (Tag_no == TAG_ROOM_1 && !tag1Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag1Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag1Read && !tagJ1Read) {
    junctionRight();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_2 && tag1Read && tagJ1Read && !tagJ2Read) {
    turnL();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_3 && tag1Read && tagJ1Read && tagJ2Read && !tag3Read) {
    stopMotors();
    tag3Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_3;
    targetRoom = ROOM_1;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 1 TO Room 4 ===================================
void Room1_To_Room4() {
  if (Tag_no == TAG_ROOM_1 && !tag1Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag1Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag1Read && !tagJ1Read) {
    moveForward();
    delay(1000);

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_4 && tag1Read && tagJ1Read && !tag4Read) {
    stopMotors();
    tag4Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_4;
    targetRoom = ROOM_1;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 2 TO Room 0 ===================================
void Room2_To_Room0() {
  if (Tag_no == TAG_ROOM_2 && !tag2Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag2Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_2 && tag2Read && !tagJ2Read) {
    turnL();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_1 && tag2Read && tagJ2Read && !tagJ1Read) {
    moveForward();
    delay(1000);

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_0 && tag2Read && tagJ2Read && tagJ1Read && !tag0Read) {
    stopMotors();
    tag0Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_0;
    targetRoom = ROOM_2;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 2 TO Room 1 ===================================
void Room2_To_Room1() {
  if (Tag_no == TAG_ROOM_2 && !tag2Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag2Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_2 && tag2Read && !tagJ2Read) {
    turnL();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_1 && tag2Read && tagJ2Read && !tagJ1Read) {
    junctionLeft();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_1 && tag2Read && tagJ2Read && tagJ1Read && !tag1Read) {
    stopMotors();
    tag1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_1;
    targetRoom = ROOM_2;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 2 TO Room 3 ===================================
void Room2_To_Room3() {
  if (Tag_no == TAG_ROOM_2 && !tag2Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag2Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_2 && tag2Read && !tagJ2Read) {
    moveForward();
    delay(1000);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_3 && tag2Read && tagJ2Read && !tag3Read) {
    stopMotors();
    tag3Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_3;
    targetRoom = ROOM_2;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 2 TO Room 4 ===================================
void Room2_To_Room4() {
  if (Tag_no == TAG_ROOM_2 && !tag2Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag2Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_2 && tag2Read && !tagJ2Read) {
    turnL();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_1 && tag2Read && tagJ2Read && !tagJ1Read) {
    junctionRight();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_4 && tag2Read && tagJ2Read && tagJ1Read && !tag4Read) {
    stopMotors();
    tag4Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_4;
    targetRoom = ROOM_2;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 3 TO Room 0 ===================================
void Room3_To_Room0() {
  if (Tag_no == TAG_ROOM_3 && !tag3Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag3Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_2 && tag3Read && !tagJ2Read) {
    turnR();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 

  else if (Tag_no == Junction_1 && tag3Read && tagJ2Read && !tagJ1Read) {
    moveForward();
    delay(1000);

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_0 && tag3Read && tagJ2Read && tagJ1Read && !tag0Read) {
    stopMotors();
    tag0Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_0;
    targetRoom = ROOM_3;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 3 TO Room 1 ===================================
void Room3_To_Room1() {
  if (Tag_no == TAG_ROOM_3 && !tag3Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag3Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_2 && tag3Read && !tagJ2Read) {
    turnR();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_1 && tag3Read && tagJ2Read && !tagJ1Read) {
    junctionLeft();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_1 && tag3Read && tagJ2Read && tagJ1Read && !tag1Read) {
    stopMotors();
    tag1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_1;
    targetRoom = ROOM_3;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 3 TO Room 2 ===================================
void Room3_To_Room2() {
  if (Tag_no == TAG_ROOM_3 && !tag3Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag3Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_2 && tag3Read && !tagJ2Read) {
    moveForward();
    delay(1000);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_2 && tag3Read && tagJ2Read && !tag2Read) {
    stopMotors();
    tag2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_2;
    targetRoom = ROOM_3;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 3 TO Room 4 ===================================
void Room3_To_Room4() {
  if (Tag_no == TAG_ROOM_3 && !tag3Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag3Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_2 && tag3Read && !tagJ2Read) {
    turnR();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_1 && tag3Read && tagJ2Read && !tagJ1Read) {
    junctionRight();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_4 && tag3Read && tagJ2Read && tagJ1Read && !tag4Read) {
    stopMotors();
    tag4Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_4;
    targetRoom = ROOM_3;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 4 TO Room 0 ===================================
void Room4_To_Room0() {
  if (Tag_no == TAG_ROOM_4 && !tag4Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag4Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag4Read && !tagJ1Read) {
    junctionRight();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_0 && tag4Read && tagJ1Read && !tag0Read) {
    stopMotors();
    tag0Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_0;
    targetRoom = ROOM_4;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 4 TO Room 1 ===================================
void Room4_To_Room1() {
  if (Tag_no == TAG_ROOM_4 && !tag4Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag4Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag4Read && !tagJ1Read) {
    moveForward();
    delay(1000);

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_1 && tag4Read && tagJ1Read && !tag1Read) {
    stopMotors();
    tag1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_1;
    targetRoom = ROOM_4;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 4 TO Room 2 ===================================
void Room4_To_Room2() {
  if (Tag_no == TAG_ROOM_4 && !tag4Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag4Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag4Read && !tagJ1Read) {
    junctionLeft();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_2 && tag4Read && tagJ1Read && !tagJ2Read) {
    turnR();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_2 && tag4Read && tagJ1Read && tagJ2Read && !tag2Read) {
    stopMotors();
    tag2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_2;
    targetRoom = ROOM_4;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

//================================ Room 4 TO Room 3 ===================================
void Room4_To_Room3() {
  if (Tag_no == TAG_ROOM_4 && !tag4Read) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);

    tag4Read = true;
    Tag_no = 0;
  } 
  else if (Tag_no == Junction_1 && tag4Read && !tagJ1Read) {
    junctionLeft();

    tagJ1Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == Junction_2 && tag4Read && tagJ1Read && !tagJ2Read) {
    turnL();
    delay(1300);
    moveForward();
    delay(400);

    tagJ2Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
  } 
  else if (Tag_no == TAG_ROOM_3 && tag4Read && tagJ1Read && tagJ2Read && !tag3Read) {
    stopMotors();
    tag3Read = true;
    Tag_no = 0;

    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_PIN, LOW);
    
    delay(3000);

    currentRoom = ROOM_3;
    targetRoom = ROOM_4;

    resetTagFlags();

    makeUTurn();
  } 
  else {
    smartForward();
  }
}

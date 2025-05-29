// DFPlayerHandler.cpp
#include "DFPlayerHandler.h"
#include <DFRobotDFPlayerMini.h>

const int RELAY_PIN = 25;

DFRobotDFPlayerMini player;

HardwareSerial mySerial(1); // GPIO 27=RX, 26=TX

void setupDFPlayer() {
  mySerial.begin(9600, SERIAL_8N1, 27, 26);   // GPIO 27=RX, 26=TX
  pinMode(RELAY_PIN, OUTPUT);
  if (player.begin(mySerial)) {
    Serial.println("DFPlayer OK");
    player.volume(30);
  } else {
    Serial.println("DFPlayer initialization failed!");
  }
}

// Other functions like ownerMessage(), fireserviceMessage(), etc.





void Announcement() {
  player.play(4);
  digitalWrite(RELAY_PIN, HIGH);
  delay(40700);
  Serial.println("Relay ON");

  digitalWrite(RELAY_PIN, LOW);

  Serial.println("Relay OFF");
}

void room11Owner() {
  player.play(2);
  delay(15420);
  player.play(5);
}

void room12Owner() {
  player.play(2);
  delay(15420);
  player.play(6);
}

void room30Owner() {
  player.play(2);
  delay(15420);
  player.play(7);
}

void room31Owner() {
  player.play(2);
  delay(15420);
  player.play(1);
}


void room11fireservice() {
  player.play(3);
  delay(26230);
  player.play(5);
}

void room12fireservice() {
  player.play(3);
  delay(26230);
  player.play(6);
}

void room30fireservice() {
  player.play(3);
  delay(26230);
  player.play(7);
}

void room31fireservice() {
  player.play(3);
  delay(26230);
  player.play(1);
}

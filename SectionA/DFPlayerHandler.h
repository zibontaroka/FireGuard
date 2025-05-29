#ifndef DFPLAYER_HANDLER_H
#define DFPLAYER_HANDLER_H

#include <HardwareSerial.h>


void setupDFPlayer();
void ownerMessage();
void fireserviceMessage();
void Announcement();

void room11Owner();
void room12Owner();
void room30Owner();
void room31Owner();

void room11fireservice();
void room12fireservice();
void room30fireservice();
void room31fireservice();


#endif // DFPLAYER_HANDLER_H

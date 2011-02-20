#ifndef MESSAGES_SEND_H
#define MESSAGES_SEND_H

#include "message.h"

message *send_message(int fd, const char *text, message *next_message);

#endif

#ifndef MESSAGES_CLOSE_H
#define MESSAGES_CLOSE_H

#include "message.h"

message *close_message(int fd, message *next_message);

#endif

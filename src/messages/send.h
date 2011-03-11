#ifndef MESSAGES_SEND_H
#define MESSAGES_SEND_H

#include "bstrlib.h"

#include "message.h"

message *send_message(int fd, bstring text, message *next_message);

#endif

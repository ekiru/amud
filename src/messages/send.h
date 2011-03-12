#ifndef MESSAGES_SEND_H
#define MESSAGES_SEND_H

#include "bstrlib.h"

#include "message.h"
#include "player.h"

message *send_message(player *recipient, bstring text, message *next_message);

#endif

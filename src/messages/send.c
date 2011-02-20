#include "messages/send.h"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

typedef struct {
    message msg;
    int fd;
    const char *text;
    size_t length;
    message *next;
} send_message_t;

static void send_message_handler(message *msgp) {
    send_message_t *msg = (send_message_t *) msgp;
    send(msg->fd, msg->text, msg->length, 0);
    message_queue(msg->next);
    free(msg);
}   

message *send_message(int fd, const char *text, message *next_message) {
    send_message_t *result = (send_message_t *) malloc(sizeof (*result));
    if (result) {
        result->msg.handle_message = &send_message_handler;
        result->fd = fd;
        result->text = text;
        result->length = strlen(text);
        result->next = next_message;
    }
    return (message *) result;
}

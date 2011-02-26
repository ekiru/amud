#include "messages/close.h"

#include <stdlib.h>
#include <unistd.h>

typedef struct {
	message msg;
	int fd;
	message *next;
} close_message_t;

static void close_message_handler(message *msgp) {
	close_message_t *msg = (close_message_t *) msgp;
	close(msg->fd);
	message_queue(msg->next);
	free(msg);
}

message *close_message(int fd, message *next_message) {
	close_message_t *result = (close_message_t *) malloc(sizeof (*result));
	if (result) {
		result->msg.handle_message = &close_message_handler;
		result->fd = fd;
		result->next = next_message;
	}
	return (message *) result;
}

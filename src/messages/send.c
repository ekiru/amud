#include "messages/send.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "error_status.h"

typedef struct {
	message msg;
	int fd;
	const char *text;
	size_t length;
	message *next;
} send_message_t;

static void send_message_handler(message *msgp) {
	send_message_t *msg = (send_message_t *) msgp;
	ssize_t bytes_sent = send(msg->fd, msg->text, msg->length, MSG_DONTWAIT);
	if (bytes_sent == msg->length) {
		message_queue(msg->next);
		free(msg);
	} else if (bytes_sent >= 0) {
		message *new_message = send_message(msg->fd, msg->text + bytes_sent, msg->next);
		if (!new_message)
			exit(ALLOCATION_ERROR);
		message_queue(new_message);
		free(msg);
	} else {
		switch (errno) {
		case EAGAIN: /* message didn't send due to it being a blocking operation. */
			message_queue(msgp);
			break;
		case ECONNRESET:
			/* need to work in handing of disconnections */
			free(msg);
			break;
		default:
			free(msg);
			break;
		}
	}
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

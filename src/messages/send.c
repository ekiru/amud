#include "messages/send.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "bstrlib.h"

#include "error_status.h"

typedef struct {
	message msg;
	player *recipient;
	bstring text;
	size_t offset;
	message *next;
} send_message_t;

static void free_send_message(send_message_t *msg) {
	if (bdestroy(msg->text) == BSTR_ERR)
		exit(BSTRING_ERROR);
}

static void send_message_handler(message *msgp) {
	send_message_t *msg = (send_message_t *) msgp;
	ssize_t bytes_sent = send(player_fd(msg->recipient), bdata(msg->text) + msg->offset, blength(msg->text) - msg->offset, MSG_DONTWAIT);
	if (bytes_sent == blength(msg->text) - msg->offset) {
		message_queue(msg->next);
		free_send_message(msg);
	} else if (bytes_sent >= 0) {
		msg->offset += bytes_sent;
		message_queue(msgp);
	} else {
		switch (errno) {
		case EAGAIN: /* message didn't send due to it being a blocking operation. */
			message_queue(msgp);
			break;
		case ECONNRESET:
			/* need to work in handing of disconnections */
			free_send_message(msg);
			break;
		default:
			free(msg);
			break;
		}
	}
}

message *send_message(player *recipient, bstring text, message *next_message) {
	send_message_t *result = (send_message_t *) malloc(sizeof (*result));
	if (result) {
		result->msg.handle_message = &send_message_handler;
		result->recipient = recipient;
		result->text = text;
		result->offset = 0;
		result->next = next_message;
	}
	return (message *) result;
}

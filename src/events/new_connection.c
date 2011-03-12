#include "events/new_connection.h"

#include <stdio.h>
#include <stdlib.h>

#include "bstrlib.h"

#include "error_status.h"
#include "io_util.h"
#include "message.h"
#include "messages/close.h"
#include "messages/send.h"
#include "player.h"

typedef struct {
	event ev;
	int fd;
} new_conn_event;

static unsigned long hits = 0;

static void handle_new_conn_event(event *evp) {
	new_conn_event *ev = (new_conn_event *) evp;
	bstring greeting, announcement;
	message *user_msg, *all_msg;
	player *pl;
	hits++;
	if ((greeting = bformat("Hello, you are user #%d.\n", hits)) == NULL)
		exit(ALLOCATION_ERROR);
	if ((user_msg = send_message(ev->fd, greeting, NULL)) == NULL)
	    exit(ALLOCATION_ERROR);
	message_queue(user_msg);

	if ((announcement = bformat("User #%d arrived.\n", hits)) == NULL)
		exit(ALLOCATION_ERROR);
	send_all(announcement);

	if ((pl = new_player(ev->fd, hits)) == NULL)
		exit(ALLOCATION_ERROR);
	add_player(pl);
	free(ev);
	printf("Hit %lu\n", hits);
}

event *new_connection_event(int connection_fd) {
	new_conn_event *result = (new_conn_event *) malloc(sizeof (*result));
	if (result) {
		result->ev.handle_event = &handle_new_conn_event;
		result->fd = connection_fd;
	}
	return (event *) result;
}

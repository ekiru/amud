#include "events/new_connection.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
	event ev;
	int fd;
} new_conn_event;

static unsigned long hits = 0;

static void handle_new_conn_event(event *evp) {
	new_conn_event *ev = (new_conn_event *) evp;
	char *msg = "Hello, world!";
	hits++;
	send(ev->fd, msg, strlen(msg), 0);
	close(ev->fd);
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

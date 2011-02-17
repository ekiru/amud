#include "listener_thread.h"

#include "error_status.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define LISTENER_BACKLOG_SIZE 10

static int open_socket(char *port) {
	struct addrinfo hints, *server_info, *p;
	int result = -1;

	memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port, &hints, &server_info)) {
		goto getaddrinfo_error;
	}

	for (p = server_info; p != NULL; p = p->ai_next) {
		if ((result = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			continue;
		}

		if (bind(result, p->ai_addr, p->ai_addrlen) == -1) {
			close(result);
			continue;
		}
	}

	freeaddrinfo(server_info);

	getaddrinfo_error:
	if (result == -1) exit(LISTENER_INIT_ERROR);

	if (listen(result, LISTENER_BACKLOG_SIZE) == -1) {
		close(result);
		exit(LISTENER_INIT_ERROR);
	}

	return result;
}

void *listener_thread_start(void *port) {
	int listener_fd;
	puts("Listener thread started.");

	listener_fd = open_socket((char *) port);

	for (;;) {
		int new_connection;
		if ((new_connection = accept(listener_fd, NULL, 0)) != -1) {
			send(new_connection, "Hello, world!", sizeof("Hello, world!"), 0);
			close(new_connection);
		}
	}

	puts("Listener thread exiting.");

	pthread_exit(NULL);
}


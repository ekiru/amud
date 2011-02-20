#include "io_thread.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "message.h"

void *io_thread_start(void *ignore) {
	puts("IO thread started.");
	for (;;) {
		message *msg = message_dequeue();
		if (msg != NULL) {
			msg->handle_message(msg);
		}
	}
	pthread_exit(NULL);
}

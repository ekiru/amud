#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "event_thread.h"
#include "io_thread.h"
#include "listener_thread.h"

#define EVENT_THREAD_COUNT 5
#define IO_THREAD_COUNT 5

#define THREAD_ERROR 1

int main(int argc, char **argv) {
	int i;
	pthread_t listener_thread,
	          event_threads[EVENT_THREAD_COUNT],
		  io_threads[IO_THREAD_COUNT];
	int port[1] = { 9000 };

	if (pthread_create(&listener_thread, NULL, listener_thread_start, (void *) port))
		goto thread_error;
	for (i = 0; i < EVENT_THREAD_COUNT; i++) {
		if (pthread_create(&event_threads[i], NULL, event_thread_start, NULL))
			goto thread_error;
	}
	for (i = 0; i < IO_THREAD_COUNT; i++) {
		if (pthread_create(&io_threads[i], NULL, io_thread_start, NULL))
			goto thread_error;
	}

	pthread_exit(NULL);

	thread_error:
	fprintf(stderr, "%s: something went wrong in pthreads\n", argv[0]);
	exit(THREAD_ERROR);
}

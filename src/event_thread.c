#include "event_thread.h"

#include <pthread.h>
#include <stdio.h>

void *event_thread_start(void *ignore) {
	puts("Event thread started.");
	pthread_exit(NULL);
}

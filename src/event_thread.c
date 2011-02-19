#include "event_thread.h"

#include "event.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *event_thread_start(void *ignore) {
	puts("Event thread started.");
	for (;;) {
		event *ev = event_dequeue();
		if (ev != NULL) {
			ev->handle_event(ev);
		}
	}
	pthread_exit(NULL);
}

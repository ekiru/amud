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
			event *new_event;
			if ((new_event = ev->handle_event(ev)) != NULL)
				event_queue(new_event);
		}
	}
	pthread_exit(NULL);
}

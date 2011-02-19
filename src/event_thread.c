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
			struct message *new_message;
			switch(ev->handle_event(ev, &new_event, &new_message)) {
			case FOLLOWUP_EVENT:
				event_queue(new_event);
				break;
			case FOLLOWUP_MESSAGE:
			    break;
			default:
			    break;
			}
		}
	}
	pthread_exit(NULL);
}

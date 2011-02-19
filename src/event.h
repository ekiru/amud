#ifndef EVENT_H
#define EVENT_H

typedef struct event {
	void (*handle_event)(struct event *);
} event;

event *event_dequeue(void);
int event_queue(event *ev);

#endif

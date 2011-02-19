#ifndef EVENT_H
#define EVENT_H

#include "followup.h"

struct message;

typedef struct event {
	followup_type (*handle_event)(struct event *,
                                  struct event **,
	                              struct message **);
} event;

event *event_dequeue(void);
int event_queue(event *ev);

#endif

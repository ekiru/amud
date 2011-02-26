#include "event.h"

#include "queue.h"

queue ev_queue = QUEUE_INITIALIZER;

event *event_dequeue(void) {
	return (event *) queue_dequeue(&ev_queue);
}
int event_queue(event * ev) {
	return queue_enqueue(&ev_queue, (void *) ev);
}

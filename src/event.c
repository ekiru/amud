#include "event.h"

#include <pthread.h>
#include <stdlib.h>

typedef struct queue_node queue_node;

typedef struct {
	queue_node *head, *tail;
} queue;

struct queue_node {
	event *ev;
	queue_node *next, *prev;
};

static queue_node *new_node(event *ev, queue_node *prev, queue_node *next) {
	queue_node *result = (queue_node *) malloc(sizeof (*result));
	if (result) {
		result->ev = ev;
		result->prev = prev;
		result->next = next;
	}
	return result;
}

queue ev_queue = { NULL, NULL };
pthread_mutex_t ev_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

int event_queue(event *ev) {
	int result = 0;
	pthread_mutex_lock(&ev_queue_mutex);
	if (ev_queue.head == NULL) {
		ev_queue.head = ev_queue.tail = new_node(ev, NULL, NULL);
		result = ev_queue.head != NULL;
		goto end;
	} else {
		queue_node *new_tail = new_node(ev, ev_queue.tail, NULL);
		if (result) {
			ev_queue.tail = new_tail;
			result = 1;
		}
	}

	end:
	pthread_mutex_unlock(&ev_queue_mutex);
	return result;
}

event *event_dequeue(void) {
	event *result = NULL;
	queue_node *new_head;
	pthread_mutex_lock(&ev_queue_mutex);
	if (ev_queue.head == NULL)
		goto end;
	result = ev_queue.head->ev;
	new_head = ev_queue.head->next;
	free(ev_queue.head);
	ev_queue.head = new_head;
	if (ev_queue.head)
		ev_queue.head->prev = NULL;
	else
		ev_queue.tail = NULL;

	end:
	pthread_mutex_unlock(&ev_queue_mutex);
	return result;
}

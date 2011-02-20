#include "queue.h"

struct queue_node {
	void *element;
	queue_node *next, *prev;
};

static queue_node *new_node(void *element, queue_node *prev, queue_node *next) {
	queue_node *result = (queue_node *) malloc(sizeof (*result));
	if (result) {
		result->element = element;
		result->prev = prev;
		result->next = next;
	}
	return result;
}

int queue_enqueue(queue *q, void *element) {
	int result = 0;
	pthread_mutex_lock(&(q->lock));
	if (q->head == NULL) {
		q->head = q->tail = new_node(element, NULL, NULL);
		result = q->head != NULL;
		goto end;
	} else {
		queue_node *new_tail = new_node(element, q->tail, NULL);
		if (result) {
			q->tail = new_tail;
			result = 1;
		}
	}

	end:
	pthread_mutex_unlock(&(q->lock));
	return result;
}

void *queue_dequeue(queue *q) {
	void *result = NULL;
	queue_node *new_head;
	pthread_mutex_lock(&(q->lock));
	if (q->head == NULL)
		goto end;
	result = q->head->element;
	new_head = q->head->next;
	free(q->head);
	q->head = new_head;
	if (q->head)
		q->head->prev = NULL;
	else
		q->tail = NULL;

	end:
	pthread_mutex_unlock(&(q->lock));
	return result;
}

#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>
#include <stdlib.h>

typedef struct queue_node queue_node;

typedef struct {
	pthread_mutex_t lock;
	queue_node *head, *tail;
} queue;

#define QUEUE_INITIALIZER { PTHREAD_MUTEX_INITIALIZER, NULL, NULL }

int queue_enqueue(queue *q, void *element);
void *queue_dequeue(queue *q);

#endif

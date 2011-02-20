#include "message.h"

#include "queue.h"

queue msg_queue = QUEUE_INITIALIZER;

message *message_dequeue(void) {
    return (message *) queue_dequeue(&msg_queue);
}

int message_queue(message *msg) {
    return queue_enqueue(&msg_queue, (void *) msg);
}

#ifndef MESSAGE_H
#define MESSAGE_H

typedef struct message {
    void (*handle_message)(struct message *);
} message;

message *message_dequeue(void);
int message_queue(message *msg);

#endif

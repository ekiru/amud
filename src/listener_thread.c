#include "listener_thread.h"

#include <pthread.h>
#include <stdio.h>

void *listener_thread_start(void *portp) {
	int port = * (int *) portp;
	puts("Listener thread started.");
	pthread_exit(NULL);
}

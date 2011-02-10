#include "io_thread.h"

#include <pthread.h>
#include <stdio.h>

void *io_thread_start(void *ignore) {
	puts("IO thread started.");
	pthread_exit(NULL);
}

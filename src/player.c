#include "player.h"

#include <pthread.h>
#include <stdlib.h>

struct player {
	player *prev, *next;
	int fd;
	unsigned long id;
};

player *new_player(int fd, unsigned long id) {
	player *result = malloc(sizeof (*result));
	if (result) {
		result->fd = fd;
		result->id = id;
	}
	return result;
}

void free_player(player *p) {
	free(p);
}

int player_fd(player *p) {
	return p->fd;
}

unsigned long player_id(player *p) {
	return p->id;
}

static player *player_list = NULL;
static pthread_mutex_t player_list_mutex = PTHREAD_MUTEX_INITIALIZER;

void player_list_lock(void) {
	pthread_mutex_lock(&player_list_mutex);
}

void player_list_unlock(void) {
	pthread_mutex_unlock(&player_list_mutex);
}

player *player_list_head(void) {
	return player_list;
}

player *player_list_next(player *p) {
	return p->next;
}

player *player_list_previous(player *p) {
	return p->prev;
}

void add_player(player *p) {
	player_list_lock();
	if (player_list == NULL) {
		player_list = p;
		p->next = p->prev = p;
	} else {
		p->next = player_list;
		p->prev = player_list->prev;
		p->next->prev = p;
		p->prev->next = p;
	}
	player_list_unlock();
}

void remove_player(player *p) {
	player_list_lock();
	if (p == player_list)
		player_list = p->next;

	p->next->prev = p->prev;
	p->prev->next = p->next;
	player_list_unlock();
}

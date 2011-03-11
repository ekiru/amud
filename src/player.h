#ifndef PLAYER_H
#define PLAYER_H

typedef struct player player;

player *new_player(int fd, unsigned long id);
void free_player(player *p);

int player_fd(player *p);
unsigned long player_id(player *p);

void player_list_lock(void);
void player_list_unlock(void);
player *player_list_head(void);
player *player_list_next(player *p);
player *player_list_previous(player *p);

void add_player(player *p);
void remove_player(player *p);

#define PLAYER_LIST_LOCKED(block) do { \
		player_list_lock(); \
		do block while (0); \
		player_list_unlock(); \
	} while (0)

#endif

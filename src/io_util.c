#include "io_util.h"

#include <stdlib.h>

#include "error_status.h"
#include "message.h"
#include "messages/send.h"
#include "player.h"

void send_all(bstring text) {
	int result = 1;
	player *curr, *head;
	player_list_lock();
	head = curr = player_list_head();
	if (head == NULL)
		goto end;

	do {
		message *msg;
		bstring text_copy = bstrcpy((const_bstring) text);
		if (text_copy == NULL)
			exit(ALLOCATION_ERROR);
		if ((msg = send_message(curr, text_copy, NULL)) == NULL)
			exit(ALLOCATION_ERROR);
		message_queue(msg);
		curr = player_list_next(curr);
	} while (curr != head);

	end:
	player_list_unlock();
}

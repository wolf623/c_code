#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

int main(void)
{
	dllist_t *dl;
	dllist_t original;
	dllist_t *item = malloc(sizeof(item));
	memset(&original, 0, sizeof(original));
	original.prev = NULL;
	original.next = NULL;

	item->data = 23;

	dllist_t *new_item = malloc(sizeof(new_item));
	new_item->data = 38;

	//dllist_insert_head(original.prev, original.next, item);
	//dllist_new(1, sizeof(dllist_t), original.prev, original.next, dl);
	
	dllist_insert_head(original.prev, original.next, item);
	dllist_insert_head(original.prev, original.next, new_item);
	
	dllist_get_first_item(original.prev, original.next, dl);
	printf("data: %d\n", dl->data);

	//printf("original.prev->data: %d\n", original.prev->data);
	//printf("original.next->data: %d\n", original.next->data);

	return 0;
}


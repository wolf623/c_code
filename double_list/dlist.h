/*
 * double list file
 * 2013-11-18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* define double list data structure */
typedef struct dllist_s
{
	struct dllist_s *prev;
	struct dllist_s *next;
	int data;
}dllist_t;

/* insert an new item at the head */
#define dllist_insert_head(head, tail, item) \
{ \
	if(item != NULL) \
	{ \
		(item)->prev = NULL; \
							\
		if(head == NULL) \
		{ \
			tail = item; \
			(item)->next = NULL; \
		} \
		else \
		{ \
			(item)->next = head; \
			(head)->prev = item; \
		} \
					\
		head = item; \
	} \
}

/* get first item from the double list */
#define dllist_get_first_item(head, tail, item) \
{ \
	item = head; \
	if(head != NULL) \
	{ \
		if(item == tail) \
		{ \
			tail = NULL; \
		} \
		else \
		{ \
			(head)->prev = NULL; \
		} \
				\
		(item)->prev = NULL; \
		(item)->next = NULL; \
	} \
}


/* search the data in the double list */
#define dllist_search_data(head, tail, data) \
{ \
	if(head != NULL) \
}




#define dllist_new(num, size, head, tail, item) \
{ \
	unsigned char *p; \
	int i, len = num * size; \
						\
	if((p = (unsigned char *)malloc(len)) != NULL) \
	{ \
		head = NULL; \
		tail = NULL; \
					\
		memset((void *)p, 0, len); \
		for(i=0; i<num; i++) \
		{ \
			(item) = (void *)p; \
			dllist_insert_head(head, tail, item); \
			p = p + size; \
		} \
	} \
}


		

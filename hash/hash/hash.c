/*
 * This file is implement of the hash 
 * Author: wolf
 * Thu May 22 16:25:07 CST 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "linux_hash.h"
#include "hash.h"

static inline u_int32_t u32_hash(u_int32_t value)
{
	return hash_long (value, 16) & (HASH_SIZE - 1);
}

/* initial the hash bushet, return 0 if success, or -1 */
int hash_init()
{
	pthread_mutex_lock(&data_hash_mutex);

	if(data_hash_p == NULL)
	{
		data_hash_p = (data_hash_p_t *)malloc(sizeof(data_hash_p_t) * HASH_SIZE);
		if(data_hash_p == NULL)
		{
			pthread_mutex_unlock(&data_hash_mutex);
			return -1;
		}
	}

	int i = 0;
	for(i=0; i<HASH_SIZE; i++)
	{
		data_hash_p[i] = NULL;
	}

	return 0;
}

/* destroy the hash bushet */
void hash_destroy()
{
	int i = 0;
	for(i=0; i<HASH_SIZE; i++)
	{
		data_hash_t *p = data_hash_p[i];
		data_hash_t *p1;

		while(p != NULL)
		{
			p1 = p->next;
			if(p->data != NULL)
			{
				free(p->data);
				p->data = NULL;
			}
			free(p);
			p = p1;
		}
		
		data_hash_p[i] = NULL;
	}
	
	pthread_mutex_unlock(&data_hash_mutex);
}


/* add new entry into the hash bushet,return 0 if success, -1 if failed */
int hash_add(u_int32_t key, void *data, int len)
{
	int index = u32_hash(key);
	data_hash_t *p = data_hash_p[index];

	data_hash_t *dp = (data_hash_t *)malloc(sizeof(data_hash_t));
	if(dp != NULL)
	{
		dp->key = key;
		dp->data = malloc(len);
		dp->next = NULL;
	}

	if(dp == NULL || dp->data == NULL)
	{
		return -1;
	}
	
	if(data != NULL)
	{
		//printf("input data: %d\n", *(int *)data);
		memcpy(dp->data, data, len);
		//printf("after input: %d\n", *(int *)(dp->data));
	}

	if(p == NULL)
	{
		data_hash_p[index] = dp;
	}
	else
	{
		dp->next = p->next;
		p->next = dp;
	}

	return 0;
}

void* hash_find(u_int32_t key)
{
	int index = u32_hash(key);
	data_hash_t *p = data_hash_p[index];

	while(p != NULL)
	{
		if(p->key == key)
		{
			//return p->data;
			return p; //return the point of the data
		}
		p = p->next;
	}

	return NULL;
}

void* hash_deep_find(u_int32_t key, void *data, ssize_t len)
{
	if(data == NULL || len == 0)
	{
		return hash_find(key);
	}

	int index = u32_hash(key); 
	data_hash_t *p = data_hash_p[index];

	while(p != NULL)
	{
		if(p->key == key)
		{
			if(p->data && memcmp(p->data, data, len) == 0)
			{
				//return p->data;
				return p; //return back the point of data
			}
		}
		p = p->next;
	}
	
	return NULL;
}


void hash_print()
{
	int i = 0;
	for(i=0; i<HASH_SIZE; i++)
	{
		data_hash_t *p = data_hash_p[i];
		while(p != NULL)
		{
			printf("key: %d, ", p->key);
			if(p->data != NULL)
			{
				printf("data: %d\n", *(int *)p->data);
			}
			printf("\n");
			p = p->next;
		}
	}
}




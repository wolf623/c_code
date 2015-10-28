#ifndef _HASH_H
#define _HASH_H

#include <stdio.h>
#include <pthread.h>

#include "linux_hash.h"

#define HASH_SIZE	8192

typedef unsigned int u_int32_t;

typedef struct _data_hash_t
{
	u_int32_t key;
	void *data;
	struct _data_hash_t *next;
}data_hash_t;

typedef data_hash_t* data_hash_p_t;

static data_hash_p_t* data_hash_p = NULL;

static pthread_mutex_t data_hash_mutex = PTHREAD_MUTEX_INITIALIZER;

static inline u_int32_t u32_hash(u_int32_t value);

/* initial the hash bushet, return 0 if success, or -1 */
int hash_init();

/* destroy the hash bushet */
void hash_destroy();

/* add new entry into the hash bushet,return 0 if success, -1 if failed */
int hash_add(u_int32_t key, void *data, int len);

void* hash_find(u_int32_t key);


void* hash_deep_find(u_int32_t key, void *data, ssize_t len);


void hash_print();

#endif


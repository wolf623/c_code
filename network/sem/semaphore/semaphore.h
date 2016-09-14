#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>

union semun
{
	int val; /* value for SETVAL */
	struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
	unsigned short *array; /* Array for GETVAL, SETVAL */
	struct seminfo *__buf; /* buffer for IPC_INFO */
};

//shared data
typedef struct _shard_data_t
{
	int val;
}shared_data_t;

/* global */
static int semid = 0; //semaphore id
static int nsem = 1; //one semaphore

static int val = 0; //shard value
static key_t semkey = -1;

static int shmid = -1; //sharedmemory id
static shared_data_t *ptr = NULL; //sharedmemory address

/* function  head */
int semaphore_create_and_p();
void semaphore_v();
void semaphore_unlock();
void semaphore_delete();

/* shared memory */
int sharedmemory_create();
shared_data_t *sharedmemory_init();
void sharedmemory_set(int val);
int sharedmemory_get();
int sharedmemory_remove();
int sharedmemory_delete();
int sharedmemory_change();
void sharedmemory_increase();

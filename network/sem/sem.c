#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

static int semid = 0;
static void sem_initial()
{
	union semun sem_union;
	sem_union.val = 1;
	if(semctl(semid, 0, SETVAL, sem_union) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
}

static int semaphore_p()
{
	struct sembuf buff;
	buff.sem_num = 0;
	buff.sem_op = -1; //p
	buff.sem_flg = SEM_UNDO;
	if(semop(semid, &buff, 1) == -1)
	{
		printf("%s(): semop(P) failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	
	return 0;
}

static int semaphore_v()
{
	struct sembuf buff;
	buff.sem_num = 0;
	buff.sem_op = 1; //p
	buff.sem_flg = SEM_UNDO;
	if(semop(semid, &buff, 1) == -1)
	{
		printf("%s(): semop(V) failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	
	return 0;
}

static void sem_delete()
{
	if(semctl(semid, 0, IPC_RMID) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
}

int main(int argc, char *argv[])
{
	char msg = 'x';
	int i = 0;
	key_t key = ftok("/home/lm/network/sem/sem.c", 1);
	if(key == -1)
	{
		printf("%s(): ftok failed(%d), %s\n", __FUNCTION__, key, strerror(errno));
		return -1;
	}

	semid = semget(key, 1, 0666|IPC_CREAT);
	if(semid == -1)
	{
		printf("%s(): semget failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	
	if(argc > 1)
	{
		msg = argv[1][0];
		sem_initial();
	}
	
	for(i=0; i<10; i++)
	{
		if(semaphore_p() != 0)
			return -1;
		printf("%c", msg);
		fflush(stdout);
		sleep(rand()%3);
		printf("%c", msg);
		fflush(stdout);
		if(semaphore_v() != 0)
				return -1;
		sleep(rand()%2);
	}

	sleep(10);
	printf("finish...\n");

	if(argc > 1)
	{
		sem_delete();
	}
	return 0;
}


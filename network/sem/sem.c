/*
  * 2015-11-17 11:47
  * System V semaphore usage
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
	int val;  /* value for SETVAL */
	struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
	unsigned short *array; /* array for GETVAL, SETALL */
	struct seminfo *_buf; /* buffer for IPC_INFO */
};

static int semid = 0;
static int nsem = 3;

//SETVAL and SETALL do the same operation
static void semaphore_initial()
{
	int i;
	union semun sem_union;
	#if 0
	for(i=0; i<nsem; i++)
	{
		sem_union.val = i+1;
		if(semctl(semid, i, SETVAL, sem_union) == -1)
		{
			printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
			return;
		}
	}
	#else
	unsigned short array[] = {1, 2, 3};
	sem_union.array = array;
	//The second parameter(-1) is ignored
	if(semctl(semid, -1, SETALL, sem_union) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
	#endif
}

static void semaphore_getsemval()
{

	#if 0
	int semval;
	int i;
	for(i=0; i<nsem; i++)
	{
		if((semval = semctl(semid, i, GETVAL)) == -1)
		{
			printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
			return;
		}

		printf("semval: %d\n", semval);
	}
	#else
	union semun sem_union;
	unsigned short array[3] = {0};
	sem_union.array = array;
	if(semctl(semid, -1, GETALL, sem_union) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
	int i;
	for(i=0; i<nsem; i++)
	{
		printf("%d\n", array[i]);
	}
	#endif
}
	
static void semaphore_getpid()
{
	int pid;
	if((pid = semctl(semid, 1, GETPID)) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
			return;
	}

	printf("pid: %d\n", pid);
}

static void semaphore_getncnt()
{
	int ncnt;
	if((ncnt = semctl(semid, 0, GETNCNT)) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
			return;
	}

	printf("ncnt: %d\n", ncnt);
}

static void semaphore_getzcnt()
{
	int zcnt;
	if((zcnt = semctl(semid, 2, GETZCNT)) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
			return;
	}

	printf("zcnt: %d\n", zcnt);
}

static void semaphore_getipcstat()
{
	union semun sem_union;
	struct semid_ds ds;
	sem_union.buf = &ds;
	if(semctl(semid, 0, IPC_STAT, sem_union) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
	printf("sem_nsems: %d, sem_ctime: %d, sem_otime: %d\n", (int)ds.sem_nsems, (int)ds.sem_ctime, (int)ds.sem_otime);
}

static void semaphore_setipcstat()
{
	union semun sem_union;
	struct semid_ds ds;
	//can not change sem_nsems/sem_ctime/sem_otime etc.
	sem_union.buf = &ds;
	if(semctl(semid, -1, IPC_SET, sem_union) == -1)
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
	buff.sem_op = 1; //v
	buff.sem_flg = SEM_UNDO;
	if(semop(semid, &buff, 1) == -1)
	{
		printf("%s(): semop(V) failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	
	return 0;
}

static void semaphore_delete()
{
	if(semctl(semid, nsem, IPC_RMID) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
}

static int semaphore_create_and_post()
{
	key_t key = IPC_PRIVATE;
	union semun arg;
	struct sembuf buff;
	
	if(semid == 0)
	{
		if((semid = semget(key, nsem, 0666|IPC_CREAT|IPC_EXCL)) != -1)
		{
			//create successfully, no initial here
			arg.val = 1;
			if(semctl(semid, 0, SETVAL, arg) == -1)
			{
				printf("%s(): semctl(SETVAL) failed, %s\n", __FUNCTION__, strerror(errno));
				return -1;
			}
		}
		else if(errno == EEXIST) //it exist already?
		{
			if((semid = semget(key, nsem, 0666)) == -1)
				printf("%s(): semget failed, %s\n", __FUNCTION__, strerror(errno));
			
			//we need to check if it is initialized already,
			//because we need to deal with multi-process situation
			struct semid_ds seminfo;
			arg.buf = &seminfo;
			int i, max_tries = 5; //max try times
			for(i=0; i<max_tries; i++)
			{
				if(semctl(semid, 0, IPC_STAT, arg) != -1)
				{
					if(arg.buf->sem_otime == 0)  //indicate it is not initialized yet
						sleep(1); //wait for initial
					else
						//break;
						goto initialize;
				}
			}
		}
		else //should not go here
		{
			printf("%s(): semget(IPC_CREAT) failed, %s\n", __FUNCTION__, strerror(errno));
			return -1;
		}
	}

initialize:
	#if 1
	buff.sem_num = 0; //the first one
	buff.sem_op = -1;
	buff.sem_flg = SEM_UNDO;
	if(semop(semid, &buff, 1) == -1)
	{
		printf("%s(): semop(P) failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	#endif
	
	return semid;
}

int main(int argc, char *argv[])
{
	char msg = 'x';
	int i = 0;
	#if 1
	key_t key;
	#if 0
	key = ftok("/home/lm/network/sem/sem.c", 1);
	if(key == -1)
	{
		printf("%s(): ftok failed(%d), %s\n", __FUNCTION__, key, strerror(errno));
		return -1;
	}
	#else
	key = IPC_PRIVATE;
	#endif

	if(semid == 0)
		semid = semget(key, nsem, 0666|IPC_CREAT);
	
	if(semid == -1)
	{
		printf("%s(): semget failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	#else
	semaphore_create_and_post();
	#endif
	semaphore_initial();
	semaphore_getsemval();
	semaphore_getpid();
	semaphore_getncnt();
	semaphore_getzcnt();
	//semaphore_setipcstat();
	semaphore_getipcstat();
	
	for(i=0; i<10; i++)
	{
		//if(semaphore_p() != 0)
		//	return -1;
		printf("%c", msg);
		fflush(stdout);
		//sleep(rand()%3);
		printf("%c", msg);
		fflush(stdout);
		//if(semaphore_v() != 0)
		//		return -1;
		//sleep(rand()%2);
	}
	
	semaphore_delete();
	
	return 0;
}


#include "semaphore.h"


int semaphore_create_and_p()
{
	//Here, we can not use it, becase we must the same only key
	//key_t key = IPC_PRIVATE;
	union semun arg;
	struct sembuf buff;
	
	if(semid == 0)
	{
		semkey = ftok("./semaphore.h", 1);
		if(semkey == -1)
		{
			printf("%s(): ftok() failed, %s\n", __FUNCTION__, strerror(errno));
			return -1;
		}
		if((semid = semget(semkey, nsem, 0777|IPC_CREAT|IPC_EXCL)) != -1)
		{	
			#if 1
			//create successfully, no initial here
			arg.val = 1; //initialize with 1
			if(semctl(semid, 0, SETVAL, arg) == -1)
			{
				printf("%s(): semctl(SETVAL) failed, %s\n", __FUNCTION__, strerror(errno));
				return -1;
			}
			#endif
		}
		else if(errno == EEXIST) //it exist already?
		{
			if((semid = semget(semkey, nsem, 0777)) == -1)
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
	buff.sem_num = 0; //the first one
	buff.sem_op = -1; //p
	buff.sem_flg = SEM_UNDO;
	if(semop(semid, &buff, 1) == -1)
	{
		printf("%s(): semop(P) failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	
	return semid;
}

void semaphore_v()
{
	//in case semid is not initialized yet
	if(semid == 0)
	{
		if(semkey == -1)
			semkey = ftok("./semaphore.h", 1);
		
		if(semkey == -1)
			return;
		if((semid = semget(semkey, nsem, 0777)) == -1)
		{
			printf("%s(): semget failed, %s\n", __FUNCTION__, strerror(errno));
			return;
		}
	}

	//try to get
	if((semid = semget(semkey, nsem, 0777)) == -1)
		return; //maybe delelte by other process, just return back
	
	struct sembuf buff;
	buff.sem_num = 0; 
	buff.sem_op = 1; //v
	buff.sem_flg = SEM_UNDO;
	if(semop(semid, &buff, 1) == -1)
	{
		printf("%s(): semop(V) failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
}

void semaphore_unlock()
{
	union semun arg;
	arg.val = 1;
	if(semctl(semid, 0, SETVAL, arg) == -1)
	{
		printf("%s(): semctl(SETVAL) failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
}


void semaphore_delete()
{
	if(semid == 0)
		return; //it should be deleted already by other prcess

	if(semkey == -1)
		semkey = ftok("./semaphore.h", 1);
		
	if(semkey == -1)
		return;

	if((semid = semget(semkey, nsem, 0777)) == -1)
			return; //maybe delete by other process.just return back
	
	if(semctl(semid, nsem, IPC_RMID) == -1)
	{
		printf("%s(): semctl failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
	
	semid = 0; //reset semid to 0
}

/* shared memory API */
int sharedmemory_create()
{
	if(shmid != -1)
		return shmid;
	
	//key_t key = IPC_PRIVATE;
	key_t key = ftok("./semaphore.h", 1);
	if(key == -1)
	{
		printf("%s(): ftok failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	
	shmid = shmget(key, sizeof(shared_data_t), 0777|IPC_CREAT); //IPC_EXCL
	if(shmid == -1)
	{
		printf("%s(): shmget(IPC_CREAT|IPC_EXCL) failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}

	return shmid;
}

shared_data_t *sharedmemory_init()
{
	if(shmid == -1)
	{
		sharedmemory_create();
	}
	
	if(ptr != NULL)
	{
		return ptr;
	}

	if((ptr = (shared_data_t *)shmat(shmid, 0, 0)) == NULL)
	{
		printf("%s(): shmat failed, %s\n", __FUNCTION__, strerror(errno));
		return NULL;
	}

	ptr->val = 0;
	return ptr;
}

void sharedmemory_set(int val)
{
	if(ptr == NULL)
	{
		sharedmemory_init();
	}

	ptr->val = val;
}

int sharedmemory_get()
{
	if(ptr == NULL)
		sharedmemory_init();

	return ptr->val;
}

void sharedmemory_increase()
{
	if(ptr == NULL)
		sharedmemory_init();

	sleep(rand()%2);
	ptr->val++;
}

int sharedmemory_remove()
{
	if(ptr == NULL)
		return 0;

	if(shmdt(ptr) == -1)
	{
		printf("%s(): shmdt failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}

	ptr = NULL;
}

int sharedmemory_delete()
{
	if(shmid == -1)
		return 0;

	if(shmctl(shmid, IPC_RMID, 0) == -1)
	{
		printf("%s(): shmctl(IPC_RMID) failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}

	shmid = -1;
}

int sharedmemory_change()
{
}




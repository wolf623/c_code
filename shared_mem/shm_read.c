#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <error.h>
#include "shmdata.h"

int shm_read(void)
{
	//(1) create shared memory
	int shmid = 0;
	if((shmid = shmget((key_t)1234, sizeof(shmdata_t), 0666|IPC_CREAT)) == -1)
	{
		perror("shmget");
		return -1;
	}

	//(2) link the shard memory address to current process address
	void *shm = shmat(shmid, NULL, 0);
	if(shm == (void *)-1)
	{
		perror("shmat");
		return -1;
	}

	printf("Memory attached at %x\n", *(int *)shm);

	//(3)set shard memory
	shmdata_t *shmdata = NULL;
	shmdata = (shmdata_t *)shm;
	shmdata->flag = 0;

	int running = 1; //the flag is the process is running or not
	while(running)
	{
		if(shmdata->flag != 0)
		{
			printf("you wrote: %s\n", shmdata->text);
			sleep(rand() % 3);
			shmdata->flag = 0; //reset the flag for write
			if(!strncmp(shmdata->text, "quit", 4))
				running = 0; //quit
		}
		else //othe process is writing the message, can not use
		{
			sleep(1);
		}
	}

	//remove the shared memory from current process
	if(shmdt(shm) == -1)
	{
		perror("shmdt");
		return -1;
	}

	//delete the shared memory
	if(shmctl(shmid, IPC_RMID, 0) == -1)
	{
		perror("shmid");
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	shm_read();

	return 0;
}


	

		




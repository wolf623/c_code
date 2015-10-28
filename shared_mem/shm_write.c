#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <error.h>
#include "shmdata.h"

int shm_write(void)
{
	//(1) get shared memory
	int shmid = 0;
	if((shmid = shmget((key_t)1234, sizeof(shmdata_t), 0666)) == -1)
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
	char buff[TEXT_LEN + 1] = {0};
	while(running)
	{
		while(shmdata->flag == 1)
		{
			//do not read the text message, wait it to done
			printf("wrinting...\n");
			sleep(1);
		}

		printf("please write what you want: ");
		fgets(buff, TEXT_LEN, stdin);
		strncpy(shmdata->text, buff, TEXT_LEN);
		shmdata->flag = 1; //reset the flag for read
		if(!strncmp(shmdata->text, "quit", 4))
			running = 0; //quit
	}

	//remove the shared memory from current process
	if(shmdt(shm) == -1)
	{
		perror("shmdt");
		return -1;
	}

/*
	//delete the shared memory
	if(shmctl(shmid, IPC_RMID, 0) == -1)
	{
		perror("shmid");
		return -1;
	}
*/
	return 0;
}

int main(int argc, char *argv[])
{
	shm_write();

	return 0;
}


	

		




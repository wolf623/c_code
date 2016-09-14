/* Process A */

#include "semaphore.h"

int main(int argc, char *argv[])
{
	#if 0
	int i;
	for(i=0; i<2; i++)
	{
		semaphore_create_and_p();
		val++;
		printf("I am A process...val %d\n", val);
		fflush(stdout);
		sleep(1);
		//semaphore_v();
	}

	//printf("I am A process to delete semid...\n");
	//semaphore_delete();
	//printf("Process B: I am done...\n");
	#endif

	int val = sharedmemory_create();
	printf("%s(): shmid %d\n", __FUNCTION__, val);
	sharedmemory_init();
	int i;
	for(i=0; i<10; i++)
	{
		semaphore_create_and_p();
		sharedmemory_increase();
		printf("A process: val %d\n", sharedmemory_get());
		semaphore_v();
	}
	
	sharedmemory_delete();
	semaphore_delete();
	return 0;
}

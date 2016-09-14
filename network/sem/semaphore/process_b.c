/* Process B */

#include "semaphore.h"

int main(int argc, char *argv[])
{
	#if 0
	int i;
	for(i=0; i<2; i++)
	{
		//semaphore_create_and_p();
		val++;
		printf("I am B process...val %d\n", val);
		fflush(stdout);
		semaphore_v();
		sleep(1);
	}

	sleep(3);
	semaphore_delete();
	#endif

	int val = sharedmemory_create();
	printf("%s(): shmid %d\n", __FUNCTION__, val);
	sharedmemory_init();
	int i;
	for(i=0; i<10; i++)
	{
		semaphore_create_and_p();
		sharedmemory_increase();
		printf("B process: val %d\n", sharedmemory_get());
		semaphore_v();
	}
	sharedmemory_delete();
	semaphore_delete();
	
	return 0;
}

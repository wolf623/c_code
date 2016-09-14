/*
  * 2015-11-16 19:18
  * Shared Memory Usage
  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

static int sharedmemoryid = 0;
typedef struct _sharddata_t
{
	int val;
}shareddata_t;

static shareddata_t *arg = NULL;

//define a error log here
#define LOG(x) printf("%s(): %s, %s\n", __FUNCTION__, (x), strerror(errno))

static int sharedmemory_create()
{
	key_t key = IPC_PRIVATE;
	if((sharedmemoryid = shmget(key, sizeof(shareddata_t), (0666|IPC_CREAT|IPC_EXCL))) == -1)
	{
		printf("%s(): shmget(IPC_CREAT) failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}
	return sharedmemoryid;
}

static shareddata_t * sharedmemory_initial()
{	
	if(sharedmemoryid == 0)
	{
		sharedmemory_create();
	}

	if((arg = shmat(sharedmemoryid, NULL, 0)) == NULL)
	{
		printf("%s(): shmat failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
	
	return arg;
}

static void sharedmemory_remove()
{
	if(sharedmemoryid == 0)
		return;

	if(shmdt(arg) == -1)
	{
		printf("%s(): shmdt failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
}

static void sharedmemory_delete()
{
	if(sharedmemoryid == 0)
		return;

	if(shmctl(sharedmemoryid, IPC_RMID, NULL) == -1)
	{
		printf("%s(): shmctl(IPC_RMID) failed, %s\n", __FUNCTION__, strerror(errno));
		return;
	}
}


//CMD: IPC_SET/IPC_INFO/SHM_INFO/SHM_STAT/
static void sharedmemory_getinfo()
{
	if(sharedmemoryid == 0)
		sharedmemory_initial();

	struct shmid_ds arg;
	if((shmctl(sharedmemoryid, IPC_STAT, &arg)) == -1)
		LOG("shmctl(IPC_STAT) failed");

	printf("creater's pid: %d(%d)\n", arg.shm_cpid, getpid());
}

static void sharedmemory_setinfo()
{
	if(sharedmemoryid == 0)
		sharedmemory_initial();

	struct shmid_ds arg;
	memset(&arg, 0, sizeof(arg));//juli
	if((shmctl(sharedmemoryid, IPC_SET, &arg)) == -1)
		LOG("shmctl(IPC_STAT) failed");
}

static void shareddata_init()
{
	if(arg == NULL)
	{
		sharedmemory_initial();
	}

	if(arg != NULL)
		arg->val = 23;
}

static int shareddata_get()
{
	if(arg != NULL)
		return arg->val;
}

int main(int argc, char *argv[])
{
	sharedmemory_create();
	sharedmemory_initial();
	shareddata_init();
	printf("shared val: %d\n", shareddata_get());
	sharedmemory_getinfo();
	sharedmemory_delete();
	
	return 0;
}

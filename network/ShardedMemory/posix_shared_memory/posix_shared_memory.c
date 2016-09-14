#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Based on the file map way
//Base on the shared-memory way

//#define POSIX_SHARED_NAME "./tempposixsharednaem"
#define POSIX_NAME "test"

typedef struct _shared_data_t
{
	int val;
}shared_data_t;

int main(int argc, char *argv[])
{
	pid_t pid;
	shared_data_t *p_data = NULL;

	#ifdef POSIX_SHARED_NAME
	int fd = open(POSIX_SHARED_NAME, O_CREAT|O_RDWR, 0666);
	if(fd < 0)
	{
		printf("open %s failed\n", POSIX_SHARED_NAME);
		return -1;
	}
	#else
	int fd = shm_open(POSIX_NAME, O_CREAT|O_RDWR, 0666);
	if(fd < 0)
	{
		printf("shm_open failed, %s\n", strerror(errno));
		return -1;
	}
	#endif

	if(ftruncate(fd,  sizeof(shared_data_t)) < 0)
	{
		printf("ftruncate failed, %s\n", strerror(errno));
		return -1;
	}

	if((p_data=(shared_data_t *)mmap(NULL, sizeof(shared_data_t), PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
	{
		printf("mmap failed, %s\n", strerror(errno));
		return -1;
	}
	
	if((pid=fork()) < 0)
	{
		printf("fork failed, %s\n", strerror(errno));
		return -1;
	}
	else if(pid == 0)
	{ 
		//child
		//p_data->val = 23;
		//printf("child: val %d\n", p_data->val);
	}
	else 
	{
		//parent
		p_data->val = 23;
		printf("main process: val %d\n", p_data->val);
		waitpid(pid, NULL, 0); //wait child process exit
	}

	#if 0
	if(munmap(p_data, sizeof(shared_data_t)) < 0)
	{
		printf("unmap failed, %s\n", strerror(errno));
		return -1;
	}
	
	#ifndef POSIX_SHARED_NAME
	if(shm_unlink(POSIX_NAME) == -1)
	{
		printf("shm_unlink failed, %s\n", strerror(errno));
		return -1;
	}
	#endif
	
	close(fd);
	#endif
	
	return 0;
}


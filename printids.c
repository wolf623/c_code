#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t gtid;

void printids(const char *str)
{
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	fprintf(stdout, "%s: pid %u tid %u (0x%x)\n", str, (unsigned int)pid,
			(unsigned int)tid, (unsigned int)tid);
	
}

void *
pth_func(void *arg)
{
	printids("New Thread:");
	return ((void *)0);
}

int main(void)
{
	int err;

	err = pthread_create(&gtid, NULL, pth_func, NULL);
	
	fprintf(stdout, "pid = %u, tid = %u, gtid = %u.\n", (unsigned int)getpid(), (unsigned int)pthread_self(),(unsigned int) gtid);

	if(err != 0)
	{
		fprintf(stderr, "pthread_create error.\n");
		exit(1);
	}

	printids("Main Thread:");
	
	sleep(1);

	exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define PTHREAD_NUM	2 //max pthread number
#define FILE_NAME "temp.txt"
FILE *fp = NULL;
int g_value = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
typedef void (*func)(int *);

void write_file1(int *arg)
{
	pthread_mutex_lock(&mutex);
	printf("%s(): arg %d\n", __FUNCTION__, *arg);
	if(fp == NULL)
	{
		fp = fopen(FILE_NAME, "w+");
	
		if(fp == NULL)
		{
			printf("fopen failed!\n", strerror(errno));
			return;
		}
	}
	
	char *ptr = "write somgthing here...";
	fwrite(ptr, strlen(ptr), 1, fp);
	printf("in func1 before add, value %d\n", g_value);
	struct timeval now;
	struct timespec outtime;
	gettimeofday(&now, NULL);
	outtime.tv_sec = now.tv_sec + 2;
	outtime.tv_nsec = now.tv_usec * 1000;
	//pthread_cond_wait(&cond, &mutex);
	pthread_cond_timedwait(&cond, &mutex, &outtime);
	printf("time out...I am ready to go!!!\n");
	g_value++;
	printf("in func1 after add, value %d\n", g_value);
	pthread_mutex_unlock(&mutex);
	pthread_exit("pthread exit message - 1");
}

void write_file2(int *arg)
{
	pthread_mutex_lock(&mutex);
	printf("%s(): arg %d\n", __FUNCTION__, *arg);
	if(fp == NULL)
	{
		fp = fopen(FILE_NAME, "w+");
	
		if(fp == NULL)
		{
			printf("fopen failed!\n", strerror(errno));
			return;
		}
	}
	
	char *ptr = "write somgthing here...";
	fwrite(ptr, strlen(ptr), 1, fp);

	printf("in func2 before add, value %d\n", g_value);
	pthread_cond_wait(&cond, &mutex);
	
	g_value++;
	printf("in func2 after add, value %d\n", g_value);
	pthread_mutex_unlock(&mutex);
	pthread_exit("pthread exit message - 2");
}

int main(int argc, char *argv[])
{
	pthread_t pthread_ns[PTHREAD_NUM];
	int i = 0, ec = 0;
	void *msg = NULL;
	func func_array[PTHREAD_NUM] = {write_file1, write_file2};

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //fenli

	pthread_mutexattr_t mtattr;
	pthread_mutexattr_init(&mtattr);
	pthread_mutexattr_settype(&mtattr, PTHREAD_MUTEX_RECURSIVE);
	
	pthread_mutex_init(&mutex, &mtattr);

	pthread_cond_init(&cond, NULL);
	//pthread_condattr_setclock(&cond, (clockid_t)CLOCK_MONOTONIC); //CLOCK_REALTIME
	 
	for(i=0; i<PTHREAD_NUM; i++)
	{
		ec = pthread_create(&pthread_ns[i], &attr, (void *(*)(void *))func_array[i], &i);
		if(ec != 0)
		{
			printf("pthread failed!\n");
		}
	}

	sleep(1);
	printf("I am here...\n");
	//pthread_cond_broadcast(&cond);
	pthread_cond_signal(&cond);
	
	for(i=0; i<PTHREAD_NUM; i++)	
	{
		pthread_join(pthread_ns[i], &msg);
		printf("end...%s\n", (char *)msg);
	}

	pthread_attr_destroy(&attr);
	pthread_mutexattr_destroy(&mtattr);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	return 0;
}




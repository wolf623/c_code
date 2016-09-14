#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#define handle_error_msg(msg) \
	do {perror(msg); return -1;} while(0)

#define handle_error_en_msg(en, msg) \
	do {errno = en; perror(msg); return -1;} while(0)
	
//global value
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int icount = 0; 

void cleanup(void *arg)
{
	printf("cleanup function...\n");
	//pthread_mutex_unlock(&mutex);
}

void *thread_one(void *arg)
{
	pthread_cleanup_push(&cleanup, NULL);

	pthread_mutex_lock(&mutex);
	while(icount < 100)
	{
		pthread_cond_wait(&cond, &mutex); //wait signal
	}
	printf(" I have got the signal...\n");
	fflush(stdout);
	pthread_mutex_unlock(&mutex);

	sleep(3);
	//return 1;
	pthread_exit((void *)1);

	pthread_cleanup_pop(0);
}

void *thread_two(void *arg)
{
	pthread_detach(pthread_self()); //detach thread
	
	pthread_cleanup_push(&cleanup, NULL);

	pthread_mutex_lock(&mutex);
	while(icount != 1000)
	{
		icount++;
	}
	pthread_cond_signal(&cond); //send signal
	pthread_mutex_unlock(&mutex);

	pthread_cleanup_pop(0);
	
	pthread_exit((void *)2);
}

int main(int argc, char *argv[])
{
	pthread_t threadId1, threadId2;
	int rc = -1;
	pthread_attr_t attr;
	void *res;
	
	pthread_attr_init(&attr);
	rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); //detach thread
	if(rc != 0)
		handle_error_en_msg(rc, "pthread_attr_setdetachstate");
		
	rc = pthread_create(&threadId1, NULL, &thread_one, NULL);
	if(rc != 0)
		handle_error_en_msg(rc, "pthread_create");

	rc = pthread_create(&threadId2, NULL, &thread_two, NULL);
	if(rc != 0)
		handle_error_en_msg(rc, "pthread_create");

	//cancel pthread1
	rc = pthread_cancel(threadId1);
	if(rc != 0)
		handle_error_en_msg(rc, "pthread_cancel");
		
	rc = pthread_join(threadId1, &res);
	if(rc == 0)
	{
		printf("thread1 return %d, %d\n", (int)res, PTHREAD_CANCELED);
		if(res == PTHREAD_CANCELED)
		{
			printf("thread1 is canceled...\n");
		}
	}
	else if(rc == EDEADLK)
		printf("thread deadlock...\n");
	else if(rc == EINVAL)
		printf("thread is not joinable...\n");
	else if(rc == EINVAL)
		printf("Another thread is already waiting to join with this thread...\n");
	else if(rc == ESRCH)
		printf("No thread with the ID thread %d could be found...\n", threadId1);
	else
		printf("Others error...\n");
	
	pthread_attr_destroy(&attr);
	
	return 0;
}



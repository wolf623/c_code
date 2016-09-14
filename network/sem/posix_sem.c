#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <errno.h>
#include <pthread.h>

static int sem_init_flag = 0; // 1 : sem is initialized
static sem_t semkey;
static int num = 0;

static void posix_sem_getvalue()
{
	int val;
	sem_getvalue(&semkey, &val);
	printf("value: %d\n", val);
}

static void posix_sem_init()
{
	sem_init(&semkey, 0, 2);//init to 2?
	sem_init_flag = 1; 
	posix_sem_getvalue();
}

static int posix_sem_p()
{
	int rc = 0;
	while(1)
	{
		errno = 0;
		rc = sem_wait(&semkey);
		/* 
		  * Our version of Linux 2.6.10 is funny, if a thread
		  * is blocked on a semaphore and it receives any
		  * signal, it returns -1 and error is set to EINTR
		  * (sem_wait must always return 0)
		*/
		if((rc == -1) && (errno == EINTR))
		{
			continue;
		}
		break;
	}
	return 0;	
}

static int posix_sem_timewait()
{
	struct timespec t;
	t.tv_sec = 10; //10 second
	t.tv_nsec = 0; 

	int rc = 0;
	while(1)
	{
		errno = 0;
		//rc = sem_trywait(&semkey);
		rc = sem_timedwait(&semkey, &t);
		if((rc == -1) && (errno == EINTR))
			continue;
		else
			break;
	}
	return rc;
}

static void posix_sem_v()
{
	sem_post(&semkey);
}

static void posix_sem_destroy()
{
	sem_destroy(&semkey);
}

static void * thread_one(void *arg)
{
	//pthread_detach(pthread_self());
	if(sem_init_flag == 0)
	{
		posix_sem_init();
		printf("thread1 init the sem...\n");
	}

	int i = 0;
	for(i=0; i<10; i++)
	{
		posix_sem_p();
		num++;
		printf("thread1: num %d\n", num);
		posix_sem_v();
	}
	printf("thread1 will return back...\n");
	//return 0;
	pthread_exit(0);
}

static void * thread_two(void *arg)
{
	//pthread_detach(pthread_self());
	if(sem_init_flag == 0)
	{
		posix_sem_init();
		printf("thread2 init the sem...\n");
	}

	int i = 0;
	for(i=0; i<10; i++)
	{
		posix_sem_p();
		num++;
		printf("thread2: num %d\n", num);
		posix_sem_v();
	}
	printf("thread2 will return back...\n");
	//return 0;
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, &thread_one, NULL);
	pthread_create(&thread2, NULL, &thread_two, NULL);

	printf("will join...\n");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	posix_sem_destroy();
	
	printf("back end...\n");
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#define handle_error_msg(msg) \
	do {perror(msg); return -1;} while(0)

#define handle_error_en_msg(en, msg) \
	do {errno = en; perror(msg); return -1;} while(0)

char *p = "Hello world";
int value1 = 1;
int value2 = 2;
int value3 = 3;

void cleanup_handle(void *arg)
{
	printf("cleanup handle function...\n");
}

static int i = 0;
void *pthread_1st(void *arg)
{
	#if 0
	int oldstate;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
	if(oldstate == PTHREAD_CANCEL_ENABLE)
		printf("it is enable before...\n");
	#endif

	#if 0
	int oldtype;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
	if(oldtype == PTHREAD_CANCEL_DEFERRED)
		printf("it is deferrred...\n");
	#endif
	
	pthread_cleanup_push(cleanup_handle, NULL);
	//printf("%s(): The first thread...\n", __FUNCTION__);
	//fflush(stdout);
	
	while(1)
	{
		
		if(i == (2^32)/2-1)
			break;
		//printf("%s(): i %d\n", __FUNCTION__, i);
		//fflush(stdout);
		i++;
	}

	//sleep(1);
	//return;
	//pthread_testcancel();
	printf("I will exit...\n");
	fflush(stdout);
	pthread_exit((void *)22);
	pthread_cleanup_pop(0);
	//exit(1);
}

void *pthread_2st(void *arg)
{
	printf("%s(): The second thread...\n", __FUNCTION__);
	fflush(stdout);
	//return;
	//exit(0);
	pthread_exit((void *)&value2);
}

void *pthread_3st(void *arg)
{
	pthread_detach(pthread_self());
	
	printf("%s(): The third thread...\n", __FUNCTION__);
	fflush(stdout);
	
	//return;
	//exit(0);
	pthread_exit((void *)&value3);
}

int main(int argc, char *argv[])
{
	pthread_t threadId1, threadId2, threadId3;
	pthread_attr_t attr;
	int rc = 0;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	rc = pthread_create(&threadId1, NULL, &pthread_1st, NULL);
	if(rc != 0)
		handle_error_en_msg(rc, "pthread_create");
	
	rc = pthread_create(&threadId2, &attr, &pthread_2st, NULL);
	if(rc != 0)
		handle_error_en_msg(rc, "pthread_create");

	//rc = pthread_create(&threadId3, NULL, &pthread_3st, NULL);
	if(rc != 0)
		handle_error_en_msg(rc, "pthread_create");

	pthread_attr_destroy(&attr);


	rc = pthread_kill(threadId3, 0);
	printf("pthread_kill return %d, %d\n", rc, ESRCH);
	
	//cancel pthread
	printf("%s(): i %d\n", __FUNCTION__, i);
	fflush(stdout);
	rc = pthread_cancel(threadId1);
	printf("%s(): i %d\n", __FUNCTION__, i);
	fflush(stdout);
	if(rc != 0)
		handle_error_en_msg(rc, "pthread_cancle");

	//wait thread exit
	void *res;
	rc = pthread_join(threadId1, &res);
	if(res == PTHREAD_CANCELED)
		printf("threadId1 was canceled, rc %d\n", rc);
	else
		printf("threadId1 was terminated normally, rc %d\n", rc);

	printf("threadId1 retun value %d, %d\n", (int)res, PTHREAD_CANCELED);
	fflush(stdout);

	return 0;
}

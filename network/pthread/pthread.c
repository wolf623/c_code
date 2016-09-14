/*
  * Pthread Usage
  * 2015-11-27
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
	
#define handle_error_en(en, msg) \
	do {errno = en; perror(msg); exit(EXIT_FAILURE); } while(0)

#define handle_error(msg) \
	do {perror(msg); exit(EXIT_FAILURE); } while(0)

typedef struct _thread_info
{
	pthread_t thread_id;
	int thread_num;
	char *argv_string;
}thread_info;

void *thread_clean(void *arg)
{
	if(arg != NULL)
		printf("%s(): %s\n", __FUNCTION__, (char *)arg);
	else
		printf("%s(): I am here...\n", __FUNCTION__);

	return (void *)0;
}

static void *thread_start(void *arg)
{
	thread_info *tinfo = arg;
	char *uargv, *p;
	printf("%s(): Thread %d: top of stack near %p; argv_string=%s\n",
			__FUNCTION__, tinfo->thread_num, &p, tinfo->argv_string);

	if(arg == NULL || tinfo->argv_string == NULL)
		return;

	pthread_cleanup_push((void *)thread_clean, "thread cleanup function");
	
	uargv = strdup(tinfo->argv_string);
	if(uargv == NULL)
		handle_error("strdup");

	for(p=uargv; *p!='\0'; p++)
		*p = toupper(*p);

	printf("%s(): identified %d\n", __FUNCTION__, (int)pthread_self());
	pthread_cleanup_pop(0);
	
	pthread_exit(0);
	
	return uargv;
	//exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	int i, rc, num_threads, opt, stack_size = -1;
	pthread_attr_t attr;
	thread_info *tinfo = NULL;
	void *res = NULL;
	
	while((opt = getopt(argc, argv, "s:")) != -1)
	{
		switch(opt)
		{
			case 's':
				stack_size = strtoul(optarg, NULL, 0);
				break;
			default:
				fprintf(stderr, "Usage: %s [-s stack size] arg...\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	num_threads = argc - optind;
	//printf("num thread %d(argc %d, optind %d), stack size %d\n", num_threads, argc, optind, stack_size);
	/* Initialize thread creation attributes */
	rc = pthread_attr_init(&attr);
	if(rc != 0)
		handle_error_en(rc, "pthread_attr_init");

	if(stack_size > 0)
	{
		rc = pthread_attr_setstacksize(&attr, stack_size);
		if(rc != 0)
			handle_error_en(rc , "pthread_attr_setstacksize");
	}
	
	tinfo = (thread_info *)calloc(num_threads, sizeof(thread_info));
	if(tinfo == NULL)
		handle_error("calloc");

	for(i=0; i<num_threads; i++)
	{
		tinfo[i].thread_num = i + 1;
		tinfo[i].argv_string = argv[optind+i];
		//printf("string: %s, optind %d, i %d\n", tinfo[i].argv_string, optind, i);
		rc = pthread_create(&tinfo[i].thread_id, &attr, &thread_start, &tinfo[i]);
		if(rc != 0)
			handle_error_en(rc, "pthread_create");
	}

	rc = pthread_attr_destroy(&attr);
	if(rc != 0)
		handle_error_en(rc, "pthread_attr_destory");

	for(i=0; i<num_threads; i++)
	{
		rc = pthread_join(tinfo[i].thread_id, &res);
		if(rc != 0)
			handle_error_en(rc, "pthread_join");

		printf("Join with thread %d, returned value was\n", tinfo[i].thread_num, (char *)res);
	}
	
	free(tinfo);
	exit(EXIT_SUCCESS);
}


	

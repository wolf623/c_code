#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FILE_FLAG O_RDWR | O_CREAT

static int mqflag = 0;
static mqd_t mqd = 0;
struct sigevent sigev;
static void sig_usr1(int value)
{
	printf("%s(): value %d\n", __FUNCTION__, value);
	mqflag = 1;
	return;
}

static void notify_thread(union sigval arg)
{
	ssize_t n;
	char recv_buff[128] = {0};
	printf("notify_thread started! sigval %d\n", arg.sival_int);
	mq_notify(mqd, &sigev);
	int prio = 0;
	while((n = mq_receive(mqd, recv_buff, sizeof(recv_buff), &prio)) > 0)
		printf("recv: %s, %d\n", recv_buff, prio);
		
	if(errno != EAGAIN)
	{
		printf("mq_receive error! %s\n", strerror(errno));
		return;
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: a.out <name>\n");
		return -1;
	}
	
	struct mq_attr attr;
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg = 2;
	attr.mq_msgsize = 128;
	mqd = mq_open(argv[1], FILE_FLAG, FILE_MODE, &attr);
	if(mqd == -1)
	{
		printf("mq_open failed! %s\n", strerror(errno));
		return -1;
	}

	if(mq_getattr(mqd, &attr) == 0)
	{
		printf("mq_maxmsg %lu, mq_msgsize %lu, msg_curmsgs %lu, mq_flags %lu\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs, attr.mq_flags);
	}

#if 0
	attr.mq_flags = O_NONBLOCK;
	if(mq_setattr(mqd, &attr, NULL) == 0)
	{
		printf("mq_setattr success, flags %lu\n", attr.mq_flags);
	}

	memset(&attr, 0, sizeof(attr));
	if(mq_getattr(mqd, &attr) == 0)
	{
		printf("After mq_setattr, mq_maxmsg %lu, mq_msgsize %lu, msg_curmsgs %lu, mq_flags %lu\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs, attr.mq_flags);
	}
#endif

	sigset_t zeromask, newmask, oldmask;
	memset(&sigev, 0, sizeof(sigev));
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	//sigev.sigev_value.sival_int = 3; //parameter
	int value = 2;
	sigev.sigev_value.sival_ptr = &value; //parameter
	printf("%s(): set parameter %d\n", __FUNCTION__, *(int *)sigev.sigev_value.sival_ptr);
	
	
	printf("Begin to receive ...\n");
	char recv_buff[128] = {0};
	int prio = 0;

	#if 0
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigemptyset(&oldmask);
	sigaddset(&newmask, SIGUSR1);
	signal(SIGUSR1, sig_usr1);

	if(mq_notify(mqd, &sigev) == -1)
	{
		printf("mq_notify failed! %s\n", strerror(errno));
		goto remove_mqd;
	}

	
	while(1)
	{
		sigprocmask(SIG_BLOCK, &newmask, &oldmask);
		while(mqflag == 0)
			sigsuspend(&zeromask);

		mqflag = 0;
		mq_notify(mqd, &sigev);
	
		if(mq_receive(mqd, recv_buff, sizeof(recv_buff), &prio) != -1)
		{
			printf("recv: %s, %d\n", recv_buff, prio);
		}
		else
		{
			printf("mq_receive failed! %s\n", strerror(errno));
			goto remove_mqd;
		}
	}
	#elif 0
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &newmask, NULL);

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;

	if(mq_notify(mqd, &sigev) == -1)
	{
		printf("mq_notify failed! %s\n", strerror(errno));
		goto remove_mqd;
	}
	
	ssize_t n;
	int signo;
	while(1)
	{
		sigwait(&newmask, &signo); //block and wait for the signal
		if(signo == SIGUSR1)
		{
			mq_notify(mqd, &sigev);
			while((n = mq_receive(mqd, recv_buff, attr.mq_msgsize, &prio)) > 0)
				printf("recv: %s, %d\n", recv_buff, prio);
			if(errno != EAGAIN)
			{
				printf("mq_receive error! %s\n", strerror(errno));
				return -1;
			}
		}
	}
	#else
	sigev.sigev_notify = SIGEV_THREAD;
	sigev.sigev_value.sival_ptr = &mqd;
	sigev.sigev_notify_function = notify_thread;
	sigev.sigev_notify_attributes = NULL;

	if(mq_notify(mqd, &sigev) == -1)
	{
		printf("mq_notify failed! %s\n", strerror(errno));
		goto remove_mqd;
	}

	while(1)
	{
		pause();
	}
	#endif
	
#if 0
	printf("Begin to send...\n");
	char buff[64] = "Hello, POSIX Message!";
	prio = 0;
	if(mq_send(mqd, (const char *)&buff, sizeof(buff), prio) == -1)
	{
		printf("mq_send failed! %s\n", strerror(errno));
		goto remove_mqd;
	}

	prio = 1;
	if(mq_send(mqd, (const char *)&buff, sizeof(buff), prio) == -1)
	{
		printf("mq_send failed! %s\n", strerror(errno));
		goto remove_mqd;
	}
#endif

	if(mq_close(mqd) == -1)
	{
		printf("mq_close failed! %s\n", strerror(errno));
		goto remove_mqd;
	}

remove_mqd:
	if(mq_unlink(argv[1]) == -1)
	{
		printf("mq_unlink failed! %s\n", strerror(errno));
		return -1;
	}
	
	return 0;
}


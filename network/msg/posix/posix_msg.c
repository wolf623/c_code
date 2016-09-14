#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FILE_FLAG O_RDWR | O_CREAT
#define FILE_FLAG_RDWR O_RDWR

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
	mqd_t mqd = mq_open(argv[1], FILE_FLAG_RDWR, FILE_MODE, &attr);
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

#if 0
	printf("Begin to receive ...\n");
	char recv_buff[128] = {0};
	int prio = 0;
	if(mq_receive(mqd, recv_buff, sizeof(recv_buff), &prio) != -1)
	{
		printf("recv: %s, %d\n", recv_buff, prio);
	}
	else
	{
		printf("mq_receive failed! %s\n", strerror(errno));
		goto remove_mqd;
	}
#endif

	printf("Begin to send...\n");
	char buff[64] = "Hello, POSIX Message!";
	int prio = 0;
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

	return 0;
	
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


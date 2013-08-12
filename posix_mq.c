#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAXLINE		128

int
main(int argc, char *argv[])
{
	mqd_t mqd = 0;
	struct mq_attr attr;
	struct mq_attr old_attr;
	char *buff = NULL;
	int prio = 0;
	char *rece_buff = NULL;
	int rece_size = 0;
	unsigned int proip = 0;
	int result = 0;
	int mode = O_CREAT | O_RDWR;

	memset(&attr, 0, sizeof(attr));
	memset(&old_attr, 0, sizeof(old_attr));


	while( (result = getopt(argc, argv, "ne")) != -1)
	{
		switch(result)
		{
			case 'n': mode |= O_NONBLOCK;
				break;
			case 'e': mode |= O_EXCL;
				break;
			default: 
				break;
		}
	}

	if(optind != argc -1)
	{
		printf("Input error.\n");
		exit(0);
	}


	if(argc < 1 || argv[argc-1][0] != '/')
	{
		printf("Useage: ./a.out </name>\nThe name must begin with '/'\n");
		exit(0);
	}

	if( (buff = malloc(MAXLINE)) == NULL)
	{
		printf("malloc() failed\n");
		exit(0);
	}

	mqd = mq_open(argv[argc-1], mode, S_IREAD | S_IWRITE, NULL);
	if(mqd == -1)
	{
		printf("mq_open() failed\n");
		exit(0);
	}

	if(mq_getattr(mqd, &attr) != -1)
	{
		printf("Default: The mq_maxmsg = %ld, The mq_msgsize = %ld\n", attr.mq_maxmsg, attr.mq_msgsize);
	}
	
	attr.mq_maxmsg = 23;
	attr.mq_msgsize = 1024;
	if(mq_setattr(mqd, &attr, &old_attr) != -1)
	{
		printf("set the attr ok.\n");
		printf("The new value: the mq_maxmsg = %ld, the mq_msgsize = %ld\n", attr.mq_maxmsg, attr.mq_msgsize);
		printf("The old value: the mq_maxmsg = %ld, the mq_msgsize = %ld\n", old_attr.mq_maxmsg, old_attr.mq_msgsize);
	}

	prio = 2;
	buff = "Hello CASA";
	if(mq_send(mqd, buff, MAXLINE, prio) != -1)
	{
		printf("\nsend the message to the mqueue ok.\n");
		printf("The message: \"%s\", the prio = %d\n", buff, prio);
	}
	
	//Change the message
	prio = 3;
	buff = "Hello World";
	if(mq_send(mqd, buff, MAXLINE, prio) != -1)
	{
		printf("\nsend the message to the mqueue ok.\n");
		printf("The message: \"%s\", the prio = %d\n", buff, prio);
	}
	
	
	//use the mq_getattr() to set the receive buff size
	if(mq_getattr(mqd, &attr) != -1)
	{
		rece_size = attr.mq_maxmsg * attr.mq_msgsize;
		if( (rece_buff = malloc(rece_size)) == NULL)
		{	
			printf("malloc failed,then have to exit.\n");
			exit(0);
		}
	}
	
	//Receive the message use the function mq_receive()
	if(mq_receive(mqd, rece_buff, rece_size, &proip) != -1)
	{
		printf("\nReceive the message: \"%s\", the proip = %d\n", rece_buff, proip);
	}

	//if(mq_close(mqd) == -1)
	if(mq_unlink(argv[argc-1]) == -1)
	{
		printf("mq_unlink() failed\n");
		exit(0);
	}

	exit(0);
}

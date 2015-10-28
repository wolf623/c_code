/*
 * =====================================================================================
 *
 *       Filename:  rpc1.c
 *
 *    Description:  This include rpc1 client and rpc2 server
 *
 *        Version:  1.0
 *        Created:  10/09/14 10:21:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <rpc/rpc.h>


#include "rpc1.h"
#include "rpc2.h"


int main(int argc, char *argv[])
{
	//fflush(stdin);
	int type = 0;
	char buf[2]; //This at least must be bigger than 1
	char *endPtr = 0;
	char *host;

	if(argc < 2)
	{
		printf("Usage: %s server host\n", argv[0]);
		return  -1;
	}

	host = argv[1];

	printf("Usage: 1: printf time, 2: printf pid number, 0: exit\n");

	printf("Please input:");
	if(fgets(buf, sizeof(buf), stdin) == NULL)
	{
		return -2;
	}

	type = (int)(strtoul(buf, &endPtr, 0));
	printf("Your input is %d\n", type);

	if(type == 0)
	{
		printf("I will go exit...\n");
		return -23;
	}

	//(1)call rpc1 clnt to send type to rpc1 server
	pthread_param_t pthread_param;
	memcpy(pthread_param.host, host, sizeof(pthread_param.host));
	pthread_param.type = type;

	pthread_t pid1;
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_DETACHED);
	int rc1 = pthread_create(&pid1, &attr1, rpc1_rpc_prog_1, (void *)&pthread_param);
	pthread_attr_destroy(&attr1);
	if(rc1 != 0)
	{
		printf("Create rpc1_rpc_prog_1 pthread failed! %d\n", rc1);
		return -1;
	}

	//(2) call rpc2 server to receive and print the result
	pthread_t pid2;
	pthread_attr_t attr2;
	pthread_attr_init(&attr2);
	pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_DETACHED);
	int rc2 = pthread_create(&pid2, &attr2, rpc2_server, (void *)NULL);
	pthread_attr_destroy(&attr2);
	if(rc2 != 0)
	{
		printf("Create rpc2_server pthread failed! %d\n", rc2);
		return -1;
	}

	while(1);

	printf("exit ...\n");
	return 0;
}


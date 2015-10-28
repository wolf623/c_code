/*
 * =====================================================================================
 *
 *       Filename:  rpc2.c
 *
 *    Description:  This include rpc1 server and rpc2 client
 *
 *        Version:  1.0
 *        Created:  10/09/14 11:41:39
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

#include "rpc2.h"

int main(int argc, char *argv[])
{
	//(1) run rpc1 server to receive rpc1 client param
	pthread_t pid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	int rc = pthread_create(&pid, &attr, rpc1_server, (void *)NULL);
	if(rc != 0)
	{
		printf("Error: create rpc1_server pthread failed, %d\n", rc);
		return -1;
	}
	
	//(2) run rpc2 client to send result to rpc2 server to print out
	unsigned int num = 0;
	while(1)
	{
		//printf("num...%d\n", num);
		if(num > 100000000)
			//break;
			;
		else
			num++;
	}
	

	printf("exit...\n");
	return 0;
}

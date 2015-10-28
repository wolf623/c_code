/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "rpc1.h"

#define IP_ADDRESS(x)  (((x)>>24)&0xff), (((x)>>16)&0xff), (((x)>>8)& 0xff), ((x)&0xff)

int *
rpc1_rpcc_1_svc(rpc1_data_t *argp, struct svc_req *rqstp)
{
	static int  result;

	char buff[256] = {0};

	/*
	 * insert server code here
	 */
	//deal with the param from rpc1 client
	if(argp->type == 1) //time
	{
		result = 0;
		char timebuff[256] = {0};
		getSysTime_r(timebuff);
		sprintf((char *)buff, "type %d: current time: %s", argp->type, timebuff);	
	}
	else if(argp->type == 2) //pid number
	{
		result = 0;
		sprintf((char *)buff, "type %d: pid number %d", argp->type, getpid());	
	}
	else
	{
		printf("%s(): Error param...type %d\n", __FUNCTION__, argp->type);
		result = -1;
		return &result;
	}

	//call rpc2 clinet to send back result
	struct sockaddr_in *sin = svc_getcaller(rqstp->rq_xprt);
	int ip = sin->sin_addr.s_addr;
	struct in_addr in;
	in.s_addr = ip;
	//char host[256] = {0};
	//sprintf((char *)host, "%u.%u.%u.%u", IP_ADDRESS(ip));
	char *phost = inet_ntoa(in);
	printf("ip address: %s\n", phost);

	rpc2_rpc_prog_1(phost, buff);
	
	return &result;
}

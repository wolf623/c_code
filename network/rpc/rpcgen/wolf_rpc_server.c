/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "wolf_rpc.h"

int *
wolf_rpcc_1_svc(wolf_rpc_data_t *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

wolf_rpc_data_t *
wolf_rpcc_2_svc(wolf_rpc_data_t *argp, struct svc_req *rqstp)
{
	static wolf_rpc_data_t  result;

	/*
	 * insert server code here
	 */

	return &result;
}
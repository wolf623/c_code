/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "squarel.h"

squarel_out *
squarelprog_1_svc(squarel_in *argp, struct svc_req *rqstp)
{
	static squarel_out  result;

	/*
	 * insert server code here
	 */
	result.out = 23;
	return &result;
}

squarel_out *
squarelprog_2_svc(squarel_in *argp, struct svc_req *rqstp)
{
	static squarel_out  result;

	/*
	 * insert server code here
	 */

	return &result;
}
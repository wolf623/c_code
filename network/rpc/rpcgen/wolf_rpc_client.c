/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "wolf_rpc.h"


void
wolf_rpc_prog_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	wolf_rpc_data_t  wolf_rpcc_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, WOLF_RPC_PROG, WOLF_RPC_VERS1, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = wolf_rpcc_1(&wolf_rpcc_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


void
wolf_rpc_prog_2(char *host)
{
	CLIENT *clnt;
	wolf_rpc_data_t  *result_1;
	wolf_rpc_data_t  wolf_rpcc_2_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, WOLF_RPC_PROG, WOLF_RPC_VERS2, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = wolf_rpcc_2(&wolf_rpcc_2_arg, clnt);
	if (result_1 == (wolf_rpc_data_t *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	wolf_rpc_prog_1 (host);
	wolf_rpc_prog_2 (host);
exit (0);
}

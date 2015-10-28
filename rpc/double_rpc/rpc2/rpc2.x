/*
 * This is one of rpc
 */

#define RPC1_RPC_PROG_NUM 	0x38000024  //this should be bigger than 0x38000000

#define MAX_CHAR_LEN  256

/* data Structure */
struct _rpc2_data_t {
	char data[MAX_CHAR_LEN];
};

typedef struct _rpc2_data_t rpc2_data_t;

program RPC2_RPC_PROG {
	version RPC2_RPC_VERS1 {
		int  RPC2_RPCC(rpc2_data_t) = 1; /* Procedure number = 1 */
	} = 1; /* Version number = 1 */
} = RPC1_RPC_PROG_NUM;  /* Program number */



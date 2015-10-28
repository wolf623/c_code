/*
 * This is one of rpc
 */

#define RPC1_RPC_PROG_NUM 	0x38000023  //this should be bigger than 0x38000000

/* data Structure */
struct _rpc1_data_t {
	int type;	/* 1: time, 2: pid number */
	char data[0];
};

typedef struct _rpc1_data_t rpc1_data_t;

program RPC1_RPC_PROG {
	version RPC1_RPC_VERS1 {
		int  RPC1_RPCC(rpc1_data_t) = 1; /* Procedure number = 1 */
	} = 1; /* Version number = 1 */
} = RPC1_RPC_PROG_NUM;  /* Program number */



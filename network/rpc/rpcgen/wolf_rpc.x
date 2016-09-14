/*
  * wolf_rpc.x
  */

#define WOLF_RPC_PROG_NUM	0x38000023 //this should more than 0x38000000

struct wolf_rpc_data_s 
{
	int type; /* message type */
	int len; /* length of the data to follow */
	char data[1]; /* space holder for the data */
};
typedef struct wolf_rpc_data_s wolf_rpc_data_t;

program WOLF_RPC_PROG {
	version WOLF_RPC_VERS1 {
		int WOLF_RPCC(wolf_rpc_data_t) = 1; /* Procedure number = 1 */
	} = 1; /* Version number = 1 */

	version WOLF_RPC_VERS2 {
		wolf_rpc_data_t WOLF_RPCC(wolf_rpc_data_t) = 1; /* Procedure number = 1 */
	} = 2; /* Version number = 2	*/
} = WOLF_RPC_PROG_NUM; /* Program number */




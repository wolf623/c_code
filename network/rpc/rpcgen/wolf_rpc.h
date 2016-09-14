/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _WOLF_RPC_H_RPCGEN
#define _WOLF_RPC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct wolf_rpc_data_s {
	int type;
	int len;
	char data[1];
};
typedef struct wolf_rpc_data_s wolf_rpc_data_s;

typedef wolf_rpc_data_s wolf_rpc_data_t;

#define WOLF_RPC_PROG 0x38000023
#define WOLF_RPC_VERS1 1

#if defined(__STDC__) || defined(__cplusplus)
#define WOLF_RPCC 1
extern  int * wolf_rpcc_1(wolf_rpc_data_t *, CLIENT *);
extern  int * wolf_rpcc_1_svc(wolf_rpc_data_t *, struct svc_req *);
extern int wolf_rpc_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define WOLF_RPCC 1
extern  int * wolf_rpcc_1();
extern  int * wolf_rpcc_1_svc();
extern int wolf_rpc_prog_1_freeresult ();
#endif /* K&R C */
#define WOLF_RPC_VERS2 2

#if defined(__STDC__) || defined(__cplusplus)
extern  wolf_rpc_data_t * wolf_rpcc_2(wolf_rpc_data_t *, CLIENT *);
extern  wolf_rpc_data_t * wolf_rpcc_2_svc(wolf_rpc_data_t *, struct svc_req *);
extern int wolf_rpc_prog_2_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
extern  wolf_rpc_data_t * wolf_rpcc_2();
extern  wolf_rpc_data_t * wolf_rpcc_2_svc();
extern int wolf_rpc_prog_2_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_wolf_rpc_data_s (XDR *, wolf_rpc_data_s*);
extern  bool_t xdr_wolf_rpc_data_t (XDR *, wolf_rpc_data_t*);

#else /* K&R C */
extern bool_t xdr_wolf_rpc_data_s ();
extern bool_t xdr_wolf_rpc_data_t ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_WOLF_RPC_H_RPCGEN */
/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPC2_H_RPCGEN
#define _RPC2_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct _rpc2_data_t {
	char data[256];
};
typedef struct _rpc2_data_t _rpc2_data_t;

typedef _rpc2_data_t rpc2_data_t;

#define RPC2_RPC_PROG 0x38000024
#define RPC2_RPC_VERS1 1

#if defined(__STDC__) || defined(__cplusplus)
#define RPC2_RPCC 1
extern  int * rpc2_rpcc_1(rpc2_data_t *, CLIENT *);
extern  int * rpc2_rpcc_1_svc(rpc2_data_t *, struct svc_req *);
extern int rpc2_rpc_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define RPC2_RPCC 1
extern  int * rpc2_rpcc_1();
extern  int * rpc2_rpcc_1_svc();
extern int rpc2_rpc_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr__rpc2_data_t (XDR *, _rpc2_data_t*);
extern  bool_t xdr_rpc2_data_t (XDR *, rpc2_data_t*);

#else /* K&R C */
extern bool_t xdr__rpc2_data_t ();
extern bool_t xdr_rpc2_data_t ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

void *rpc2_server();

#endif /* !_RPC2_H_RPCGEN */
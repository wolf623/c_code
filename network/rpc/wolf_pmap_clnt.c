/*
  * new added by wolf
  */
  
#include "wolf_rpc.h"

/////////////////////////////////////////////////////////////////////////

#define IP_ADDR(x) (((x)>>24)&0xff), (((x)>>16)&0xff), (((x)>>8)&0xff), ((x)&0xff)

int connect_nb(int fd, struct sockaddr_in *p_addr, int ms)
{
	struct timeval timeout;
	timeout.tv_sec = ms / 1000;
	timeout.tv_usec = (ms % 1000) * 1000;

	if(connect(fd, (struct sockaddr *)p_addr, sizeof(struct sockaddr_in)) < 0)
	{
		if(errno != EINPROGRESS)
		{
			fprintf(stderr, "%s():%d: fd %d, connect to %u.%u.%u.%u failed\n", __FUNCTION__, __LINE__, fd, IP_ADDR(p_addr->sin_addr.s_addr));
			return -1;
		}
	}

	fd_set wrset;
	FD_ZERO(&wrset);
	FD_SET(fd, &wrset);
	int ec = select(fd+1, NULL, &wrset, NULL, &timeout);

	int sock_err;
	socklen_t optlen = sizeof(sock_err);
	if(getsockopt(fd, SOL_SOCKET, SO_ERROR, &sock_err, &optlen) < 0)
	{
		fprintf(stderr, "%s():%d: fd %d, connect() to %u.%u.%u.%u failed, %m\n", __FUNCTION__, __LINE__, fd, IP_ADDR(p_addr->sin_addr.s_addr));
		return -1;
	}

	if(ec == 1 && sock_err == 0)
	{
		return 0; //successfully connected
	}

	fprintf(stderr, "%s():%d: fd %d, connect() to %u.%u.%u.%u failed, %m\n", __FUNCTION__, __LINE__, fd, IP_ADDR(p_addr->sin_addr.s_addr));
	return -1;	
}

int create_tcp_sock_w_src(u_int32_t src_ip, u_int16_t port)
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
	{
		fprintf(stderr, "%s():%d: cannot create udp socket: %m\n", __FILE__, __LINE__);
		return -1;
	}

	struct sockaddr_in addr;
	memset((char *) &addr, 0, sizeof(addr));
	
	size_t len = sizeof(struct sockaddr_in);
	addr.sin_addr.s_addr = htonl(src_ip); // INADDR_ANY == 0
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if(bind(sock, (struct sockaddr *)&addr, len) < 0)
	{
		fprintf(stderr, "%s():%d: cannot bind tcp socket %m\n", __FILE__, __LINE__);
		close(sock);
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&addr, len) < 0)
	{
		fprintf(stderr, "%s():%d: cannot connect tcp socket %m\n", __FILE__, __LINE__);
		close(sock);
		return -1;
	}

	return sock;
}

int create_tcp_sock()
{
	return create_tcp_sock_w_src(INADDR_ANY, 0);
}

int create_udp_sock_w_src(u_int32_t src_ip, u_int16_t port)
{
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock < 0) 
	{
		fprintf(stderr, "%s():%d: cannot create udp socket: %m\n", __FILE__, __LINE__);
		return -1;
	}

	#if 0
	struct sockaddr_in addr;
	memset((char *) &addr, 0, sizeof(addr));
	
	size_t len = sizeof(struct sockaddr_in);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // src_ip
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if(bind(sock, (struct sockaddr *)&addr, len) < 0)
	{
		fprintf(stderr, "%s():%d: cannot bind udp socket, %m, src_ip: %u.%u.%u.%u\n", __FUNCTION__, __LINE__, IP_ADDR(addr.sin_addr.s_addr));
		close(sock);
		return -1;
	}
	#endif
	
	return sock;
}

int create_udp_sock()
{
	return create_udp_sock_w_src(INADDR_ANY, 0);
}

//////////////////////////////////////////////////////////////////////////

static const struct timeval _timeout = {3, 0};
static const struct timeval _tottimeout = {6, 0};

int __create_tcp_sock_w_src(struct sockaddr_in *addr, u_int32_t src_ip, int ms)
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0)
	{
		return -1;
	}
	
	struct sockaddr_in laddr;
	socklen_t namelen = sizeof(laddr);
	laddr.sin_family = AF_INET;
	laddr.sin_port = 0;
	laddr.sin_addr.s_addr = htonl(src_ip);
	
	if(bind(sock, (struct sockaddr *)&laddr, namelen) < 0)
	{
		printf("%s(): create socket for %u.%u.%u.%u failed: %m\n", __FUNCTION__, IP_ADDR(addr->sin_addr.s_addr));
		close(sock);
		return -1;
	}
	
	int ec = 0;
	if(ms > 0)
	{
		unsigned long imode = 1;
		int status = ioctl(sock, FIONBIO, &imode);
		if(status != 0)
		{
			printf("%s(): %d: sock %d, ioctl failed with error: %m\n", __FUNCTION__, __LINE__, sock);
			close(sock);
			return -1;
		}
		
		ec = connect_nb(sock, addr, ms);
	}
	else
	{
		ec = connect(sock, (struct sockaddr *)addr, namelen);		
	}
	
	if(ec < 0)
	{
		printf("%s(): connect to %u.%u.%u.%u failed: %m\n", __FUNCTION__, IP_ADDR(addr->sin_addr.s_addr), sock);
		close(sock);
		return -1;
	}
	
	return sock;
}

u_int16_t wolf_pmap_getport(u_int32_t src_ip, struct sockaddr_in *addr, u_int32_t program, u_int16_t version, u_int16_t protocol, int ms)
{
	int port = 0;
	int sock = -1;
	CLIENT *client = NULL;
	struct pmap parms;
	bool closeit = false;
	
	addr->sin_port = htons(PMAPPORT);
	if(protocol == IPPROTO_TCP)
	{
		sock = __create_tcp_sock_w_src(addr, src_ip, ms);
		if(sock >= 0)
		{
			closeit = true;
			
			client = (clnttcp_create)(addr, PMAPPROG, PMAPVERS, &sock,
								 RPCSMALLMSGSIZE, RPCSMALLMSGSIZE);
		}
	}
	else
	{
		sock = create_udp_sock_w_src(src_ip, 0);
		if(sock >= 0)
		{
			printf("%s(): get udp sock..\n", __FUNCTION__);
			closeit = true;
			
			client = (clntudp_bufcreate)(addr, PMAPPROG, PMAPVERS, _timeout,
					&sock, RPCSMALLMSGSIZE, RPCSMALLMSGSIZE);
		}
		else
		{
			printf("%s(): can not get udp sock..\n", __FUNCTION__);
		}
	}
	
	if(client != (CLIENT *)NULL)
	{
		struct rpc_createerr *ce = &get_rpc_createerr();
		parms.pm_prog = program;
	    parms.pm_vers = version;
	    parms.pm_prot = protocol;
	    parms.pm_port = 0;    /* not needed or used */
	    if(CLNT_CALL(client, PMAPPROC_GETPORT, (xdrproc_t)(xdr_pmap),
	    	(caddr_t)&parms, (xdrproc_t)(xdr_u_short),
	    	(caddr_t)&port, _tottimeout) != RPC_SUCCESS)
	    {
	    	printf("%s(): I am here...0\n", __FUNCTION__);
	    	ce->cf_stat = RPC_PMAPFAILURE;
	    	clnt_geterr (client, &ce->cf_error);
		}
		else if(port == 0)
		{
			printf("%s(): I am here...1\n", __FUNCTION__);
			ce->cf_stat = RPC_PROGNOTREGISTERED;
		}
		
		CLNT_DESTROY(client);
	}	
	else
	{
		//error
	}
	
	if(closeit)
	{
		(void)close(sock);	
	}
	
	addr->sin_port = 0;
	
	return port;
}

//////////////////////////////////////////////////////////////////////////

CLIENT *clnt_create_w_src (u_int32_t dst_ip, u_int16_t prog, u_int16_t vers, int proto, u_int32_t src_ip, int timeout)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_addr.s_addr = htonl(dst_ip); // INADDR_ANY == 0
	addr.sin_family = AF_INET;
	int rport = wolf_pmap_getport(0/*src_ip*/, &addr, prog, vers, proto, timeout);
	if(rport == 0)
	{
		fprintf(stderr, "%s(): get port failed!\n", __FUNCTION__);
		//return NULL;
	}
	addr.sin_port = htons(rport);
	
	int ec, sock = 0;
	struct timeval tv;
	CLIENT *client = NULL;
	
	switch(proto)
	{
		case IPPROTO_UDP:
			sock = create_udp_sock_w_src(src_ip, 0);
			if(sock < 0)
			{
				fprintf(stderr, "%s(): create udp sock failed!\n", __FUNCTION__);
				return NULL;
			}
			tv.tv_sec = 5; //5s
			tv.tv_usec = 0;
			client = (clntudp_create)(&addr, prog, vers, tv, &sock);
			if(client == NULL)
			{
				fprintf(stderr, "%s(): create udp rpc client failed!\n", __FUNCTION__);
				close(sock);
				return NULL;
			}
			clnt_control(client, CLSET_FD_CLOSE, NULL);
			break;
		case IPPROTO_TCP:
			if(src_ip == 0)
			{
				sock = RPC_ANYSOCK;
				client = (clnttcp_create)(&addr, prog, vers, &sock, 0, 0);
				if(client == NULL)
				{
					fprintf(stderr, "%s():%d: create tcp rpc client failed!\n", __FUNCTION__, __LINE__);
					close(sock);
					return NULL;
				}
			}
			else
			{
				sock = create_tcp_sock_w_src(src_ip, 0);
				if(sock < 0)
				{
					fprintf(stderr, "%s(): create tcp sock failed!\n", __FUNCTION__);
					return NULL;
				}
				
				if(timeout > 0)
				{
					ec = connect_nb(sock, &addr, timeout);
				}
				else
				{
					ec = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
				}
				
				if(ec < 0)
				{
					fprintf(stderr, "%s(): connect() failed, prog %d, src %u.%u.%u.%u, dst %u.%u.%u.%u, rpot %d\n",
					__FUNCTION__, prog, IP_ADDR(src_ip), IP_ADDR(dst_ip), rport);
					close(sock);
					return NULL;
				}
				
				client = (clnttcp_create)(&addr, prog, vers, &sock, 0, 0);
				if(client == NULL)
				{
					fprintf(stderr, "%s():%d: create tcp rpc client failed!\n", __FUNCTION__, __LINE__);
					close(sock);
					return NULL;
				}
				
				clnt_control(client, CLSET_FD_CLOSE, NULL);
			}
			break;
		default:
			fprintf(stderr, "%s(): Unknow proto type %d\n", __FUNCTION__, proto);
			return NULL;
			break;
	}
		
	return client;
}

 
CLIENT *new_clnt_create (const char *dst_host, const char *src_host, u_int16_t prog, u_int16_t vers, int proto)
{	
	u_int32_t dst_ip = inet_addr(dst_host);
	u_int32_t src_ip = inet_addr(src_host);
	return clnt_create_w_src(dst_ip, prog, vers, proto, src_ip, 0);
}

//////////////////////////////////////////////////////////////////////////

static bool_t
__get_myaddress (struct sockaddr_in *addr)
{
	memset(addr, 0, sizeof(*addr));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = htonl(0x7F000001);// loopback lo ip address: 127.0.0.1
	addr->sin_port = htons(PMAPPORT);
	return TRUE;
}

static const struct timeval timeout = {5, 0};
static const struct timeval tottimeout = {60, 0};

/*
 * Set a mapping between program,version and port.
 * Calls the pmap service remotely to do the mapping.
 */
bool_t wolf_pmap_set (u_long program, u_long version, int protocol, u_short port)
{
  struct sockaddr_in myaddress;
  int socket = -1;
  CLIENT *client;
  struct pmap parms;
  bool_t rslt;

  if (!__get_myaddress (&myaddress))
    return FALSE;

  socket = create_udp_sock();
  if (socket < 0)
  {
    return FALSE;
  }
  client = clntudp_bufcreate(&myaddress, PMAPPROG, PMAPVERS,
				      timeout, &socket, RPCSMALLMSGSIZE,
				      RPCSMALLMSGSIZE);
  if (client == (CLIENT *) NULL)
    return (FALSE);
  parms.pm_prog = program;
  parms.pm_vers = version;
  parms.pm_prot = protocol;
  parms.pm_port = port;
  if (CLNT_CALL (client, PMAPPROC_SET, (xdrproc_t)(xdr_pmap),
		 (caddr_t)&parms, (xdrproc_t)(xdr_bool), (caddr_t)&rslt,
		 tottimeout) != RPC_SUCCESS)
    {
      clnt_perror(client, ("Cannot register service"));
      rslt = FALSE;
    }
  CLNT_DESTROY (client);
  /* (void)close(socket); CLNT_DESTROY closes it */
  close(socket);// need to close the provioning socket
  return rslt;
}

/*
 * Remove the mapping between program,version and port.
 * Calls the pmap service remotely to do the un-mapping.
 */
bool_t wolf_pmap_unset (u_long program, u_long version)
{
  struct sockaddr_in myaddress;
  int socket;
  CLIENT *client;
  struct pmap parms;
  bool_t rslt;

  if (!__get_myaddress (&myaddress))
    return FALSE;
  socket = create_udp_sock();
  if (socket < 0)
  {
    return FALSE;
  }
  
  client = clntudp_bufcreate(&myaddress, PMAPPROG, PMAPVERS,
				      timeout, &socket, RPCSMALLMSGSIZE,
				      RPCSMALLMSGSIZE);
  if (client == (CLIENT *) NULL)
  {
    return FALSE;
  }
  parms.pm_prog = program;
  parms.pm_vers = version;
  parms.pm_port = parms.pm_prot = 0;
  CLNT_CALL (client, PMAPPROC_UNSET, (xdrproc_t)(xdr_pmap),
	     (caddr_t)&parms, (xdrproc_t)(xdr_bool), (caddr_t)&rslt,
	     tottimeout);
  CLNT_DESTROY (client);
  /* (void)close(socket); CLNT_DESTROY already closed it */
  close(socket);// need to close the provioning socket
  return rslt;
}
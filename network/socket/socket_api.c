#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/epoll.h>

/* set fd as non-block mode */
int set_fd_nb(int fd)
{
	int val;
	val = fcntl(fd, F_GETFL);
	if (val < 0)
	{
		fprintf(stderr, "%s(): fcntl(F_GETFL) for fd %d failed, %m\n", __FUNCTION__, fd);
		return -1;
	}
	else
	{
		if (fcntl(fd, F_SETFL, val | O_NONBLOCK) < 0)
		{
			fprintf(stderr, "%s(): fcntl(F_SETFL, O_NONBLOCK) for fd %d failed, val %d, %m\n", __FUNCTION__, fd, val);
			return -2;
		}
	}

	return 0;
}


int my_read_fd(int sock_fd, char *buf, int len, int timeout_ms)
{
	struct pollfd plfd;

	/*
	struct sockaddr  peer;
	int peer_len;	
	*/
	
	if (len == 0)
		return 0;
	
	plfd.fd = sock_fd;
	plfd.events = POLLIN;
	while (TRUE)
	{
		switch (poll(&plfd, 1, timeout_ms))
		{
			case 0:
				return 0; // time up

			case -1:
				if (errno == EINTR)
					continue;
				return MY_ERR_SOCKET;
		}
		
		break;
	}

	len = read(sock_fd, buf, len);
	
	switch (len)
	{
		case 0:
			// premature eof
			return MY_ERR_CONNECTION_RESET_BY_PEER; // it's really a error

		case -1:
			//cannot receive;
			break;
	}
	
	return len;
}

/*
 @params:
                timeout - a timeout in milliseconds, a negative value means infinite timeout.
*/
int fd_wait_for_io(int fd, BOOLEAN for_read, int timeout)
{
	struct pollfd pfd;
	int ec;

	pfd.fd     = fd;
	pfd.events = for_read ? POLLIN: POLLOUT;

	do {
		ec = poll(&pfd, 1, timeout);
	} while (ec == -1 && errno == EINTR);
	if (ec == 0) {
		return MY_ERR_TIMEUP;
	}
	else if (ec > 0) {
		return MY_OK;
	}
	else {
		return errno? errno: MY_ERR_UNKNOWN_SYS_ERROR;
	}
}


/*
 @params:
                timeout - a timeout in milliseconds  
*/
int sock_recv(int sockfd, char *buf, int len, int *p_total_rlen, int timeout, int recv_all)
{
	int recvlen;
	int rc;
	/*
	struct sockaddr  peer;
	int peer_len;	
	*/

	while (len > 0)
	{
		do {
			recvlen = read(sockfd, buf, len);
		} while (recvlen == -1 && errno == EINTR);

		if (recvlen == 0) {
			// premature eof // fix bug 23495
			return MY_ERR_CONNECTION_RESET_BY_PEER;
			/*
		    peer_len = sizeof(peer);
		    if (getpeername(sockfd, &peer, (u_int32_t *)&peer_len) == -1) {
		        return  MY_ERR_CONNECTION_RESET_BY_PEER;
		    }
		    */
		}
		else
		{
			while ((recvlen == -1) && (errno == EAGAIN || errno == EWOULDBLOCK) && (timeout > 0)) {
				rc = fd_wait_for_io(sockfd, TRUE, timeout);
				if (rc != MY_OK) 
				{
					return rc;
				} else {
					do {
						recvlen = read(sockfd, buf, len);
					} while (recvlen == -1 && errno == EINTR);
					if (recvlen == 0) {
						// premature eof // fix bug 23495
						return MY_ERR_CONNECTION_RESET_BY_PEER;
					}
				}
			}
			if (recvlen == -1) {
			    // other error
				return MY_ERR_SOCKET;
			}

			buf += recvlen;
			len -= recvlen;	
			(*p_total_rlen) += recvlen;
		}
		if (!recv_all)
			break;
	}
	
	return MY_OK;
}

/*
 @params:
                timeout - a timeout in milliseconds  
*/
int sock_send(int sockfd, const char *buf, int len, int *txlen, int timeout)
{
#define EDG_SEND_RETRY 128
	(*txlen) = 0;
	int rc;
	int i;	
	int errsv = 0;

	while(len > 0)
	{
		for (i = 0; i < EDG_SEND_RETRY; i++)
		{
			(*txlen) = write(sockfd, buf, len);
			if ((*txlen) != -1)
			{
				break;
			}
			else
			{
				errsv = errno; // make debug easier
				if (errsv != EINTR)
				{
					break;
				}
			}
		}

		while ((*txlen) == -1 && timeout > 0) 
		{
			errsv = errno;
			if (errsv != EAGAIN && errsv != EWOULDBLOCK)
			{
				break;
			}
			
			rc = fd_wait_for_io(sockfd, FALSE, timeout);
			if (rc != MY_OK) {
				///fprintf(stderr, "%s():%d: send to socket %d failed, i = %d, len %d, timeout %d, pid %d, %s, rc %s\n", __FUNCTION__, __LINE__, sockfd, i, len, timeout, getpid(), strerror(errsv), cdb_strerr(rc));
				return rc;
			}
			else {
				for (i = 0; i < EDG_SEND_RETRY; i++)
				{
					(*txlen) = write(sockfd, buf, len);
					if ((*txlen) != -1)
					{
						break;
					}
					else
					{
						errsv = errno; // make debug easier
						if (errsv != EINTR)
						{
							break;
						}
					}
				}
			}
		}
		
		if ((*txlen) == -1) {
			return MY_ERR_SOCKET;
		}		
		
		buf += (*txlen);
		len -= (*txlen);
	}
	
	return MY_OK;
}

/*
 @params:
                timeout - a timeout in milliseconds  
*/
int sock_read(int sockfd, char *buf, int len, int *p_total_rlen, int timeout, int recv_all)
{
	int recvlen;

	while (len > 0)
	{
		recvlen = my_read_fd(sockfd, buf, len, timeout);

		if (recvlen == 0) {
			// time up
			return MY_ERR_TIMEUP;
		}
		
		if (recvlen < 0)
		{
			return recvlen;
		}

		buf += recvlen;
		len -= recvlen;	
		(*p_total_rlen) += recvlen;
		
		if (!recv_all)
			return MY_OK;
	}
	
	return MY_OK;
}

int my_read_sock(int sock_fd, char *buf, int len)
{
	struct pollfd plfd;
	int milliseconds = 2000;

	/*
	struct sockaddr  peer;
	int peer_len;	
	*/
	
	if (len == 0)
		return 0;
	
	plfd.fd = sock_fd;
	plfd.events = POLLIN;
	while (TRUE)
	{
		switch (poll(&plfd, 1, milliseconds))
		{
			case 0:
				return 0; // time up

			case -1:
				if (errno == EINTR)
					continue;
				return MY_ERR_SOCKET;
		}
		
		break;
	}

	len = read(sock_fd, buf, len);
	
	switch (len)
	{
		case 0:
			// premature eof
			/*
			peer_len = sizeof(peer);
			if (getpeername(sock_fd, &peer, (u_int32_t *)&peer_len) == -1) {
				len = MY_ERR_CONNECTION_RESET_BY_PEER;
			}
			*/
			len = MY_ERR_CONNECTION_RESET_BY_PEER; // it's really a error
			break;

		case -1:
			//cannot receive;
			break;
	}
	
	return len;
}

int my_recv(int sockfd, char *buf, int len, int *p_total_rlen, int timeout, int recv_all)
{
	fd_set fds;
	int rc;
	struct timeval to_tv = {0};
	
	while(1)
	{
		FD_ZERO(&fds);
		FD_SET(sockfd, &fds);

		to_tv.tv_sec = 10;
		rc = select(sockfd+1, &fds, NULL, NULL, &to_tv);

		if(rc > 0)
		{
			if(FD_ISSET(sockfd, &fds)
			{
				if((rc = recv(sockfd, buf, len, 0)) <= 0)
				{
					if(rc == -1)
					{
						printf("%s(): recv failed! %s\n", __FUNCTION__, strerror(errno));
					}
					continue;
				}		
			}
		}
		sleep(1);
	}
	
	return 0;
}

int epoll_recv(int sockfd, char *buf, int len, int *p_total_rlen, int timeout, int recv_all)
{
	int efd, ec, fd, nread, nwrite;
	struct epoll_event ev;
	struct epoll_event *events;
	int i, maxevents = 100;
	struct sockaddr_in clientaddr;
	size_t clilen = sizeof(clientaddr);
	
	efd = epoll_create(maxevents);
	if(efd == -1)
	{
		printf("%s(): epoll_create1 failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}

	ev.data.fd = sockfd;
	ev.events = EPOLLIN | EPOLIET;
	rc = epoll_ctl(efd, EPOLL_CTL_ADD, &ev);
	if(rc == -1)
	{
		printf("%s(): epoll_ctl failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}

	events = malloc(sizeof(ev)*maxevents);
	if(events == NULL)
	{
		return -1;
	}

	while(1)
	{
		int nfds = epoll_wait(efd, events, maxevents, -1);
		if(nfds == -1)
		{
			printf("%s(): epoll_wait failed\n", __FUNCTION__);
			break;
		}

		for(i=0; i<nfds; i++)
		{
			if(events[i].data.fd == sockfd)
			{
				int new_fd = accept(sockfd, (struct sockaddr *)&clientaddr, &clilen);
				if(new_fd < 0)
				{
					 if(errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
					 {
					 	printf("accpet failed!, %s\n", strerror(errno));
					 }
					continue;
				}
				else
				{
					//accept success
					ev.data.fd = new_fd;
					ev.events = EPOLLIN|EPOLLET;
					epoll_ctl(efd, EPOLL_CTL_ADD, new_fd, &ev);
				}
			}
			else if(events[i].events & EPOLLIN)
			{
				if((fd = events[i].data.fd) < 0)
				{
					printf("fd < 0, continue...\n");
					continue;
				}
				
				if((nread = read(fd, buf, sizeof(buf))) < 0)
				{
					if(errno == ECONNRESET)
					{
						close(fd);
						events[i].data.fd = -1;
					}
					else
					{
						printf("read error!\n");
					}
				}
				else if(nread == 0)
				{
					close(fd);
					events[i].data.fd = -1;
				}

				printf("read message: %s\n", buf);

				ev.data.fd = fd;
				ev.events = EPOLLOUT | EPOLLET;
				epoll_ctl(efd, EPOLL_CTL_MOD, fd, &ev);
			}
			else if(events[i].events & EPOLLOUT)
			{
				if((fd = events[i].data.fd) < 0)
				{
					printf("write fd < 0, continue...\n");
					continue;
				}

				char *p = "Hello, I am client";
				write(fd, p, strlen(p));

				ev.data.fd = fd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(efd, EPOLL_CTL_MOD, fd, &ev);
			}
			else
			{
				printf("something is error!\n");
				break;
			}
		}
	}

	return 0;
}


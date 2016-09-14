#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>

int epoll_recv(int sockfd, char *buf, int len, int *p_total_rlen, int timeout, int recv_all);

int main(int argc,char *argv[])
{
	struct sockaddr_in ser_addr;
	struct sockaddr_in cli_addr;
	char msg_buffer[64] = {0}; //message buffer
	int socket_fd; //listening socket
	int client_fd; //accept socket
	int server_port = 8200;

	//(1)create a socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		printf("create socket failed!!!, %s\n", strerror(errno));
		return -1;
	}

	int addrlen = sizeof(struct sockaddr_in);
	bzero(&ser_addr, addrlen);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(server_port);
	
	//(2) bind the server address
	if(bind(socket_fd, (struct sockaddr *)&ser_addr, addrlen) < 0)
	{
		printf("bind failed!, %s\n", strerror(errno));
		close(socket_fd);
		return -1;
	}

	int send_buffer_size = 65535;
	if(setsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &send_buffer_size, sizeof(send_buffer_size)) < 0)
	{
		printf("%s(): setsockopt failed\n", __FUNCTION__);
		return -1;
	}
			
	//(3)listen for the socket
	if(listen(socket_fd, 10) < 0)
	{
		printf("listen socket failed!, %s\n", strerror(errno));
		close(socket_fd);
		return -1;
	}
	
	epoll_recv(socket_fd, msg_buffer, sizeof(msg_buffer), NULL, -1, 1);
	
	close(socket_fd);
	
	return 0;
}

int setnonblocking(int sockfd)
{
	int opts;
	opts = fcntl(sockfd, F_GETFL);
	if(opts < 0)
	{
		printf("fcntl get failed.!\n");
		return -1;
	}

	opts = opts | O_NONBLOCK;
	if(fcntl(sockfd, F_SETFL, opts) < 0)
	{
		printf("fcntl set failed!\n");
		return -1;
	}

	return 0;
}

int epoll_recv(int sockfd, char *buf, int len, int *p_total_rlen, int timeout, int recv_all)
{
	int efd, rc, fd, nread, nwrite;
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
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
	ev.events = EPOLLIN | EPOLLET;
	//ev.events = EPOLLIN;
	rc = epoll_ctl(efd, EPOLL_CTL_ADD, sockfd, &ev);
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

		printf("nfds: %d\n", nfds);
		for(i=0; i<nfds; i++)
		{
			if(events[i].data.fd == sockfd)
			{
				int new_fd = accept(sockfd, (struct sockaddr *)&clientaddr, (socklen_t *)&clilen);
				if(new_fd == -1)
				{
					 if(errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
					 {
					 	printf("accpet failed!, %s\n", strerror(errno));
					 }
					break;
				}
				
				
				//accept success
				ev.data.fd = new_fd;
				ev.events = EPOLLIN|EPOLLET;
				//ev.events = EPOLLIN;
				epoll_ctl(efd, EPOLL_CTL_ADD, new_fd, &ev);
			}
			else if(events[i].events & EPOLLIN)
			{
				if((fd = events[i].data.fd) < 0)
				{
					printf("fd < 0, continue...\n");
					continue;
				}

				int done = 0;
				setnonblocking(fd);
				
				while(1)
				{
					nread = read(fd, buf, len);
					//nread = recv(fd, buf, len, MSG_DONTWAIT);
					if(nread == -1)
					{
						/* If errno == EAGAIN, that means we have read all data. So go back to the main loop. */
						if(errno == EAGAIN)
						{
							done = 1;
							break;
						}
						else if(errno == ECONNRESET)
						{
							//client send RST
							done = 1;
							break;
						}
						else if(errno == EINTR)
						{
							//interrupted by signal
							continue;
						}
						else
						{
							printf("read error!\n");
							done = 1;
						}
						break;
					}
					else if(nread == 0)
					{
						/* End of file. The remote has closed the  connection. */
						done = 1;
						break;
					}

					printf("%s(): read message: %s\n", __FUNCTION__, buf);
				}

				
				ev.data.fd = fd;
				ev.events = EPOLLOUT | EPOLLET;
				//ev.events = EPOLLOUT;
				epoll_ctl(efd, EPOLL_CTL_MOD, fd, &ev);
			}
			else if(events[i].events & EPOLLOUT)
			{
				if((fd = events[i].data.fd) < 0)
				{
					printf("write fd < 0, continue...\n");
					continue;
				}

				//setnonblocking(fd);
				char *p = "Hello, I am server";
				int data_size = strlen(p)+1;
				int n_send = data_size;
				printf("data size %d\n", n_send);
				while(n_send > 0)
				{
					int nwrite = write(fd, p+data_size-n_send, n_send);
					if(n_send == -1)
					{
						if(errno == EAGAIN)
						{
							//send all data
						}
						else if(errno == ECONNRESET)
						{
							//client send RST
							break;
						}
						else if(errno == EINTR)
						{
							//interrupted by signal
							continue;
						}
						else
						{
							printf("write error!\n");
							break;
						}
						break;
					}
					else if(n_send == 0)
					{
						//client is closed
						break;
					}
					
					n_send -= nwrite;
				}

				ev.data.fd = fd;
				ev.events = EPOLLIN | EPOLLET;
				//ev.events = EPOLLIN;
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



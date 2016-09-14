#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

	while(1)
	{
		//(4)wait for client to connect to server
		client_fd = accept(socket_fd, (struct sockaddr *)&cli_addr, &addrlen);
		if(client_fd <= 0)
		{
			printf("accept error! %s\n", strerror(errno));
			close(socket_fd);
			return -1;
		}
		else
		{
			//(5)receive client's request 
			recv(client_fd, msg_buffer, sizeof(msg_buffer)-1, 0);
			printf("received a connection from %s, msg %s\n", inet_ntoa(cli_addr.sin_addr), msg_buffer);
			strcpy(msg_buffer, "hi,I am server!");
            send(client_fd, msg_buffer, sizeof(msg_buffer), 0);

			int window_size = 0, size = sizeof(window_size);
			
			if(getsockopt(socket_fd, SOL_SOCKET, SO_SNDBUF, &window_size, &size) < 0)
			{
				printf("%s(): getsockopt send-buffer failed!\n", __FUNCTION__);
				return -1;
			}

			printf("send buffer size: %d\n", window_size);
	
			if(getsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &window_size, &size) < 0)
			{	
				printf("%s(): getsockopt recv-buffe failed!\n", __FUNCTION__);
				return -1;
			}

			printf("recv buffer size: %d\n", window_size);
           
            close(client_fd); 
		}
	}

	close(socket_fd);
	
	return 0;
}


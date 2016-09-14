#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in ser_addr;
	char msg_buffer[64] = {0};
	int addrlen = 0;
	int socket_fd;
	int server_port = 8200;

	//(1)create a socket
	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("create socket failed!\n", strerror(errno));
		return -1;
	}

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(server_port);
	addrlen = sizeof(struct sockaddr_in);
	
	//(2)connect to the server
	if(connect(socket_fd, (struct sockaddr *)&ser_addr, addrlen) < 0)
	{
		printf("connect to server failed!\n", strerror(errno));
		close(socket_fd);
		return -1;
	}

	strcpy(msg_buffer, "Hello, I am client!\n");
	sendto(socket_fd, msg_buffer, strlen(msg_buffer)+1, 0, (struct sockaddr *)&ser_addr, addrlen);
	recvfrom(socket_fd, msg_buffer, sizeof(msg_buffer), 0, NULL, 0);
	printf("rece from server's message %s\n", msg_buffer);

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
	
	close(socket_fd);
	
	return 0;
}


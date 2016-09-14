#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 8100

int main(int argc, char *argv[])
{
	struct sockaddr_in addr_serv, addr_clie;
	int sockfd;
	int addrlen = sizeof(addr_clie);
	int addrClientLen = sizeof(addr_clie);
	
	//(1)create socket
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("%s(): create socket failed %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}

	memset(&addr_clie, 0, sizeof(addr_clie));
	
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_port = htons(SERVER_PORT);
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_serv.sin_family = AF_INET;
	
	//(2)bind
	if(bind(sockfd, (struct sockaddr *)&addr_serv, addrlen) < 0)
	{
		printf("%s(): bind failed, %s\n", __FUNCTION__, strerror(errno));
		return -1;
	}

	char rcv_buffer[128] = {0};
	char snd_buffer[128] = {0};
	while(1)
	{
		//(3)recvfrom
		if(recvfrom(sockfd, &rcv_buffer, sizeof(rcv_buffer), 0, (struct sockaddr *)&addr_clie, &addrClientLen) < 0)
		{
			continue;
		}

		printf("recv message: %s\n", rcv_buffer);
		printf("client's port %d, ipadd: %s\n", htons(addr_clie.sin_port), inet_ntoa(addr_clie.sin_addr));
		
		//(4)sendto
		char *p_msg = "Hi, I am UDP server!";
		sprintf(snd_buffer, "%s\n", p_msg);
		int n = sendto(sockfd, &snd_buffer, sizeof(snd_buffer), 0, (struct sockaddr *)&addr_clie, addrClientLen);
		if(n < 0)
			printf("send message to client failed\n");
		else
			printf("send message: %s\n", snd_buffer);
	}

	//(5)close
	close(sockfd);
	
	return 0;
}


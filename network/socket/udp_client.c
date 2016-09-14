#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 8100

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in addr_serv;

	//(1)create socket
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("create socket failed, %s\n", strerror(errno));
		return -1;
	}

	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_port = htons(SERVER_PORT);
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_serv.sin_family = AF_INET;

	struct sockaddr_in addr_clie;
	bzero(&addr_clie, sizeof(addr_clie));
	addr_clie.sin_port = htons(8055);
	addr_clie.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_clie.sin_family = AF_INET;

	#if 0
	if(bind(sockfd, (struct sockaddr *)&addr_clie, sizeof(addr_clie)) < 0)
	{
		printf("bind failed, %s\n", strerror(errno));
		return -1;
	}
	#endif
	
	//message
	char snd_buffer[128] = {0};
	char rcv_buffer[128] = {0};
	char *p_msg = "Hi, I am UDP client!";
	sprintf(snd_buffer, "%s\n", p_msg);
	
	//(2)sendto
	sendto(sockfd, &snd_buffer, strlen(snd_buffer), 0, (struct sockaddr *)&addr_serv, sizeof(addr_serv));
	
	//(3)recvfrom
	recvfrom(sockfd, &rcv_buffer, sizeof(rcv_buffer), 0, NULL, NULL);
	printf("recv message from UDP server: %s\n", rcv_buffer);
	
	//(4)close
	close(sockfd);
	
	return 0;
}


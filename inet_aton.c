#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //This is important
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	struct in_addr inaddr;

	if(inet_aton("192.168.0.121", &inaddr) == 0)
	{
		fprintf(stdout, "inet_aton error\n");
		return 0;
	}

	printf("%s\n", inet_ntoa(inaddr));

	return 0;
}

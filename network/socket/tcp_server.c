#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc,char *argv[])
{
	int socket_fd = socket(AF_INET, SOCK_STREAM);
	if(socket_fd < 0)
	{
		printf("create socket failed!!!, %s\n", strerror(errno));
		return -1;
	}

	int host;
	int port = 8200;
	bind(host, port);

	listen(fd);

	while(1)
	{
		accept();
	}
		
	return 0;
}


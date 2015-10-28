#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int
get_ip_address(char *prompt, int *ip)
{
	char buf[80];
	struct in_addr in;

	fflush(stdin);
	fprintf(stdout, "%s: ", prompt);
	if(fgets(buf, sizeof(buf), stdin) == NULL)
	{
		printf("Invalid input.\n");
		return -1;
	}

	if(!inet_aton(buf, &in))
	{
		return -1;
	}

	*ip = (int)(ntohl(in.s_addr));

	return 0;
}

int 
main(int argc, char *argv[])
{
	int ip;
	get_ip_address("Please input the ip address", &ip);

	printf("What you input is %d\n", ip);

	return 0;
}

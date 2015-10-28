#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IP_ADDRESS(x)  (((x)>>24)&0xff), (((x)>>16)&0xff), (((x)>>8)& 0xff), ((x)&0xff)

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s <ip_address>\n", argv[0]);
		return -1;
	}

	//unsigned int ip = inet_addr(argv[1]);
	//printf("IP: %u\n", ip);
	
	char buff[128] = "10.121.1.240";
	struct in_addr in;
	/*
	if(fgets(buff, sizeof(buff), stdin) == NULL)
	{
		printf("Inval input\n");
		return -1;
	}
	*/
	//strcpy(buff, argv[1]);
	if(!inet_aton(buff, &in))
	{
		printf("something is error\n");
		return -1;
	}
	unsigned int ip = (u_int32_t)(ntohl(in.s_addr));
	char ipv6_txt[128];
	struct in6_addr ipv6;
	ipv6.s6_addr32[0] = in.s_addr;
	ipv6.s6_addr32[1] = 0;
	ipv6.s6_addr32[2] = 0;
	ipv6.s6_addr32[3] = 0;
	struct in6_addr ip6;
	unsigned int ipv6addr[4] = {in.s_addr, 0x0, 0x0, 0x0};
	unsigned short int ip_v6[8] = {htons(0x2001), htons(0x0), htons(0x121), htons(0x1), htons(0xdd82), htons(0x8946), htons(0x903f), htons(0xc6f9)};
	//unsigned short int ip_v6[8] = {0x0120, 0x0, 0x1012, 0x0001, 0x82dd, 0x4689, 0x3f90, 0xf9c6};
	//memcpy(&ip6, ip_v6, 128);

	memcpy(&ip6, ipv6addr, 128);
	inet_ntop(AF_INET6,  &ip6, ipv6_txt, sizeof(ipv6_txt));

	//inet_ntop(AF_INET6,  &ipv6, ipv6_txt, sizeof(ipv6_txt));
	printf("ip address: %u.%u.%u.%u, %u\n", IP_ADDRESS(in.s_addr), ip);
	printf("ipv6: %s\n", ipv6_txt);


	return 0;
}

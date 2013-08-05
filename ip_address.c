#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if 1
#include <arpa/inet.h>
#include <netinet/in.h>
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define IP_ADDRESS(ip) (((ip)>>24)&0xff), (((ip)>>16)&0xff),(((ip)>>8)&0xff), ((ip)&0xff)

#if 0
typedef unsigned int u_int32_t;
typedef u_int32_t in_addr_t;
struct in_addr
{
	in_addr_t s_addr;
}

struct in6_addr {
	union {
			isc_uint8_t	_S6_u8[16];
			isc_uint16_t	_S6_u16[8];
			isc_uint32_t	_S6_u32[4];
	} _S6_un;
};
#define s6_addr		_S6_un._S6_u8
#define s6_addr8	_S6_un._S6_u8
#define s6_addr16	_S6_un._S6_u16
#define s6_addr32	_S6_un._S6_u32
#endif

void v4_in_v6_addr0( struct in6_addr *v6_addr, u_int32_t v4_addr )
{
    v6_addr->s6_addr32[0] = v4_addr;
	v6_addr->s6_addr32[1] = 0;
	v6_addr->s6_addr32[2] = 0;
	v6_addr->s6_addr32[3] = 0;
}

int get_interface_ip_address(char *ifname)
{
	struct ifreq ifr;
	memset(&ifr, 0, sizeof(ifr));
	struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;
	strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	
	int socketfd;
	if((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		fprintf(stderr, "create a socket failed, errno = %d\n", errno);
		perror("");
		return -1;
	}
	
	if(ioctl(socketfd, SIOCGIFADDR, &ifr) == -1)
	{
		fprintf(stderr, "ioctl call failed, errno = %d\n", errno);
		perror("");
		close(socketfd);
		return -1;
	}

	fprintf(stdout, "ipaddress: %u.%u.%u.%u\n", IP_ADDRESS(sin->sin_addr.s_addr));
	fprintf(stdout, "ipaddress: %s\n", inet_ntoa(sin->sin_addr));

	return 0;
}


int main(int argc, char *argv[])
{
#if 0
	printf("you input ip addrss: %s\n", argv[1]);
	struct in_addr ip;
	ip.s_addr = inet_addr(argv[1]);
	printf("ip_address(int): %d\n", ip.s_addr);

	printf("ip address: %u.%u.%u.%u\n", IP_ADDRESS(ip.s_addr));
	printf("ip_address: %s\n", inet_ntoa(ip));

	//char ipv6_txt[64]; 
	//inet_ntop(AF_INET6,  &ipv6_addr, ipv6_txt, sizeof(ipv6_txt));
	
	char ipv4_txt[32];
	unsigned int ipv4_addr;
	inet_pton(AF_INET, argv[1], &ipv4_addr);
	printf("ip address(inet_pton): %d\n", ipv4_addr);

	inet_ntop(AF_INET, &ipv4_addr, ipv4_txt, sizeof(ipv4_txt));
	printf("ip address(inet_ntop): %s\n", ipv4_txt);
#endif
	
	get_interface_ip_address("eth0");

	return 0;
}

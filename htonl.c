#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define IP_ADDRESS(x)  (((x)>>24)&0xff), (((x)>>16)&0xff), (((x)>>8)& 0xff), ((x)&0xff)
int main(int argc, char *argv[])
{
	//unsigned int addr = htonl(0x7f000001);
	//unsigned int addr = htonl(0xE0000000);
	unsigned int addr = htonl(0x01000000|5);
	printf("addr: %u.%u.%u.%u\n", IP_ADDRESS(addr));

	if(argc != 5)
		return 0;

	unsigned int abc;
	int a, b, c;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = atoi(argv[3]);
	int d = atoi(argv[4]);
	abc = (unsigned int)a << (3 * 8);
	abc |= (unsigned int)b << (2 * 8);
	abc |= (unsigned int)c << (1 * 8);
	abc |= (unsigned int)d << (0 * 8);
	printf("abc: %u\n", abc);

	return 0;
}


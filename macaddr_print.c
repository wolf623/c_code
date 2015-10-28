#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define print_mac_addr(mac_addr) printf("mac addr: %02x%02x.%02x%02x.%02x%02x\n", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5])

int main(void)
{
	unsigned char mac_addr[6] = {0};
	//memcpy(mac_addr, "0013f787786e", 12);
	mac_addr[0] = 0;
	mac_addr[1] = 19;
	mac_addr[2] = 247;
	mac_addr[3] = 135;
	mac_addr[4] = 120;
	mac_addr[5] = 110;

	print_mac_addr(mac_addr);

	return 0;
}

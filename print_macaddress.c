#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PRINT_MAC_ADDRESS(x) *(x), *((x)+1), *((x)+2), *((x)+3), *((x)+4), *((x)+5)

int
main(void)
{	
	printf("%-15s  %-15s  %-14s  %-9s  %-6s  %-7s  %-7s  %-6s  %s\n", "Multicast Group", "Source IP", "NextHop MAC", "Src Intf", "Module", "kb/sec", "Status", "Type", "Up Time");

	char *group = "234.209.0.1";
	char *ip = "198.24.25.55";
	int mac[6] = {32, 253, 241, 228, 63, 85};
	char *port = "gige 6/6";
	int module = 3;
	int sec = 3834;
	char *status = "Foward";
	char *type = "Video";
	char *uptime = "0 day, 00:01:02";

	//printf("%-15s  %-15s  %-15s  %-8s  %-6s  %-7s  %-7s  %-6s  %s\n",
	//		group, ip, mac, port, moudle, sec, status, type, uptime);

	//printf("%-15s  %-15s  %-14s", group, ip, mac);
	//printf("  %-9s", port);
	//printf("  %-6s  %-7s  %-7s  %-6s  %s\n", moudle, sec, status, type, uptime);
	
	printf("%-15s  %-15s  %02x%02x.%02x%02x.%02x%02x", group, ip, PRINT_MAC_ADDRESS(mac));
	
	if(0)
	{
		printf("  %-9s  --      --       %-7s  %-6s  %s\n", port, status, type, uptime);
	}
	else
	{
		printf("  %-9s  %-6d  %-7d  %-7s  %-6s  %s\n", port, module, sec, status, type, uptime);
    }
 
 	group = "234.209.0.2";
	ip = "198.24.25.168";
	
	port = "vlan 6/6";
	module = 6;
	sec = 2836;
	status = "Block";
	type = "Docsis";
	uptime = "1 day, 10:01:02";

	//printf("%-15s  %-15s  %-15s  %-8s  %-6s  %-7s  %-7s  %-6s  %s\n",
	//		group, ip, mac, port, moudle, sec, status, type, uptime);

	//printf("%-15s  %-15s  %-14s", group, ip, mac);
	//printf("  %-9s", port);
	//printf("  %-6s  %-7s  %-7s  %-6s  %s\n", moudle, sec, status, type, uptime);
	if(0)
	{
		printf("%-15s  %-15s  %02x%02x.%02x%02x.%02x%02x", group, ip, PRINT_MAC_ADDRESS(mac));
	}
	else
	{
		printf("                                                ");//48
	}
	
	if(1)
	{
		printf("  %-9s  --      --       %-7s  %-6s  %s\n", port, status, type, uptime);
	}
	else
	{
		printf("  %-9s  %-6d  %-7d  %-7s  %-6s  %s\n", port, module, sec, status, type, uptime);
    }
    
    group = "234.209.0.6";
	ip = "198.24.25.55";
	
	port = "xgige 7/6";
	module = 3;
	sec = 26;
	status = "Foward";
	type = "Video";
	uptime = "0 day, 05:08:02";

	//printf("%-15s  %-15s  %-15s  %-8s  %-6s  %-7s  %-7s  %-6s  %s\n",
	//		group, ip, mac, port, moudle, sec, status, type, uptime);

	//printf("%-15s  %-15s  %-14s", group, ip, mac);
	//printf("  %-9s", port);
	//printf("  %-6s  %-7s  %-7s  %-6s  %s\n", moudle, sec, status, type, uptime);
	
	printf("%-15s  %-15s  %02x%02x.%02x%02x.%02x%02x", group, ip, PRINT_MAC_ADDRESS(mac));
	if(0)
	{
		printf("  %-9s  --      --       %-7s  %-6s  %s\n", port, status, type, uptime);
	}
	else
	{
		printf("  %-9s  %-6d  %-7d  %-7s  %-6s  %s\n", port, module, sec, status, type, uptime);
    }
    

	exit(0);
}

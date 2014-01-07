#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char cmd[128];
	int fcount = 0;
	sprintf(cmd, "sync;sync;echo 1 > /proc/sys/vm/drop_caches");
	
	while(1)
	{
		/* flush page cache, every 4M (i.e., 128*32K) */
		fcount++;
		if((fcount % 128) == 0)
		{
			printf("I am going to clear the page cache...\n");
			system(cmd);
			break;
		}
	}


	return 0;
}


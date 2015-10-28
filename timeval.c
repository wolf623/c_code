#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void my_print_time()
{
	struct timeval tv;
	if(gettimeofday(&tv, NULL) != 0)
	{
		printf("gettimeofday failed\n");
		return;
	}
	
	struct tm atm;
	if(localtime_r(&tv.tv_sec, &atm) == NULL)
	{
		printf("localtime_r failed\n");
		static char tv_buf[32] = {0};
		if(ctime_r(&tv.tv_sec, tv_buf) != NULL)
		{
			tv_buf[strlen(tv_buf)] = '\0';
			printf("Time: %s\n", tv_buf);
			return;
		}
		else
		{
			printf("sec: %lu, usec: %lu\n", tv.tv_sec, tv.tv_usec);
			return;
		}
	}
		
	printf("%u min %u sec %lu msec, %lu usec\n", atm.tm_min, atm.tm_sec, tv.tv_usec/1000, tv.tv_usec);

}

int main(void)
{
	my_print_time();
	return 0;
}



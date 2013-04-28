#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

char *getSysTime_r(char *timestamp)
{
	if (!timestamp)
	{
		return NULL;
	}
						
	struct tm *datetime;	

	struct timeval  tv;
									
	if(gettimeofday(&tv, NULL) != 0)
	{
		return NULL;
	}
															
	if ((datetime = localtime(&tv.tv_sec)) == NULL)
	{
		return NULL;
	}
																					
	//strftime has some problem with 2.6 kernel
	//strftime(timestamp, sizeof(timestamp), "%Y-%m-%d,%H:%M:%S", datetime);
	sprintf(timestamp, "%04d-%02d-%02d,%02d:%02d:%02d.%01ld", 
						datetime->tm_year + 1900, datetime->tm_mon + 1, datetime->tm_mday, 
						datetime->tm_hour,  datetime->tm_min,  datetime->tm_sec, tv.tv_usec/100000);
	
	return timestamp;
}

char *getSysTime()
{
	static char buff[32] = {0};
	return getSysTime_r(buff);
}

int 
main(int argc, char *argv[])
{
	char *ptr = getSysTime();

	printf("%s\n", ptr);

	return 0;
}

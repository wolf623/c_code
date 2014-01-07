#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *timeval_to_tm(struct timeval *tv, char *timestamp)
{
	if(!timestamp)
	{
		return NULL;
	}

	struct tm *datetime;

	if( (datetime = localtime(&tv->tv_sec)) == NULL)
	{
		fprintf(stderr, "localtime() failed.\n");
		return NULL;
	}

	sprintf(timestamp, "%04d-%02d-%0d,%02d:%02d:%02d.%04ld",
		datetime->tm_year + 1900, datetime->tm_mon + 1, datetime->tm_mday,
		datetime->tm_hour, datetime->tm_min, datetime->tm_sec, tv->tv_usec/100);
	
	return timestamp;
}

int main(void)
{
	struct timeval tv = {0};
	gettimeofday(&tv, NULL);
	static char buff[64] = {0};
	static char new_buff[64] = {0};
	struct timeval new_tv = {0};
	memcpy(&new_tv, &tv, sizeof(struct timeval));

	if(timeval_to_tm(&tv, buff) != NULL)
	{
		printf("timeval_to_tm() success.\n");
		printf("%s\n", buff);
	}
	
	if(timeval_to_tm(&new_tv, new_buff) != NULL)
	{
		printf("new timeval_to_tm() success.\n");
		printf("new: %s\n", new_buff);
	}

	exit(0);
}

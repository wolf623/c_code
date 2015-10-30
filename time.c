/* 
 * About time function 
 * #include <time.h>
 * char *asctime(const struct tm *tm);
 * char *asctime_r(const struct tm *tm, char *buf);
 * char *ctime(const time_t *timep);
 * char *ctime_r(const time_t *timep, char *buf);
 * struct tm *gmtime(const time_t *timep);
 * struct tm *gmtime_r(const time_t *timep, struct tm *result);
 * struct tm *localtime(const time_t *timep);
 * struct tm *localtime_r(const time_t *timep, struct tm *result);
 * time_t mktime(struct tm *tm);
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

	if(timeval_to_tm(&tv, buff) != NULL)
	{
		printf("%s\n", buff);
	}

	time_t t = time(NULL);
	printf("time(): %d\n", (int)t);
	
	printf("ctime(): %s", ctime(&t));
	
	struct tm *datetime = gmtime(&t);
	printf("gmtime(): %04d-%02d-%0d,%02d:%02d:%02d\n",
		datetime->tm_year + 1900, datetime->tm_mon + 1, datetime->tm_mday,
		datetime->tm_hour, datetime->tm_min, datetime->tm_sec);
		
	datetime = localtime(&t);
	printf("localtime(): %04d-%02d-%0d,%02d:%02d:%02d\n",
		datetime->tm_year + 1900, datetime->tm_mon + 1, datetime->tm_mday,
		datetime->tm_hour, datetime->tm_min, datetime->tm_sec);
	
	time_t new_t = mktime(datetime);
	printf("mktime(): %d\n", (int)new_t);
	
	printf("asctime(): %s", asctime(datetime));
	
	exit(0);
}

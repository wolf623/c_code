#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>

int main(int argc, char *argv[])
{
	char buf[128];
	int i = 0;
	char str[4];
	time_t mytime = {0};
	struct tm *mytm;
	
	static struct timeval tv = {0};
	static char tv_buf[32] = {0};
	static char *time_buf;

	printf("Back:%ld\n", time(&mytime));

	if(time(&mytime) == -1)
	{
		printf("time error\n");
		exit(1);
	}

	if(ctime_r(&mytime, tv_buf) != NULL)
	{
		tv_buf[strlen(tv_buf) -1] = '\0';
	}
	else
	{
		printf("ctime_r error.\n");
		exit(1);
	}
	
	time_buf = ctime(&mytime);
	time_buf[strlen(time_buf) - 1] = '\0';

	printf("Time: %s\n", time_buf);
	printf("The time is: %s\n", tv_buf);
	
	printf("Pleae input 'yes': ");
	fgets(buf, sizeof(buf), stdin);
	
	if(strlen(buf) != 4)
	{
		printf("input error.\n");
		exit(1);
	}
	printf("strlen(buf) = %d\n", strlen(buf));

	for(i=0; i<strlen(buf); i++)
	{
		str[i] = toupper(buf[i]);
	}
	
	str[4] = 0;
	
	if(strncmp("YES", str, 3))
	{
		printf("not the character 'YES'\n");
		exit(1);
	}

	printf("You make it.\n");

	if(time(&mytime) == -1)
	{
		printf("time() error.\n");
		exit(1);
	}
	
	mytm = localtime(&mytime);

	printf("Now time is: %s\n", ctime(&mytime));
	printf("time is: %s\n", asctime(mytm));
	printf("localtime: %02d/%02d/%04d,%02d:%02d:%02d\n", 
				mytm->tm_mday, mytm->tm_mon + 1, mytm->tm_year + 1900,
				mytm->tm_hour,  mytm->tm_min,  mytm->tm_sec);

	
	//include the UTC timezero
	struct tm *datetime;
	datetime= gmtime(&mytime);
	printf("gmtime: %02d/%02d/%04d,%02d:%02d:%02d\n", 
				datetime->tm_mday, datetime->tm_mon + 1, datetime->tm_year + 1900,
				datetime->tm_hour,  datetime->tm_min,  datetime->tm_sec);

	exit(0);

}

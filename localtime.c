#include <stdio.h>
#include <time.h>

int print_date_time(void)
{
	time_t mytime;
	if(time(&mytime) == -1)
	{
		printf("time failed\n");
		return -1;
	}

	struct tm *mytm = NULL;
	if((mytm = localtime(&mytime)) == NULL)
	{
		printf("localtime failed\n");
		return -1;
	}

	printf("Now time is: %s\n", ctime(&mytime));
	printf("time is: %s\n", asctime(mytm));
	printf("localtime: %02d/%02d/%04d,%02d:%02d:%02d\n", 
				mytm->tm_mday, mytm->tm_mon + 1, mytm->tm_year + 1900,
				mytm->tm_hour,  mytm->tm_min,  mytm->tm_sec);

	return 0;
}

int main(void)
{
	print_date_time();

	return 0;
}




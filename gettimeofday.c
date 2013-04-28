#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(void)
{
	struct timeval tv_start = {0};
	struct timeval tv_end = {0};
	long lasttime = 0;

	gettimeofday(&tv_start, NULL);

	printf("The current time: %s\n", ctime(&tv_start.tv_sec));

	sleep(10);

	gettimeofday(&tv_end, NULL);

	printf("The current time: %s\n", ctime(&tv_end.tv_sec));

	lasttime = (tv_end.tv_sec + tv_end.tv_usec/100000) - (tv_start.tv_sec + tv_start.tv_usec/100000);

	printf("The Last time: %ld\n", lasttime);

	exit(0);
}

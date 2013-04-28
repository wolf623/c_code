/* 
 * nanosleep() funtion is similar to the sleep() function
 * but it can use the ns,instead of us.
 * Time: 2013-3-27
*/

/*
 * Knowledge Point:
 * define our data structer to change from the structer timeval
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

//The structer timespec was alread defined in the /usr/inlcude/time.h
#if 0
struct timespec{
	time_t tv_sec;	//second
	long tv_nsec;	// 1s = 1000ms = 1000 000us = 1000 000 000ns
};
#endif

#define TIMESPEC_TO_TIMEVAL(tv, ts) { 		\
	(tv)->tv_sec = (ts)->tv_sec; 			\
	(tv)->tv_usec = (ts)->tv_nsec / 1000;	\
}

#define TIMEVAL_TO_TIMESPEC(ts, tv) {		\
	(ts)->tv_sec = (tv)->tv_sec;			\
	(ts)->tv_nsec = (tv)->tv_usec * 1000;	\
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
	int rc;
	struct timeval tstart, tstop, tremain, timewait;
	
	TIMESPEC_TO_TIMEVAL(&timewait, req);
	(void)gettimeofday(&tstart, NULL);
	rc = select(0, NULL, NULL, NULL, &timewait);
	if(rc == -1)
	{
		(void)gettimeofday(&tstop, NULL);
		tremain.tv_sec = timewait.tv_sec - (tstop.tv_sec - tstart.tv_sec);
		tremain.tv_usec = timewait.tv_usec - (tstop.tv_usec - tstart.tv_usec);
		tremain.tv_sec += tremain.tv_usec / 1000000L;
		tremain.tv_usec %= 1000000L;
	}
	else
	{
		tremain.tv_sec = 0;
		tremain.tv_usec = 0;
	}

	if(rem != NULL)
	{
		TIMEVAL_TO_TIMESPEC(rem, &tremain);
	}

	return rc;
}

int main(int argc, char *argv[])
{
	const struct timespec pause1s = { 0, 1000000000};

	(void)nanosleep(&pause1s, NULL);

	return 0;
}

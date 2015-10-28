/*
 * =====================================================================================
 *
 *       Filename:  mytime.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/09/14 15:26:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

char * getSysTime_tv(struct timeval  *tv, char *timestamp)
{
	if (!timestamp)
	{
		return NULL;
	}
	
	struct tm *datetime;	
	
	if ((datetime = localtime(&tv->tv_sec)) == NULL)
	{
		return NULL;
	}
	
	//strftime has some problem with 2.6 kernel
	//strftime(timestamp, sizeof(timestamp), "%Y-%m-%d,%H:%M:%S", datetime);
	sprintf(timestamp, "%04d-%02d-%02d,%02d:%02d:%02d.%04ld", 
		datetime->tm_year + 1900, datetime->tm_mon + 1, datetime->tm_mday, 
		datetime->tm_hour,  datetime->tm_min,  datetime->tm_sec, tv->tv_usec/100);

	return timestamp;
}

char * getSysTime_r(char *timestamp)
{
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	getSysTime_tv(&tv, timestamp);
}

char * getSysTimeV(struct timeval  *tv) 
{
	static char buff[64] = {0};
	return getSysTime_tv(tv, buff);	
}

char * getSysTime() 
{
	static char buff[32] = {0};
	return getSysTime_r(buff);	
}


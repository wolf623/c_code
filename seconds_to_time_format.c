/****************************************************
 * Description	: Change the seconds to time format
 * Author		: wolf
 * Time			: 2013-3-12
****************************************************/

/*****************************************************
 * Knowledge Point	: 
 * The logic is how change the seconds to time format
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define u_int32_t unsigned int
#define u_int8_t unsigned char
//typedef unsigned long int u_int32_t;
//typedef unsigned char u_int8_t;
//
void seconds_to_time_format(u_int32_t seconds, u_int8_t *tmp)
{
	u_int32_t day, hour, min, sec;

	if(!tmp)
	{
		return ;
	}

	day = seconds / (3600 * 24);
	sec = seconds - day*3600*24;
	hour = sec / 3600;
	sec = sec - hour*3600;
	min = sec / 60;
	sec = sec - min*60;

	sprintf((char *)tmp, "%d day, %02d:%02d:%02d", day, hour, min, sec);

	return ;
}

int main(int argc, char *argv[])
{
	u_int8_t buff[128];
	int seconds = 2382000;
	seconds_to_time_format(seconds, buff);

	printf("%s\n", buff);

	return 0;
}

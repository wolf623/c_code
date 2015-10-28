/* 
 * This file is used for crating a random number 
 * 2013-11-4
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define linux 	1

int rfd = 0;	/* /dev/urandom */
void magic_init()
{
	long seed;
	struct timeval tv;

#ifdef linux
	rfd = open("/dev/urandom", O_RDONLY);
	if(rfd != -1) //normal
	{
		return;
	}
	else
	{
		rfd = 0; //set the flag
#endif
	/* if /dev/urandom fails, we try the traditional method */
	gettimeofday(&tv, NULL);
	seed = gethostid() ^ tv.tv_sec ^ tv.tv_usec ^ getpid();
	srandom((int)seed);
#ifdef linux
	}
#endif
}

unsigned int create_random_num()
{
#ifdef linux
	unsigned int ret = 0;
	if(rfd) //if we read /dev/urandom sucess, then it is not 0
	{
		read(rfd, &ret, sizeof(int));
		return(ret);
	}
	else
	{
		//maybe we can do it as in the magic_init()
		return (unsigned int)random();
	}
#else
	return (unsigned int)readom();
#endif
}

int main(void)
{
	magic_init();	//initial
	unsigned int rc = create_random_num();
	printf("The magic number: %u\n", rc);

	return 0;
}

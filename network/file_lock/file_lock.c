#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

#define FILENAME "./temp.txt"

//lock file (open in read mode)until timeOutSec seconds.
//if timeOutSec is -1, will lock forever.
static bool lockFileReadBlock(FILE *fp, time_t timeOutSec)
{
	struct flock fl;
	memset(&fl, 0, sizeof(fl));
	fl.l_type = F_RDLCK; //read lock
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_pid = getpid();
	time_t start  = time(NULL);
	int fd = fileno(fp);

	while(fcntl(fd, F_SETLKW, &fl) == -1)
	{
		if(timeOutSec != -1 && time(NULL)-start>=timeOutSec)
		{
			close(fd);
			return FALSE;
		}
		usleep(1);
	}
	return TRUE;
}

//lock file(open in write mode) until timeOutSec seconds.
//if timeOutSec is -1, will lock forever.
static bool lockFileWriteBlock(FILE *fp, time_t timeOutSec)
{
	struct flock fl;
	memset(&fl, 0, sizeof(fl));
	fl.l_type = F_WRLCK; //read lock
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_pid = getpid();
	time_t start  = time(NULL);
	int fd = fileno(fp);

	while(fcntl(fd, F_SETLKW, &fl) == -1)
	{
		if(timeOutSec != -1 && time(NULL)-start>=timeOutSec)
		{
			close(fd);
			return FALSE;
		}
		usleep(1);
	}
	return TRUE;
}

//unlock file
static void unlockAndCloseFile(FILE *fp)
{
	struct flock fl;
	memset(&fl, 0, sizeof(fl));
	fl.l_type = F_UNLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_pid = getpid();
	int fd = fileno(fp);
	
	fcntl(fd, F_SETLKW, &fl);
	close(fd);
}

int main(int argc, char *argv[])
{
	FILE *fp;
	int fd;

	fd = open(FILENAME, O_RDWR);
	int fd2 = open(FILENAME, O_RDWR);
	flock(fd, LOCK_SH);
	close(fd);
	flock(fd2, LOCK_EX);
	//flock(fd, LOCK_UN);
	//flock(fd2, LOCK_EX);
	
	#if 0
	if((fp = fopen(FILENAME, "w")) != NULL)
	{
		fd = fileno(fp);
		flock(fd, LOCK_EX); //lock file
		fprintf(fp, "Hello, I am wolf\n");
		system("sync");
		sleep(10);
		printf("after sleep, before unlock file...\n");
		fflush(stdout);
		flock(fd, LOCK_UN); //unlock file
		fclose(fp);
		printf("write done...\n");
		fflush(stdout);
	}
	#endif
	
	return 0;
}


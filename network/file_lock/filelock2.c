#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <errno.h>

#define FILENAME "./temp.txt"

int main(int argc, char *argv[])
{
	FILE *fp;
	int fd;
	char buff[256];
	int rc;

	if((fp = fopen(FILENAME, "r")) != NULL)
	{
		fd = fileno(fp);
		//rc = flock(fd, LOCK_EX|LOCK_NB); //lock file
		rc = flock(fd, LOCK_SH);
		if(rc == -1)
		{
			if(errno == EWOULDBLOCK)
				printf("Read Process2: return back\n");
		}
		if(fgets(buff, sizeof(buff), fp) != NULL)
		{
			printf("Read Process2: %s\n", buff);
			fflush(stdout);
		}
		//sleep(3);
		flock(fd, LOCK_UN); //unlock file
		fclose(fp);
		printf("Process2 read done...\n");
		fflush(stdout);
	}
	
	return 0;
}


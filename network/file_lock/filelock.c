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

	//sleep(5);
	if((fp = fopen(FILENAME, "r")) != NULL)
	{
		fd = fileno(fp);
		rc = flock(fd, LOCK_SH);//|LOCK_NB); //lock file
		if(rc == -1)
		{
			if(errno == EWOULDBLOCK)
				printf("Read Process1: return back\n");
		}
		
		if(fgets(buff, sizeof(buff), fp) != NULL)
		{
			printf("Read Process1: %s\n", buff);
			fflush(stdout);
		}
		//sleep(5);
		flock(fd, LOCK_UN); //unlock file
		printf("Process1 read done...\n");
		fflush(stdout);
		fclose(fp);
	}
	
	return 0;
}


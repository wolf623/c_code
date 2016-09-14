#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFONAMNE "./tmpfifoname"

int main(int argc, char *argv[])
{
	if(mkfifo(FIFONAMNE, 0666) < 0 && (errno != EEXIST))
	{
		printf("mkfifo failed!\n");
		return -1;
	}

	pid_t pid;
	int fd;
	char buff[10] = {0};
	
	if((pid = fork()) < 0)
	{
		printf("fork failed!\n");
		return -1;
	}
	else if(pid == 0)
	{
		#if 1
		//child
		if((fd = open(FIFONAMNE, O_WRONLY|O_NONBLOCK)) == -1)
		{
			printf("open fifoname for write failed!\n");
			return -1;
		}
		sprintf(buff, "%s", "abc");
		write(fd, buff, strlen(buff));
		printf("write: %s\n", buff);
		#endif
	}
	else
	{
		#if 0
		//parent
		if((fd = open(FIFONAMNE, O_RDONLY)) == -1)
		{
			printf("open fifoname for read failed!\n");
			return -1;
		}
		read(fd, buff, sizeof(buff)-1);
		printf("read: %s\n", buff);
		waitpid(pid, NULL, 0);
		#endif
	}

	printf("I am here...\n");
	waitpid(pid, NULL, 0);
	printf("I will exit...\n");
	close(fd);
	return 0;
}


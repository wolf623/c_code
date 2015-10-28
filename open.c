#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXSIZE 100

int main(char argc, char **argv)
{
    int fd, curpos, newpos, endpos;;
	char buf[MAXSIZE] = {"This is test!\n"};

	/* write text to the file */
#if 1
	if ( (fd = open("./txt", O_RDWR | O_CREAT | O_APPEND, 0666)) < 0)
	{
		perror("open error!\n");
	}
#endif
	
	//FILE *fp = fopen("./txt", "aw");

	printf(" !!! %d\n", fd);

	if (write(fd, buf, strlen(buf)) != strlen(buf))
		perror("write error!\n");

	close(fd);
}


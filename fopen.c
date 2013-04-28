#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int 
main(void)
{
	FILE *fd = fopen("/home/lm/test/tmp.file", "awb+");
	int status = 1;
	if(fd == NULL)
		fprintf(stderr, "open /tmp/tmp.file failed\n");
	else	
		fprintf(fd, "The status is %d\n", status);

	exit(0);
}

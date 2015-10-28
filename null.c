#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int
main(void)
{
	int fd = open("/dev/null", O_RDWR);

	printf("fd = %d\n", fd);

	char *ptr = "";
	int len = strlen(ptr);

	printf("len = %d\n", len);

	exit(0);
}

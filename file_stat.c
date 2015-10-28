/*
 * This file include all the stat about file
 * Tue May 27 16:33:41 CST 2014
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

size_t get_file_size(char *filename)
{
	if(filename == NULL)
		return -1;

	static fd = -1;
	if(fd = -1)
	{
		fd = open(filename, O_RDONLY);
		if(fd == -1)
		{
			printf("open %s failed, %s\n", filename, strerror(errno));
			return -2;
		}
	}

	size_t file_size = 0;
	struct stat sbuf;
	sbuf.st_size = 0;
	if(fstat(fd, &sbuf) == 0)
	{
		file_size = sbuf.st_size;
		printf("size: %d\n", (int)sbuf.st_size);
	}

	return file_size;
}
	

int main(int argc, char *argv[])
{
	printf("file size: %d\n", (int)get_file_size(argv[1]));
	return 0;
}

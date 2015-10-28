#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void reopen_stdout(void)
{
#if 0
	int fd;
	fd = open("/dev/null", O_RDWR);
	if (fd == 0)
		fd = open("/dev/null", O_RDWR);
	if (fd == 1)
		fd = open("/dev/null", O_RDWR);
	if (fd != -1)
		close(fd);
#endif
	
	int fd;
	fd = open("/dev/console", O_RDWR);
	fprintf(stdout, "fd: %d\n", fd);
}

void close_stdout(void)
{
	int i;

	for(i=0; i<3; i++)
	{	
		close(i);
	}
}

int main(int argc, char *argv[])
{
	fprintf(stdout, "stdout is normal...\n");

	fprintf(stdout, "will close stdout...\n");
	close_stdout();
	fprintf(stdout, "already close stdout...\n");

	fprintf(stdout, "will reopen stdout...\n");
	//reopen_stdout();
	freopen("/dev/tty", "w", stdout);
	fprintf(stdout, "reopen stdout successfully...\n");

	return 0;
}



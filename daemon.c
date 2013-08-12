#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>

static int set_fd_nb(int fd)
{
	int val;
	val = fcntl(fd, F_GETFL);
	if (val < 0)
	{
		fprintf(stderr, "%s(): fcntl(F_GETFL) for fd %d failed, %m\n", __FUNCTION__, fd);
		return -1;
	}
	else
	{
		if (fcntl(fd, F_SETFL, val | O_NONBLOCK) < 0)
		{
			fprintf(stderr, "%s(): fcntl(F_SETFL, O_NONBLOCK) for fd %d failed, val %d, %m\n", __FUNCTION__, fd, val);
			return -2;
		}
	}

	return 0;
}

#define TEXT_MAX	256
void myprintlog(const char *logfilename, const char *text, ...)
{
	if(logfilename == NULL)
	{
		fprintf(stdout, "The logfilename is null pointer\n");
		return;
	}

	va_list ap;
	va_start(ap, text);
	char buff[TEXT_MAX] = {0};
	vsnprintf(buff, TEXT_MAX, text, ap);
	va_end(ap);

	FILE *fp = fopen(logfilename, "a+w");
	if(fp == NULL)
	{
		fprintf(stdout, "fopen %s failed\n", logfilename);
		return;
	}

	fprintf(fp, "%s", buff);
	fclose(fp);
}

void _sm_daemonize(void)
{
	//close old stdin/stdout/stderr
	int i;
	for(i=0; i<3; i++)
	{
		close(i);
	}

	pid_t pid = fork();
	if(pid < 0)
	{
		return;
	}
	else if(pid != 0)
	{
		//parent process
		exit(0);
	}
	

	//child process
	setsid();

	umask(0);

	chdir("/");

	//reopen stdin/stdout/stderr
	int fds[3];
	fds[0] = open("/dev/null", O_RDWR, 0755);
	fds[1] = open("/dev/tty", O_RDWR, 0755);
	if(fds[1] != -1)
	{
		set_fd_nb(fds[1]);
	}

	fds[2] = open("/dev/console", O_RDWR, 0755);
	if(fds[2] != -1)
	{
		set_fd_nb(fds[2]);
	}

	if(fds[1] == 1)
	{
		fprintf(stdout, "reopen stdin, stdout, stderr successfully, %d, %d, %d\n", fds[0], fds[1], fds[2]);

	}
	
	myprintlog("/home/c_learing/stdout.tmp", "reopen stdin, stdout, stderr successfully, %d, %d, %d\n", fds[0], fds[1], fds[2]);
}

int main(int argc, char *argv[])
{
	fprintf(stdout, "start ...\n");
	_sm_daemonize();
	if(freopen("/home/c_learing/reopen.tmp", "a+w", stdout) != NULL)
	{
		myprintlog("/home/c_learing/stdout.tmp", "---------------------------\n");
	}
	else
	{
		myprintlog("/home/c_learing/stdout.tmp", "***************************\n");
	}

	fprintf(stdout, "set it as a daemon ...\n");
	printf("^^^^^^^^^^^^^^^^\n");
	fclose(stdout);
	myprintlog("/home/c_learing/stdout.tmp", "set it as a daemon\n");
	freopen("/dev/tty", "w", stdout);
	printf("end ...\n");


	while(1)
	{
		sleep(100);
	}

	return 0;
}


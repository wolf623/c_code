#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>

#include "is_proc_running.h"

static void write_pid(const char *pname)
{
	FILE *fp = fopen(pname, "w");
	if(fp != NULL)
	{
		fprintf(fp, "%d", getpid());
		fclose(fp);
	}
}

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

void _sm_daemonize(void)
{
#if 0
	//close old stdin/stdout/stderr
	int i;
	for(i=0; i<3; i++)
	{
		close(i);
	}
#endif

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

#if 0
	//reopen stdin/stdout/stderr
	int fds[3];
	fds[0] = open("/dev/null", O_RDWR, 0755);
	fds[1] = open("/dev/console", O_RDWR, 0755);
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
#endif
}

int is_process_running(pid_t *p_pid)
{
	if (access(PROC_PID_FILE, F_OK) == 0)
	{
		FILE *fp = fopen(PROC_PID_FILE, "r");
		if (fp)
		{
			char procfile[256];
			fscanf(fp, "%d", p_pid);
			fclose(fp);
			sprintf(procfile, "/proc/%d/status", *p_pid);

			if (access(procfile, F_OK) == 0)
			{
				return 1;
			}
		}
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int set_fd_nb(int fd)
{
	int val;
	val = fcntl(fd, F_GETFL);
	if(val < 0)
	{
		fprintf(stderr,"%s(): fcntl(F_GETFL) for %d failed, %m\n", __FUNCTION__, fd);
		return -1;
	}
	else
	{
		if(fcntl(fd, F_SETFL, val | O_NONBLOCK) < 0)
		{
			fprintf(stderr, "%s(): fcntl(F_SETFL, O_NONBLOCK) for %d failed, val: %d, %m\n", __FUNCTION__, fd, val);
			return -1;
		}
	}

	return 0;
}
			
static void _sm_daemonize()
{
	int i;
	int sm_fds[3];

	//close old stdin/stdout/stderr
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

	//reopen stdin
	sm_fds[0] = open("/dev/null", O_RDWR, 0755);
	sm_fds[1] = open("/dev/tty", O_RDWR, 0755);
	if(sm_fds[1] != -1)
	{
		set_fd_nb(sm_fds[1]);
	}

	sm_fds[2] = open("/dev/tty", O_RDWR, 0755);
	if(sm_fds[2] != -1)
	{	
		set_fd_nb(sm_fds[2]);
	}

	if(sm_fds[1] == 1)
	{
		fprintf(stdout, "%s(): reopen stdin, stdout, stderr successfully, %d, %d, %d\n", sm_fds[0], sm_fds[1], sm_fds[2]);
	}
}

static void monitor_abc()
{
	pid_t pid;
	_sm_init();

	if(!_is_proc_running(&pid))
	{
		system(./abc);
	}
}

void monitor_softwares()
{
	monitor_abc();
}

int main(void)
{
	_sm_daemonize();

	while(1)
	{
		monitor_softwares();
		sleep(1);
	}

	return 0;
}


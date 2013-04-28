#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int g_fds[3];
int set_fd_nonblock(int fd)
{
	int val;
	val = fcntl(fd, F_GETFL);

	if(val < 0)
	{
		fprintf(stderr, "%s(): fcntl(F_GETFL) for fd %d failed, %m\n", __FUNCTION__, fd);
		return -1;
	}
	else
	{
		if(fcntl(fd, F_SETFL, val | O_NONBLOCK) < 0)
		{
			fprintf(stderr, "%s(): fcntl(F_SETFL, O_NONBLOCK) for fd %d failed, %m\n", __FUNCTION__, fd);
			return -2;
		}
	}

	return 0;
}


static void daemonize(int nochdir, int noclose)
{
	int i = 0;
	pid_t pid = fork();
	
	if(pid < 0)
	{
		return ;
	}
	else if(pid > 0)
	{
		//parent process termination
		exit(0);
	}

	if(!noclose)
	{
		for(i = 0; i < 3; i++)
			close(i);
	}

	//child process
	/*
	 *setsid()  creates a new session if the calling process is not a process group leader.  
	 * The calling process is the leader of the new session, the process group leader of
	 * the new process group, and has no controlling tty.  The process	group ID and session
	 * ID of the calling process  are	set	to the PID of the calling process.  The calling 
	 *process will be the only process in this new process group and in this new session.
	 */

	setsid();

	umask(0);

	if(!nochdir)
	{
		chdir("/");
	}

	if(!noclose)
	{
		g_fds[0] = open("/dev/null", O_RDWR, 0755);
		g_fds[1] = open("/dev/console", O_RDWR, 0755);
		if(g_fds[1] != -1)
		{
			set_fd_nonblock(g_fds[1]);
		}
		g_fds[2] = open("/dev/console", O_RDWR, 0755);
		if(g_fds[2] != -1)
		{
			set_fd_nonblock(g_fds[2]);
		}

		if(g_fds[1] == 1 && g_fds[2] == 1)
		{
			fprintf(stdout, "%s(): reopen stdin, stdout, stderr successfully, %d, %d, %d\n", 
					__FUNCTION__, g_fds[0], g_fds[1], g_fds[2]);
		}
	}
}

int main(int argc, char *argv[])
{
	daemonize(0, 0);

	return 0;
}


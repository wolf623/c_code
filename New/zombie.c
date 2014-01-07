#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

sig_atomic_t child_exit_status;

void clean_up_child_process(int signal_num)
{
	//clean up child process
	int status;
	wait(&status);

	//store its exit status in a global variable
	child_exit_status = status;
}

int main(void)
{
	struct sigaction sigchild_action;
	memset(&sigchild_action, 0, sizeof(sigchild_action));
	sigchild_action.sa_handler = &clean_up_child_process;
	sigaction(SIGCHLD, &sigchild_action, NULL);

	//fork a child, and let it dies before parent
	pid_t pid = fork();

	if(pid > 0) //parent process
	{
		printf("in parent process, sleep for one miniute ...zZ...\n");
		sleep(100);
		//printf("after sleeping, and exit\n");
		//sleep(60);
	}
	else if(pid == 0)
	{
		//clild process exit, and to be a zombie process
		printf("in child process, and exit\n");
		exit(0);
	}
	else
	{
		printf("fork failed\n");
	}

	return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FD_NUM 	65525

void mydaemon(void)
{
	pid_t pid = fork();
	
	if(pid < 0)
	{	
		printf("fork error\n");
		exit(-1);
	}
	else if(pid > 0) //parent 
	{
		exit(0);
	}
	else //child
	{
		setsid();
		
		chdir("/");

		umask(0);

		int i=0; 
		for(i=0; i<MAX_FD_NUM; i++)
			close(i);
	}

	//write here to what you want daemon to do
	
	for(;;)
	{
		sleep(1);
	}
}

int main(void)
{
	mydaemon();

	return 0;
}

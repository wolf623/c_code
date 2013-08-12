#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
 * We can use the access() function to check if the file is exist or not 
*/
#if 0
#define ABC_FILE "abc.c"

int main(int argc, char *argv[])
{
	if(access(ABC_FILE, F_OK) == 0)
		printf("%s file exist\n", ABC_FILE);
	else
		printf("%s file is not exist\n", ABC_FILE);

	return 0;
}
#endif


#include "is_proc_running.h"

static void write_pid(const char *proc_name)
{
	FILE *fp = fopen(proc_name, "w");
	if(fp != NULL)
	{
		fprintf(fp, "%d", getpid());
		fclose(fp);
	}
}


int main(int argc, char *argv[])
{
	//_sm_daemonize();
	
	//printf("starting ...\n");
	write_pid(PROC_PID_FILE);

	pid_t pid;
	if(is_process_running(&pid))
	{
		printf("The process is running, pid: %d\n", pid);
		sleep(60);
		return 0;
	}
	else
	{
		printf("The process is not running\n");
	}
	

	sleep(60);
	printf("end ...\n");
	return 0;
}


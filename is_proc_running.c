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

//we write the pid of the process to the file
//so we can get the pid from the process
//#define PROC_PID_FILE 	"/var/run/proc.pid"
#define PROC_PID_FILE 	"proc.pid"

static int _is_process_running(pid_t *pid)
{
	if(access(PROC_PID_FILE, F_OK) == 0)
	{
		FILE *fp = fopen(PROC_PID_FILE, "r");
		if(fp != NULL)
		{
			char procfile[256];
			fscanf(fp, "%d", pid);
			fclose(fp);
			sprintf(procfile, "/proc/%d/status", *pid);
			
			if(access(procfile, F_OK) == 0)
			{
				return 1;
			}
		}
	}

	return 0;
}

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
	printf("starting ...\n");
	write_pid(PROC_PID_FILE);

	pid_t pid;
	if(_is_process_running(&pid))
	{
		printf("The process is running, pid: %d\n", pid);
		return 0;
	}

	printf("The process is not running\n");

	printf("end ...\n");

	return 0;
}
	

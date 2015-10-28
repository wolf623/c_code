#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


void do_cd(char *argv[]);
void execute_new(char *argv[]);

int main(void)
{
	char *cmd = (char *)malloc(256);
	if(cmd == NULL)
		return -1;
	
	char *cmd_arg[10];
	int cmdlen, i, j, tag;

	do
	{
		for(i=0; i<255; i++)
			cmd[i] = '\0';
		for(i=0; i<10; i++)
			cmd_arg[i] = NULL;

		printf("==Mini Shell==> ");
		fgets(cmd, 255, stdin);

		cmdlen = strlen(cmd);
		cmd[cmdlen-1] = '\0'; //no need if we have initial
		
		i=j=tag = 0;
		while(i<cmdlen && j<10)
		{
			if(cmd[i] == ' ')
			{
				cmd[i] = '\0';
				tag = 0;
			}
			else
			{
				if(tag == 0)
				{
					cmd_arg[j++] = cmd+i;
				}
				tag = 1;
			}

			i++;
		}

		if(j>=10 && i<cmdlen)
		{
			printf("Too many argumentsn\n");
			continue;
		}

		if(strcmp(cmd_arg[0], "quit") == 0)
			break;

		if(strcmp(cmd_arg[0], "cd") == 0)
		{
			do_cd(cmd_arg);
			continue;
		}

		execute_new(cmd_arg);
	}while(1);

	return 0;
}

void do_cd(char *argv[])
{
	if(argv[1] != NULL)
	{
		if(chdir(argv[1]) < 0)
		{
			switch(errno)
			{
				case ENOENT:
					printf("DIRECTORY NOT FOUND\n");
					break;
				case ENOTDIR:
					printf("NOT A DIRECTORY NAME\n");
					break;
				case EACCES:
					printf("YOU DO NOT HAVE RIGHT TO ACCESS\n");
					break;
				default:
					printf("SOME ERROR HAPPENED IN CHDIR\n");
					break;
			}
		}
	}	
	else
	{
		printf("error, the input is null\n");
	}
}

void execute_new(char *argv[])
{
	pid_t pid = fork();
	if(pid < 0)
	{
		printf("OME ERROR HAPPENED IN FORK\n");
		exit(-1);
	}
	else if(pid == 0) //child
	{
		if(execvp(argv[0], argv) < 0)
		{
			switch(errno)
			{
				case ENOENT:
					printf("COMMAND OR FILENAME NOT FOUND\n");
					break;
				case EACCES:
					printf("YOU DO NOT HAVE RIGHT TO ACCESS\n");
					break;
				default:
					printf("SOME ERROR HAPPENED IN EXEC\n");
					break;
			}
		}
	}
	else //parent
	{
		wait(NULL); //wait for  child
	}
}



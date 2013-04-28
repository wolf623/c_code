#include <stdio.h>
#include <string.h>

/*
 * There are two ways to jude if the process exist or not
 * one is use the ps command, change the output to a file, then read the file and jude it
 * the other is read the path /proc, all the running process will have the file under the path
 * also we give a API to get the pid of the process if there is a need.
*/

/* This API is use the ps command */
static int isprocessexist(char *process_name, int *flag)
{
	char cmdstr[128] = {0};
	char filename[128] = {0};
	char buff[128] = {0};
	FILE *fp;
	*flag = 0;

	snprintf(filename, sizeof(filename)-1, "/tmp/tmp_%s_file", process_name);
	//Command: ps -ae | grep %s > %s | grep -v "grep"
	snprintf(cmdstr, sizeof(cmdstr)-1, "ps -ae | grep %s > %s | grep -v \"grep\"", process_name, filename);
	system(cmdstr);

	if((fp = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "Error: open file %s failed\n", filename);
		return -1;
	}

	if(fgets(buff, sizeof(buff)-1, fp) != NULL)
	{
		if(strstr(buff, process_name) != NULL)
		{
			//find at least one process exist, set the flag
			*flag = 1; 
			//rm the temp file
			snprintf(cmdstr, sizeof(cmdstr)-1, "rm %s", filename);
			system(cmdstr);

			return 0;
		}
	}

	return 0;
}

/* This API go through the path /proc to find the name of the process */
/* Notic: there are many string we can use to jude the process exist or not,
   For example, we can use the d_name, status or exe if you want 
   But you know that it go through the path /proc, so i think it is not the 
   best way to do simple judge the process exist or not
*/
static int ispidexist(char *cmdstr)
{
	DIR *dir;
	struct dirent *nextdir;
	FILE *fp;
	char buff[MAX_BUFF_SIZE+1];
	char cmdname[MAX_BUFF_SIZE+1];
	int len = 0;

	if(cmdstr == NULL)
	{
		printf("Error: the cmdstr should not be NULL\n");
		return -1;
	}

	dir = opendir("/proc");
	if(dir == NULL)
	{
		printf("Error: open proc directory failed\n");
		return -1;
	}

	while((nextdir = readdir(dir)) != NULL)
	{
		//skip the . and .. directory
		if(strcmp(nextdir->d_name, ".") == 0 || strcmp(nextdir->d_name, "..") == 0)
		{
			continue;
		}

		//skip the directory if it is not a digit
		if(!isdigit(*nextdir->d_name))
		{
			continue;
		}

		//Judge if we can open the status or not
		//snprintf(buff, MAX_BUFF_SIZE, "/proc/%s/status", nextdir->d_name);
		snprintf(buff, MAX_BUFF_SIZE, "/proc/%s/exe", nextdir->d_name);
		
		if((len = readlink(buff, cmdname, sizeof(cmdname)-1)) < 0)
		{
			continue;
		}
		cmdname[len] = 0;

		if(strstr(cmdname, cmdstr) != NULL)
		{
			//find one
			closedir(dir);
			return 1;
		}

	#if 0
		snprintf(buff, MAX_BUFF_SIZE, "/proc/%s/cmdline", nextdir->d_name);
		if((fp = fopen(buff, "r")) == NULL)
		{
			continue;
		}

		if(fgets(buff, MAX_BUFF_SIZE, fp) == NULL)
		{
			fclose(fp);
			continue;
		}
		fclose(fp);
	#endif

	#if 0
		//Name: cmdname
		if(sscanf(buff, "%*s %s", cmdname) == 0)
		{
			//something was error
			continue;
		}

		if(strcmp(cmdname, cmdstr) == 0)
		{
			//find one, the pid is exist, then return back.
			closedir(dir);
			return 1;
		}
	#endif
		
	#if 0
		if(strstr(buff, cmdstr) != NULL)
		{
			//find one, the pid is exist, then return back.
			closedir(dir);
			return 1;
		}
	#endif

	}

	closedir(dir);

	return 0;
}

satic int get_proc_pid(const char *proc_name, int *pid_array, int *num)
{
	char cmdline[128] = { 0 };
	char tempfile[128] = { 0 };
	char buff[128] = { 0 };
	FILE *fp;
	int number = 0;

	snprintf(tempfile, sizeof(tempfile)-1, "/tmp/tmp_%s_file", proc_name);

	//command: ps aux | grep proc_name | grep -v "grep" | awk '{print $2}'
	snprintf(cmdline, sizeof(cmdline), 
			"ps aux | grep %s | grep -v \"grep\" | awk \'{print $2}\' > %s", proc_name, tempfile);
	system(cmdline);
	
	if((fp = fopen(tempfile, "r")) == NULL)
	{
		fprintf(stderr, "Error: open %s file failed\n", tempfile);
		return -1;
	}

	while(fgets(buff, sizeof(buff)-1, fp) != NULL)
	{
		number++;
		if(pid_array != NULL)
		{
			*pid_array++ = atoi(buff);
		}
	}
	
	*num = number;
	snprintf(cmdline, sizeof(cmdline)-1, "rm %s", tempfile);
	system(cmdline);

	return 0;
}

int main(int argc, char *argv[])
{
	int flag = 0;
	int array[10] = { 0 };
	int i = 0, num = 0;

	if(isprocessexist("sshd", &flag) == 0)
	{
		if(flag == 1)
			printf("process exist\n");
		else
			printf("process no exist\n");
	}
	
	if(get_proc_pid("sshd", array, &num) != -1)
	{
		for(i = 0; i < num; i++)
			printf("%d ", array[i]);
	}

	printf("\n");
	return 0;
}

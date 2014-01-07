#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_BUFF_SIZE	4096

/*
 * if the pid exist, then return 1 or return 0
 * Notice: the cmdstr is the full directory
*/
int ispidexist(char *cmdstr)
{
	DIR *dir;
	struct dirent *nextdir;
	FILE *fp;
	char buff[MAX_BUFF_SIZEI+1];

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
		snprintf(buff, MAX_BUFF_SIZE, "/proc/%s/cmdline", nextdir->d_name);
		if((fp = fopen(buff, "r")) == NULL)
		{
			continue;
		}

		if(fgets(buff, MAX_BUFF_SIEZ, fp) == NULL)
		{
			fclose(fp);
			continue;
		}
		fclose(fp);

		if(strcmp(buff, cmdstr) == 0)
		{
			//find one, the pid is exist, then return back.
			closedir(dir);
			return 1;
		}
	}

	closedir(dir);

	return 0;
}

	
int main(int argc, char *argv[])
{
	int result = ispidexist("");

	return 0;
}

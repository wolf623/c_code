#include<stdio.h>
#include<dirent.h>
#include<string.h>

#define PROC_PATH "/proc"

int search_deamon_proc(procname, pid)
const char *procname;
int *pid;
{
	DIR *dir;
	struct dirent *dire;
	int i, len, proc_len, proc_pid;
	char *str;
	char tmp[256] = {0};
	char path[256] = {0};

	proc_len = strlen(procname);

	if ((dir = opendir(PROC_PATH)) == NULL) {
		//log;
		return -1;
	}

	while((dire = readdir(dir)) != NULL) {
		
		if ((proc_pid = atoi(dire->d_name)) == 0) {
			continue;
		}
		//printf("%s\n", dire->d_name);	
		snprintf(tmp, sizeof tmp, "%s/%s/exe", PROC_PATH, dire->d_name);
		
		if ((len = readlink(tmp, path, sizeof path - 1)) < 0) {
			continue;
		}
		path[len] = 0;

		if ((str = strrchr(path, '/')) == NULL) {
			continue;
		}
		//printf("%s\n", str); 	
		if (strncmp(procname, ++str, proc_len) == 0) {
			if (str[proc_len] == '\0' 
				|| str[proc_len] == ' ') {
				pid[i] = proc_pid;
				i++;
			}
		
		}
	
	}

	closedir(dir);
	return 0;
}
int main(int ac, char *av[])
{
	int i;
	int pid[256] = {0};
	if (ac != 2) {
		//log;
		return -1;
	}
	if (search_deamon_proc(av[1], pid) != 0){
		//log;
		return -1;
	}

	for (i = 0; pid[i]; i++) {
		printf("%d\n", pid[i]);
	}

	return 0;
}

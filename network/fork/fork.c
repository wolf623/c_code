#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int arg, char *argv[])
{
	
	int gl_val = 1;
	
	int filesfd[2];
	int fd[2];
	char buf[10];
	memset(buf, 0, sizeof(buf));
	char buff[10] = {0};
	
	int rc = pipe(filesfd);
	rc = pipe(fd);
	if(rc != 0)
	{
		printf("pipe failed, %d\n", rc);
		return -1;
	}
	
	pid_t pid = fork();
	if(pid < 0)
	{
		printf("fork failed.\n");
		return -1;
	}
	else if(pid == 0)
	{
		//child
		printf("I'am child...\n");
		gl_val = 23;
		close(filesfd[0]);
		sprintf(buf, "%s", "abc");
		write(filesfd[1], buf, strlen(buf));
		printf("child: gl_val %d, write: %s, strlen(buf): %d\n", gl_val, buf, (int)strlen(buf));
		close(filesfd[1]);

		close(fd[1]);
		read(fd[0], buff, 3);
		printf(">>>parent: read %s\n", buff);
		close(fd[0]);
		
		exit(0);
	}
	else
	{
		//parent
		close(filesfd[1]);
		sleep(3);
		read(filesfd[0], buf, 3);
		printf("parent: gl_val %d, read: %s, sizeof(buf): %d\n", gl_val, buf, (int)sizeof(buf));
		close(filesfd[0]);

		close(fd[0]);
		sprintf(buff, "%s", "123");
		write(fd[1], buff, strlen(buff));
		close(fd[1]);
		
		waitpid(pid, NULL, 0);
		exit(0);
	}
	
	return 0;
}


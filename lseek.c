#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int i;
	FILE *fp;
	int fd;
	char buff[] = "Hello world!";
	if( (fp = fopen("file.log", "a")) == NULL)
	{
		printf("%s(): fopen error\n", __FUNCTION__);
		return 0;
	}
	
	fd = fileno(fp);

	for(i=0; i<2; i++)
	{
		//fprintf(fp, "%s", buff);
		write(fd, buff, sizeof(buff));
		lseek(fd, -2L, SEEK_CUR);
	}


	write(fd, "\n", 1);	
	fclose(fp);

	return 0;
}

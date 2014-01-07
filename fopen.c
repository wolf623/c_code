#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define FILE_NAME	"temp_fopen_file.cf"
#define MAX_LINE_READ	23

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./a.out type\n");
		return -2;
	}

	char read_buff[32] = {0}; 
	if(atoi(argv[1]) == 1)
	{
		FILE *fp;
		if((fp = fopen(FILE_NAME, "w")) == NULL)
		{
				printf("fopen %s for write failed\n", FILE_NAME);
				return -1;
		}
		fprintf(fp, "Hello, wolf!\n");
		fclose(fp);
		
		//read file
		if((fp = fopen(FILE_NAME, "r")) == NULL)
		{
				printf("fopen %s for read failed\n", FILE_NAME);
				return -1;
		}
		if(fgets(read_buff, MAX_LINE_READ, fp) == NULL)
		{
				printf("read %s failed\n", FILE_NAME);
				fclose(fp);
				return -1;
		}
		printf("Read from the file: %s\n", read_buff);
		fclose(fp);
		
		char cmd[32] = {0};
		sprintf(cmd, "rm -f %s\n", FILE_NAME);
		system(cmd);
	}
	else if(atoi(argv[1]) == 2)
	{
		int fd;
		if((fd = open(FILE_NAME, O_WRONLY | O_CREAT, 0666)) == -1)
		{
			printf("open %s for write failed\n", FILE_NAME);
			return -1;
		}
		char *write_msg = "Hello, wolf!\n";
		int write_msg_len = strlen(write_msg);
		//printf("msg len: %d\n", write_msg_len);
		if(write(fd, write_msg, write_msg_len) != write_msg_len)
		{
			printf("write %s file failed, %s\n", FILE_NAME, strerror(errno));
			close(fd);
			return -1;
		}
		close(fd);

		//read file
		if((fd = open(FILE_NAME, O_RDONLY, 0666)) == -1)
		{
			printf("open %s for read failed!\n", FILE_NAME);
			return -1;
		}
		if(read(fd, read_buff, MAX_LINE_READ) < 0)
		{
			printf("read %s file failed, %s\n", FILE_NAME, strerror(errno));
			return -1;
		}
		printf("read form file: %s\n", read_buff);
		char cmd[32] = {0};
		sprintf(cmd, "rm -f %s\n", FILE_NAME);
		system(cmd);
	}
	else
	{
		printf("input error\n");
		return -1;
	}

	return 0;
}
	

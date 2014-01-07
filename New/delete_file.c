/**************************************************
Description	: A callback function of delete file
Author		: wolf
Time		: 2013-3-6
**************************************************/

/*****************************************************
Knowledge Point	:
Before you delete the file, you need to make sure 
the file is exist and it is not a directory.
we can use the access() and stat() function to dot it
but we call the remove() function to delete the file
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

static int file_exist(const char *filename)
{
	if(access(filename, F_OK) == 0)
		return 1;
	else
		return 0;
}

static int is_dir(const char *filename)
{
	struct stat statbuf;
	
	if(file_exist(filename) && stat(filename, &statbuf))
	{
		if(S_ISDIR(statbuf.st_mode) != 0)
			return 1;
	}

	return 0;
}


static int delete_file(const char *file)
{
	if(file_exist(file) && ! is_dir(file) &&
		!remove(file))
		return 1;
	else
		return 0;
}

int main(int argc, char *argv[])
{
	int ec = 0;
	if(argc != 2)
	{
		fprintf(stdout, "Error: Usage ./a.out filename\n");
		return -1;
	}

	ec = delete_file(argv[1]);
	fprintf(stdout, "Delete the file %s %s\n", argv[1], (ec==1) ? "success" : "failed");

	return 0;
}
	

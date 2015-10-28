#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Get the directory portion of the file
*/
char *file_path(const char *filepath, char *path)
{
	char *ptr;
	
	if(filepath == NULL || path == NULL)
		return NULL;
	
	if((ptr = strrchr(filepath, '/')) != NULL
		|| (ptr = strrchr(filepath, '\\')) != NULL)
	{	
		strncpy(path, filepath, ptr-filepath);
		path[ptr-filepath] = '\0';
		return path;
	}

	return NULL;
}

/*
 * Get the file name of the file
*/
char *file_name(const char *filepath, char *filename)
{
	char *ptr;
	
	if(filepath == NULL || filename == NULL)
		return NULL;

	if((ptr = strrchr(filepath, '/')) != NULL
		|| (ptr = strrchr(filepath, '\\')) != NULL)
	{
		strcpy(filename, ptr + 1);
	}
	else
	{
		strcpy(filename, filepath);
	}

	return filename;
}


int main(int argc, char *argv[])
{
	char buff[128] = { 0 };
	char *ptr_path = buff;
	char *ptr_name = buff + 64;
	ptr_path = file_path(argv[1], ptr_path);
	ptr_name = file_name(argv[1], ptr_name);

	
	printf("The path: %s\n", ptr_path);
	printf("The name: %s\n", ptr_name);

	return 0;
}

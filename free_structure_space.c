#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RESET_DATASPACE(str)		if((str)) { FreeDataSpace((str)); } (str) = NULL
#define FREE_DATASPACE(str) 		if((str)) { FreeDataSpace((str)); }

#define MAXLENGTH	4094 //max length

typedef struct _data_t
{
	char *string;
	int length;
}data_t;

typedef struct _g_data_t
{
	data_t *data;
	int len;
}g_data_t;

data_t *MakeDataSpace(char *str, int len)
{
	data_t *data;

	if(len > MAXLENGTH)
	{
		fprintf(stdout, "Error: The len is too long, can't longger than %d\n", MAXLENGTH);
		return NULL;
	}

	if((data = (data_t *)malloc(sizeof(data_t) + len)) == NULL)
	{
		fprintf(stdout, "Error: malloc failed\n");
		return NULL;
	}

	data->string = (char *)(((char *)data) + sizeof(data_t));

	if(str != NULL)
		memcpy((char *)data->string, (char *)str, (int)len);
	else
		memcpy((char *)data->string, 0, (int)len);

	data->length = len;

	return data;
}

void FreeDataSpace(data_t *data)
{
	if(data != NULL)
	{
		if(data->string != (((char *)data) + sizeof(data_t)))
		{
			if(data->string != NULL)
			{
				free((void *)data->string);
			}
		}

		free((void *)data);
	}
}


int main(int argc, char *argv[])
{
	static g_data_t abc = { 0 };
	char buff[8] = {0};

	//RESET_DATASPACE(abc.data);
	FREE_DATASPACE(abc.data);

	if(abc.data == NULL)
	{
		fprintf(stdout, "After RESET_DATASPACE() function, it is NULL\n");
	}

	abc.data = MakeDataSpace(buff, sizeof(buff));

	memcpy(abc.data->string, "abc", sizeof(buff));

	printf("%s\n", abc.data->string);

	return 0;
}

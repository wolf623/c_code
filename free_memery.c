#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct _memery_data_t memery_data_t;
struct _memery_data_t
{
	int abc;
	char *data_ptr;
};

int main(int argc, char *argv[])
{
	char buff[128] = { 0 };
	memery_data_t *ptr;	
	ptr = (memery_data_t *)malloc(sizeof(memery_data_t));
	if(ptr == NULL)
	{
		printf("malloc for ptr structer failed\n");
		return -1;
	}
#if 1
	if((ptr->data_ptr = (char *)malloc(sizeof(buff))) == NULL)
	{
		printf("malloc for data_ptr failed\n");
		return -1;
	}
#endif
	ptr->abc = 23;
	strncpy(ptr->data_ptr, "Hello, world", sizeof(buff));
	
	printf("abc: %d data_ptr: %s\n", ptr->abc, ptr->data_ptr);
	
	free((memery_data_t *)ptr);
	free((char *)ptr->data_ptr);
		
	//ptr->abc = 3344;
	//strncpy(ptr->data_ptr, "3388", sizeof(buff));

	printf("abc: %d data_ptr: %s\n", ptr->abc, ptr->data_ptr);

	return 0;
}



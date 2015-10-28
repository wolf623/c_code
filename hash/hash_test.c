#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./hash/hash.h"

int main(void)
{
	if(hash_init() != 0)
	{
		printf("initial hash failed\n");
		return -1;
	}
	
	int val = 23;
	if(hash_add(0, &val, sizeof(int)) != 0)
		printf("add data into hash failed!\n");
	
	int value = 230;
	if(hash_add(2, &value, sizeof(int)) != 0)
		printf("add data into hash failed!\n");

	hash_print();
	
	data_hash_t *p = NULL;
	if((p = hash_find(1)) != NULL)
	{
		printf("find it, key: %d, data: %d\n", p->key, *(int *)p->data);
	}
	else
	{
		printf("not find it\n");
	}

	if((p = hash_deep_find(0, &val, sizeof(int))) != NULL)
	{
		printf("find it, key: %d, data: %d\n", p->key, *(int *)p->data);
	}
	else
	{
		printf("not find it\n");
	}


	return 0;
}


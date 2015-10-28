#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct test_t
{
	char name[4096];
}test;

int 
main(void)
{
	test a, b;

	int ec;

	memset(&a, 0, sizeof(a));
	memset(&b, 0, sizeof(b));


	strcpy(a.name, "lm");
	strcpy(b.name, "lmb");

	char str[4096] = "Hello World\n";

	printf("strlen(str) = %d\n", strlen(str));
	printf("sizeof(str) = %d\n", sizeof(str));
	printf("strlen(a->name) = %d\n", strlen((char *)(a.name)));
	
	ec = strncmp((char *)(a.name), (char *)(b.name), 3);

	printf("ec = %d\n", ec);

	exit(0);
}

#include <stdio.h>

char *return_ptr(void)
{
	//char *ptr = "Hello Wolf\n";
	char ptr[] = "Hello Wolf\n";
	return ptr;
}

int main(int argc, char *argv[])
{
	char *str = NULL;
	str = return_ptr();

	printf("%s", str);

	return 0;
}

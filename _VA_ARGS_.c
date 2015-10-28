#include <stdio.h>
#include <string.h>

#define printptr(fmt, ...)  fprintf(stdout, fmt, ##__VA_ARGS__)

int main(int argc, char *argv[])
{
	printptr("Hello World\n");
	printptr("%s\n", "Hello");
	printptr("%s%d\n", "wolf", 623);

	return 0;
}

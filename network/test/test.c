#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	printf("INT_MAX %d, %d, SSIZE_MAX %ld\n", INT_MAX, (INT_MAX & ~8191), SSIZE_MAX);
	
	return 0;
}
	

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char path[128];
	realpath("lm/GitHub/New", path);
	printf("path: %s\n", path);

	return 0;
}

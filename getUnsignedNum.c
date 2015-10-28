#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getUnsignedNum(char *ptr, int *unum)
{
	char buf[128];
	int num = 0;
	char *endptr = 0;

	fflush(stdout);

	fprintf(stdout, "%s: ", ptr);

	if(fgets(buf, sizeof(buf), stdin) == NULL)
	{
		return -1;
	}

	num = (int)strtoul(buf, &endptr, 0);

	*unum = num;

	return 0;
}


int
main(int argc, char *argv[])
{
	int abc = 0;
	getUnsignedNum("Please input a num", &abc);

	fprintf(stdout, "What you input is %d\n", abc);

	return 0;
}

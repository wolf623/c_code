#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *ep = NULL;
	int num = -1;
	num = strtol(argv[1]+4, &ep, 10);
	if(ep==NULL)
		printf("Input error\n");
	else if(num < 0)
		printf("input num error\n");
	else
		printf("you input the num is: %d, ep: %s\n", num, ep);

	return 0;
}


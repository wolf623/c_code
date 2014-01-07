#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char buff[128] = {0};
	if(ttyname_r(0, buff, sizeof(buff)) == 0)
		printf("%s\n", buff);
	else
		printf("ttyname_r failed\n");
	
	return 0;
}

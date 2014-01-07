#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	printf("start ...\n");

	if(freopen("stdout.tmp", "a+w", stdout) == NULL)
	{
		printf("freopen failed\n");
		return -1;
	}
	
	printf(">>>>freopen stdout successful\n");

	fprintf(stdout, "reopen stdout to stdout.tmp file\n");
	printf("reopen stdout...\n");
	fclose(stdout);
	
	freopen("/dev/tty", "w", stdout);
	fprintf(stderr, "stderr: close stdout\n");
	fprintf(stdout, "stdout: close stdout\n");
	printf("close stdout\n");

	return 0;
}
		

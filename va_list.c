/* Print variable message log */
/* Beside vsprintf(), it has vprintf()/vfprintf()/vsnprintf() and 
sprintf()/fprintf()/printf()/fflush(stdout) etc */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAXLINE		128

void printlog(FILE *fp, const char *text, ...)
{
	va_list ap;
	char buff[MAXLINE] = {0};

	va_start(ap, text);
	vsnprintf(buff, MAXLINE, text, ap);
	va_end(ap);
	buff[127] = '\0';

	printf("string: %s, length: %d\n", buff, (int)strlen(buff));
	char buf[128] = {0};
	memcpy(buf, buff, strlen(buff)+1);
	printf("copy string: %s\n", buf);

	int i = 0;
	int length = strlen(buff);
	for(i=0; i<128; i++)
	{
		printf("%c", buff[i]);
	}
	printf("----\n");

	fprintf(fp, "%s\n", buff);
}

int main(int argc, char *argv[])
{
	printlog(stdout, "wolf%d", 623);

	return 0;
}

#include <stdio.h>
#include <stdarg.h>

#define MAXLINE		128

void printlog(FILE *fp, const char *text, ...)
{
	va_list ap;
	char buff[MAXLINE];

	va_start(ap, text);
	vsnprintf(buff, MAXLINE, text, ap);
	va_end(ap);

	fprintf(fp, "%s\n", buff);
}

int main(int argc, char *argv[])
{
	printlog(stdout, "wolf%d%s", 623, "abc");

	return 0;
}

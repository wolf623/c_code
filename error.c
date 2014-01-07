#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#define MAXLINE 	128

static void err_doit(int flag, int error, const char *fmt, va_list ap);

void
err_sys(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	//abort();
	exit(0);
}

static void
err_doit(int flag, int error, const char *fmt, va_list ap)
{
	char buff[MAXLINE];

	vsnprintf(buff, MAXLINE, fmt, ap);

	if(flag)
	{
		snprintf(buff+strlen(buff), MAXLINE-strlen(buff), ": %s", strerror(error));
	}
	
	strcat(buff, "\n");
	fflush(stdout);
	fputs(buff, stderr);
	fflush(NULL);
}


int
main(void)
{
	err_sys("in the %s", __FUNCTION__);

	exit(0);
}

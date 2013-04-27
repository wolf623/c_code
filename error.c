#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <syslog.h>
#include <errno.h>

#define MAXLINE		128

int daemon_proc;	//use it in other files
	
static void err_doit(int errnoflag, int level, const char *fmt, va_list ap);

void err_sys(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, LOG_INFO, fmt, ap);
	va_end(ap);
	
	exit(1);
}

void err_quit(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(0, LOG_ERR, fmt, ap);
	va_end(ap);

	return;
}

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
	int errno_save, len;
	char buff[MAXLINE + 1];

	errno_save = errno;

#ifdef HAVE_VSNPRINTF
	vsnprintf(buff, MAXLINE, fmt, ap);
#else
	vsprintf(buff, fmt, ap);
#endif
		
	len = strlen(buff);
	if(errnoflag)
	{
		snprintf(buff+len, MAXLINE-len, ": %s", strerror(errno_save));
	}

	strcat(buff, "\n"); //make a new line
	
	/* if the process is a daemon, then use the syslog() to print log */
	if(daemon_proc)
	{
		syslog(level, buff);
	}
	else
	{
		fflush(stdout);
		fputs(buff, stderr);
		fflush(stderr);
	}
	
	return;
}

#ifdef TEST
int main(int argc, char *argv[])
{
	//err_sys("Hello Wolf");
	err_quit("Hello Wolf");

	return 0;
}
#endif



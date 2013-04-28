#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syslog.h>

int
main(void)
{
	openlog("test", LOG_CONS | LOG_PID, LOG_USER);
	//syslog(LOG_INFO, "This is a message just for test\n");
	closelog();

	exit(0);
}

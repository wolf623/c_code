#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "is_proc_running.h"

static void monitor_abc()
{
	pid_t pid;

	if(!is_process_running(&pid))
	{
		system("/home/c_learing/GitHub/New/monitor_softwares/client");
		fprintf(stdout, "restart the client process...\n");
		return;
	}
	
	fprintf(stdout, "client process is running, pid = %d\n", pid);
}

void monitor_softwares()
{
	monitor_abc();
}

int main(void)
{
	_sm_daemonize();

	while(1)
	{
		monitor_softwares();
		sleep(5);
	}

	return 0;
}


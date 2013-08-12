#ifndef _IS_PROC_RUNNING_H_
#define _IS_PROC_RUNNING_H_

#define PROC_PID_FILE   "proc.pid"

void _sm_daemonize(void);

int is_process_running(pid_t *pid);

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

static void sigaction_func(int signum, siginfo_t *info, void *myact)
{
	printf("signal_func(): signum %d, si_signo %d, %s\n", signum, info->si_signo, (char *)info->si_value.sival_ptr);
	abort();
}

int install_signal_with_sigaction(int signum)
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	struct sigaction old_sa;
	//sa.sa_handler = SIG_DFL; //take default action
	//sa.sa_handler = SIG_IGN; //ignor signal
	sa.sa_sigaction = sigaction_func; //my self deal with function
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	int rc;
	if((rc = sigaction(signum, &sa, &old_sa)) < 0)
	{
		printf("install signal %d failed, (%d)\n", signum, rc);
	}
	return 0;
}

static void signal_func(int val)
{
	printf("signal_func(): %d\n", val);
	abort();
}

int install_signal_with_signal(int signum)
{
	signal(signum, signal_func);
}

int main(int argc, char *argv[])
{
	//install_signal_with_sigaction(SIGINT);
	install_signal_with_signal(SIGINT);
	
	while(1)
	{
		printf("wait for signal to come in...\n");
		sleep(10);
		union sigval sig;
		//char str[]= "Hello, Signal";
		//sig.sival_ptr = &str;
		sig.sival_int = 23;
		sigqueue(getpid(), SIGINT, sig);
	}
	
	return 0;
}


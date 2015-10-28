#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>  
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

#include "sendlog.h"

void LOGFUNC(LOG_MODULE module, LOG_LEVEL severity, 
	unsigned long eventId, const char* text, ...)
{
	static int sfd = -1;
    static struct sockaddr_in cli_addr;
    LOGMSGDATA ldata;
    va_list ac;
    struct hostent *hp;

    if (sfd == -1) 
	{
		hp = gethostbyname ("smm");

        if (hp == NULL)
        {
            fprintf(stderr, "Can not find host smm %s:%d,%s():%s\n", __FILE__, __LINE__, __FUNCTION__, strerror(errno));
            return;
        }

        if ((sfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) 
		{
            fprintf(stderr, "%s:%d,%s():%s\n", __FILE__, __LINE__, __FUNCTION__, strerror(errno));
		   	return;
        }
	
        bzero((char*)&cli_addr, sizeof(cli_addr));
        cli_addr.sin_family = PF_INET;

        memcpy (&cli_addr.sin_addr.s_addr, hp->h_addr, hp->h_length);

        cli_addr.sin_port = htons(LOG_PORTNUM);
    }

    va_start(ac, text);
    vsnprintf(ldata.text, 256, text, ac);
    va_end(ac);
    ldata.mtype = LOG_MESSAGE;
    ldata.module = module;
    ldata.severity = severity;
    ldata.id = eventId;

	char ipv4[32];
	inet_ntop(AF_INET, &cli_addr.sin_addr, ipv4, sizeof(ipv4));
    printf("logging to %s: %s\n", ipv4, ldata.text);
    
    if (sendto(sfd, (char*)&ldata, sizeof(LOGMSGDATA), 0,
	       (const struct sockaddr*)&cli_addr,
	       sizeof(cli_addr)) == -1) {
		fprintf(stderr, "%s:%d,%s():%s\n", __FILE__, __LINE__, __FUNCTION__, strerror(errno));
    }
}

void print_help(void)
{
	printf("This is help message: \n");
	printf("./mysendlog -m module -l severity -t times -i interval <text>\n");
	printf("\tmodule:\n");
	printf("\t\tL_CLI = 0, L_SNMP = 1, L_QAM = 2, L_IMM = 3, L_RPC = 4, L_SYS = 5, L_CMTS = 6,\n");
	printf("\t\tL_DOCSIS_OB = 7, L_ALARM = 8, L_DPI = 9, L_DMM = 10, L_RNG = 11, L_MAC = 12, L_BPI = 13,\n");
	printf("\t\tL_DCTS = 14, L_EAM = 15, L_LC = 16, L_IPDR = 17, L_IPSEC = 18, L_ROUTER = 19, L_AAA = 20,\n");
	printf("\t\tL_CSM_TRA = 21, L_CSM_POL = 22, L_CSM_FFT = 23, L_CSM_EVT = 24, L_CSM_FSM = 25, L_CSM_HOP = 26,\n");
	printf("\t\tL_CSM_ERR = 27, L_CDB = 28, L_CFG = 29, L_LBM =30, L_CMREMOTE = 31, L_OTHER = 32\n");
	
	printf("\tleval:\n");
	printf("\t\tL_EMERGENCIES = 0, L_ALERTS = 1, L_CRITICAL = 2,\n");
	printf("\t\tL_ERRORS = 3, L_WARNINGS = 4, L_NOTIFICATIONS = 5, L_INFORMATIONAL = 6, L_DEBUGGING = 7\n");

	printf("\tflag:\n");
	printf("\t\t-t: send times, n - send n times, 0 - only one times\n");
	printf("\t\t-r: time interval, 0 - no time interval\n");
	
	return;
}


int main(int argc, char *argv[])
{
	int opt;
	char *parameters = "m:l:t:i:";
	LOG_MODULE module;
	LOG_LEVEL severity;
	int times;
	int interval;
	unsigned long id = 1;//default 
	va_list ap;
	char text[LOGGER_TEXT_SIZE];
	char *p_text = NULL;
	
	while((opt = getopt(argc, argv, parameters)) != -1)
	{
		switch(opt)
		{
			case 'm':
				if(*optarg == '-')
				{
					print_help();
					return -1;
				}
				module = atoi(optarg);
				printf("module: %d\n", module);
				break;
			case 'l':
				if(*optarg == '-')
				{
					print_help();
					return -1;
				}
				severity = atoi(optarg);
				printf("severity: %d\n", severity);
				break;
			case 't':
				if(*optarg == '-')
				{
					print_help();
					return -1;
				}
				times = atoi(optarg);
				printf("times: %d\n", times);
				break;
			case 'i':
				if(*optarg == '-')
				{
					print_help();
					return -1;
				}
				interval = atoi(optarg);
				printf("interval: %d\n", interval);
				break;
			default:
				printf("default\n");
				print_help();
				return -1;
				break;
		}
	}

	printf("argc: %d, optind: %d\n", argc, optind);
#if 1
	if((argc - optind) != 1)
	{
		printf("Incorrect inputed arguments\n");
		print_help();
		return -1;
	}
#endif

	p_text = argv[optind];
	memcpy(text, p_text, sizeof(text));
	printf("text: %s\n", text);

	LOGFUNC(module, severity, id, text);
	//LOGFUNC(L_CLI, L_DEBUGGING, 1, "This is debug message, pleas ignore it\n");
	
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int opt;
	char *parameter = "h1:2::34:";

	while((opt = getopt(argc, argv, parameter)) != -1)
	{
		switch(opt)
		{
			case 'h':
				printf("This is help message\n");
				printf("option=h, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			case '1':
				printf("what you input is '%d'\n", opt);
				printf("The parameter is: %s\n", optarg);
				printf("option=h, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			case '2':
				printf("what you input is '%d'\n", opt);
				printf("The parameter is: %s\n", optarg);
				printf("option=h, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			case '3':
				printf("what you input is '%d'\n", opt);
				printf("option=h, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			case '4':
				printf("what you input is '%d'\n", opt);
				printf("The parameter is: %s\n", optarg);
				printf("option=h, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			case '?':
				printf("option=h, optopt=%c, optarg=%s\n", optopt, optarg);
				break;
			default:
				printf("default, opt=%d\n", opt);
				break;
		}

		printf("argv[%d]=%s\n", optind, argv[optind]);
	}
	
	printf("argc: %d, optind: %d\n", argc, optind);

	for(opt=optind; opt<argc; opt++)
		printf("---argv[%d] = %s\n", opt, argv[opt]);

	printf("end...\n");

	return 0;
}
				
				


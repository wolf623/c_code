#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

/*
 * Define our fprintf, include the time
*/
#define MAX_LINES	4096 //max lines of the file

void time_fprintf(FILE *fp, int debug_level, int level, const char *fmt, ...)
{
	static log_file_lines = 0;
	va_list ap;
	char buff[128] = { 0 };
	time_t timedata;

	if(debug_level > level)
		return;
	
	//if the fp is the file or stdin or stdout?
	if((fp != stdin) && (fp != stdout) && (log_file_lines > MAX_LINES))
	{
		log_file_lines = 0;	//clear 0
		//rewind(fp); //This is eqeue to: lseek(fp, 0L, SEEK_SET);
		lseek(fp, 0L, SEEK_SET);
	}

	if(time(&timedata) == -1)
		return;

	if(ctime_r(&timedata, buff) == NULL)
		return;
	
	buff[strlen(buff)-1] = '\0'; //get rip of new line
	fprintf(fp, "[%s]-", buff);

	log_file_lines++;
	
	va_start(ap, fmt);
	vfprintf(fp, fmt, ap);
	va_end(ap);

	return;
}


int main(int argc, char *argv[])
{
	FILE *fp;
	if((fp = fopen("log.file", "w+")) != NULL)
	{
		time_fprintf(fp, 1, 2, "Hello %s\n", argv[0]);
	}

	//time_fprintf(stdout, 1, 2, "Hello %s\n", argv[0]);
	
	return 0;
}


/*
 * =====================================================================================
 *
 *       Filename:  dealWithFile.c
 *
 *    Description:  deal with source file
 *
 *        Version:  1.0
 *        Created:  11/24/14 14:31:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Source File Like this:
 * <132>2014-11-19,15:29:18.4 C10G-107 CMTS[DOCSIS]: <73055400> CM partial service;CM-MAC=14:cf:e2:ac:d6:82;CMTS-VER=3.0;(event count 19, last time: 2014-11-19,15:29:18.4)
 */

static int file_exist( const char *file )
{
	if(access(file, F_OK) == 0 )
		return 1;
	else
		return 0;
}

#define DOCSLOG_TAIL_STR_HEAD "(event count "
#define DOCSLOG_LASTTIME_STR ", last time"	
int deal_with_text(const char *text)
{
	int i, len;
	char tmp[512] = {0};
	char *p;

	if(text == NULL)
		return -1;
	
	if(strlen(text) < 23) //check length
		return -1;

	strncpy(tmp, text+1, 3);
	//fputs(tmp, stdout);
	//puts(tmp);

	strncpy(tmp, text+5, sizeof(tmp));
	p = strtok(tmp, " ");
	if(p == NULL)
		return -1;

	p = strtok(NULL, "]: <");
	if(p == NULL)
		return -1;
	
	//puts(p);
	p = strtok(NULL, "<");
	if(p == NULL)
		return -1;
	
	//puts(p);
	
	p = strtok(NULL, ">");
	if(p == NULL)
		return -1;
	
	//puts(p);

	char buf[512] = {0};
	strncpy(buf, p+strlen(p)+2, sizeof(buf));
	puts(buf);

	char *tail = NULL;
	len = strlen(buf);
	int new_len = len;

	for(i=1; i<len; ++i)
	{
		if(!isprint(buf[len-i]))
		{
			new_len = len - i;
			buf[new_len] = '\0';
		}
		else
		{
			break;
		}
	}

	len = new_len;
	
	for(; i<len; ++i)
	{
		if(strstr(&buf[len-i], DOCSLOG_TAIL_STR_HEAD))
		{
			new_len = len - i - 1;
			buf[new_len] = '\0';
			tail = &buf[len - i + 13];
			break;
		}
	}

	len = new_len;

	int counts = 1;
	char last_time[22] = {0};

	if(tail)
	{
		p = strtok(tail, DOCSLOG_LASTTIME_STR);
	}

	if(tail && p)
	{
		counts = atoi(p);
		if(counts <= 0)
			counts = 1;
		printf("counts: %d\n", counts);

		p = strtok(NULL, ":");
		if(p)
		{
			p = strtok(NULL, ")");
			if(p)
			{
				strncpy(last_time, p+1, sizeof(last_time));
				puts(last_time);
			}
		}
	}

	return 0;	
}

int deal_with_file(char *filename)
{
	char buff[512] = {0};
	if(filename == NULL)
		return -1;

	if(file_exist(filename))
	{
		FILE *fp = fopen(filename, "r");
		if(fp)
		{
			while(fgets(buff, 512, fp))
			{
				deal_with_text(buff);
			}
			fclose(fp);
		}
		else
		{
			printf("%s(): open file %s filed!\n", __FUNCTION__, filename);
			return -1;
		}
	}
	
}

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		deal_with_file(argv[1]);
	}
	else
	{
		printf("Usage: ./a.out <filename>\n");
		return -1;
	}

	return 0;
}


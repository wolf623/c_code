/*
 * This file is used for reading the config file
 * The config file as like this:
 * ------------------------------
 * #This is config file for xxx
 * abc 23
 * #define wolf
 * wolf	"abc"
 * ------------------------------
 * 2013-11-4
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * When we read the config file, then we can save them into 
 * the data structure at the same time.
 * but now, we only print them.
*/
int read_config_file(char *filename)
{
	FILE *fp;
	char buffer[512];
	int line = 0;	//which line
	char *p = NULL;
	int pos = 0; //the position in the line

	if(filename == NULL)
	{	
		printf("Error: the file name is null\n");
		return -1;
	}

	if((fp = fopen(filename, "r")) == NULL)
	{
		printf("Error: open the %s failed\n", filename);
		return -1;
	}

	//fgets will read one line for each calls
	while((fgets(buffer, sizeof(buffer), fp)) != NULL)
	{
		line++;
		p = buffer;

		//skip the '#' line, null line, go for next line
		if((*p == '\n') || (*p == '#') || (*p == '\0'))
		{
			continue;
		}

		/* the line is stored in p now, 
		 * as like this: char *p = 'abc 23'
		*/
		p[strlen(p)-1] = '\0';//the line is store in p now.
		
		/*
		 * The define should like this:
		 * attribute	value
		*/
		if((pos = strcspn(p, "\t ")) == 0)
		{
			printf("Error: %d line error format\n", line);
			fclose(fp);//close the file
			return -1;
		}

		p[pos] = '\0';//replace the '\t '

		//now, we can get the attribute name
		//TDO later
		printf("Attribute name: %s, ", p);

		//go next for search the value
		p += (pos + 1); 
		while(isspace(*p))	//skip the space
		{
			p++;
		}
		
		//printf(">>>%s, len: %d\n", p, strlen(p));
		if(strlen(p) == 0)
		{
			printf("\nError: %d line error format, there is no value defined\n", line);
			return -1;
		}
		
		printf("value: %s\n", p); //print the value

		/*
		//we do this in case that there is no value
		pos = strlen(p) - 1;
		while(pos >= 0 && isspace(p[pos]))
		{
			pos--;
		}
		p[pos+1] = '\0';//must end of the '\0'
		*/
	}

	return 0;
}


int main(void)
{
	read_config_file("xx.conf");

	return 0;
}

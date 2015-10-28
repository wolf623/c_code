#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "md5.h"

int main(int argc, char *argv[])
{
#if 1
	unsigned char *data = "casa";
	unsigned char md[16] = "";
	int i;
	char tmp[3] = {'\0'};
	char buff[33] = {'\0'};

	MD5(data, strlen(data), md);

	for(i=0; i<16; i++)
	{
		sprintf(tmp, "%2.2x", md[i]);
		strcat(buff, tmp);
	}

	printf("passwd: %s\n", buff);
#endif
	
#if 0
	MD5_CTX ctx;
	unsigned char *data = "casa";
	unsigned char md[16];
	char buff[33] = {'\0'};
	char tmp[3] = {'\0'};
	int i;

	MD5_Init(&ctx);
	MD5_Update(&ctx, data, strelen(data));
	MD5_Final(md, &ctx);

	for(i=0; i<16; i++)
	{
		sprintf(tmp, "%2.2x", md[i]);
		strcat(buff, tmp);
	}

	printf("passwd: %s\n", buff);
#endif

	return 0;
}

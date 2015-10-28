#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hex2int(c) ( (c >= '0' && c <= '9') ? (c - '0') : ((c & 0xf) + 9) )

int main(int argc, char *argv[])
{
    char *p = argv[1];
  
    int num = 0;
    if(isxdigit(p[0]))
        num = hex2int(p[0]);
    else
    	printf("%c is not a hex character\n", p[0]);

    printf("num = %d\n", num);

    printf("argv[1] = %s\n", argv[1]);

    printf("sizeof(char *)p = %d\n", sizeof(p));

    printf("strlen(char *)p = %d\n", strlen(p));


    exit(0);
}
    


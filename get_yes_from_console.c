#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void get_confirm_yes_input(char *string);

int main(int argc, char *argv[])
{
    char str[128];
    sprintf(str, "Please type YES to confirm");

    //fprintf(stdout, "%s\n", str);

    get_confirm_yes_input(str);

    exit(0);
}


void get_confirm_yes_input(char *string)
{
    char str[128];
    //struct termios tios;

    //tcgetattr(STDIN_FILENO, &tios);

    fprintf(stderr, "%s ", string);

    fgets(str, sizeof(str), stdin);

    printf("strlen(str) = %d\n", strlen(str));

    if(strncmp("yes", str, 3))
    	fprintf(stderr, "type error\n");
    	
}

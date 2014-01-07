#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <crypt.h>

void login_auth(void)
{
	char inputname[32];
	char passwd[32];
	char *rc; 
	struct passwd *pw;
	char *result;

	while(1) //dead loop until input the right name and passwd
	{
		printf("login name: ");
		rc = fgets(inputname, sizeof(inputname), stdin);
		if(rc == NULL)
		{
			printf("\nError input, please again\n");
			continue;
		}

		if((rc = strchr(inputname, '\n')) != NULL)
		{
			//find the "\n", and replace it with '\0'
			*rc = '\0';
		}

		printf("login passwd: ");
		rc = fgets(passwd, sizeof(passwd), stdin);
		if(rc == NULL)
		{
			printf("\nError input, please again\n");
			continue;
		}

		if((rc = strchr(passwd, '\n')) != NULL)
		{
			//find the '\n', and replace it with '\0'
			*rc = '\0';
		}
		
		if((pw = getpwnam(inputname)) == NULL)
		{
			//printf("\getpwnam failed, please again\n");
			continue;
		}

		//result = crypt_r(passwd, pw->pw_passwd, (struct crypt_data *)NULL);
		result = crypt(passwd, pw->pw_passwd);
		printf("\nDebug: name: %s, passwd: %s, result: %s, pw_passwd: %s\n", inputname, passwd, result, pw->pw_passwd);
		if(strcmp(result, pw->pw_passwd) == 0)
		{	
			//get it
			printf("Authentication ok\n");
			break;
		}
		else
		{
			printf("Authentication failed, continue\n");
			continue;
		}
	}
}

void main(void)
{
	login_auth();

	return;
}

			

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR_LEN	100

int is_valid_char(char c, char spec_char)
{
	if(c == spec_char || isalpha(c)
		|| isdigit(c))
	{
		return 1;
	}
	
	return 0;
}

int is_alpha_or_num(char c)
{
	if(isalpha(c) || isdigit(c))
	{
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int i, len, first_flag = 0, end_flag = 0, middle_flag = 0, spec_flag = 1;
	char special_char = '*';
	char input[MAX_CHAR_LEN] = {0}; 
	char buff[MAX_CHAR_LEN] = {0};
	char target[MAX_CHAR_LEN] = {0};
	//fprintf(stdout, "Please input your chars:");
	fgets(input, MAX_CHAR_LEN, stdin);

	memcpy(buff, input, MAX_CHAR_LEN);
	len = strlen(buff);
	for(i=0; i<len; i++) //the last character is '\n',
	{
		if(buff[i] == '\n')
			break;

		#if 0
		if(!is_valid_char(buff[i], special_char))
		{
			//including invalid char, just return back
			printf("the character '%c' is not a valid character\n", buff[i]);
			return -1;
		}
		#endif

		if(is_alpha_or_num(buff[i]))
		{
			spec_flag = 0;
			if(middle_flag != 0)
			{
				end_flag = i;
				memcpy(target+middle_flag, buff+i, len-i);
				break;
			}
			else
			{
				first_flag = i;
			}
		}

		if(buff[i] == special_char)
		{
			if(first_flag != 0)
			{
				middle_flag = i;
				memcpy(target, buff, i);
				first_flag = 0; //reset the flag
			}
		}
	}

	//printf("you input is: %s", buff);
	if(middle_flag != 0 && end_flag != 0 && first_flag == 0)
		printf("%s", target);
	else if(spec_flag == 1)
		printf(" ");
	else
		printf("%s", buff);

	return 0;
}

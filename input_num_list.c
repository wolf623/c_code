/*
 * Input: A serilar of number lists, then save them into 
 * a array
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SIZE	3

int get_num_lists(char *lists)
{
	int slist[NUM_SIZE] = {-1, -1, -1};
	char *p = NULL, *t = NULL;
	int i = 0, size = 0;

	p = lists;

	/*validate Illegal characters*/
    while(*p)
    {
        if(!isdigit(*p) && *p != ',')
        {
            fprintf(stderr, "Error: There is an Illegal characters '%c' within pid-list.\n", *p);
            return -1;
        }
        
        p++;
    }
    
    p = lists;
    if(p[0] == ',' || p[strlen(p) - 1] == ',')
    {
        fprintf(stderr, "Error: Character ',' should not be at the beginning or at the end of slot-list\n");
        return -1;
    }
    
    while(p)
    {
        if(size >= NUM_SIZE)
        {
            break;
        }
        
        t = index(p, ',');
        if(t != NULL)
        {
            p[t - p] = 0;
        }
        
        for(i = 0; i < size; i++)
        {
            if(slist[i] == atoi(p))
            {
                break;
            }
        }
        
        if(i >= size)
        {
            slist[size++] = atoi(p);
        }
        
        if(t == NULL)
        {
            break;
        }
        p = t + 1;
    }

	for(i=0; i<NUM_SIZE; i++)
	{	
		printf("slist[%d]: %d\n", i, slist[i]);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	get_num_lists(argv[1]);
	return 0;
}



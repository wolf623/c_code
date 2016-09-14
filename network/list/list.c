/*
  * OID list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_OID_LEN 64
#define MIN(a, b) (((a)>(b))?(b):(a))

typedef struct _OID
{
	int length;
	unsigned int *oid_ptr;
}OID;

typedef unsigned long oid;

typedef struct _oid_data_t
{
	oid oidname[MAX_OID_LEN];
	size_t oidlen;
	int priority;
	int val;
	struct _oid_data_t *next;
}oid_data_t;

typedef struct _oid_ctl_t
{
	int cnt; 
	oid_data_t *regedit; //all regedit OID
}oid_ctl_t;

//global 
static oid_ctl_t g_ctl_data = {0};

//return value: 0: macth, 1: not match
static int oid_compare(oid *o1, size_t o1_len, oid *o2, size_t o2_len, int *flag)
{
	int i = 0;
	*flag = 0;
	if(o1 == NULL || o2 == NULL)
		return -2;

	for(i=0; i<MIN(o1_len, o2_len); i++)
	{
		if(o1[i] < o2[i])
		{
			*flag = 1;
			return -1;
		}	
		else if(o1[i] > o2[i])
		{
			*flag = 1;
			return 1;
		}
	}

	if(o1_len < o2_len)
		return -1;
	else if(o1_len > o2_len)
		return 1;
	else
		return 0;

	return 0;
}

static char *print_oid(oid *olist, size_t len)
{	
	static char oidstr[256];	
	char oidptr[13];	
	int i;	

	memset(oidstr, 0, sizeof(oidstr));	
	memset(oidptr, 0, sizeof(oidptr));	

	for(i = 0; i < MIN(len, MAX_OID_LEN); i++)	
	{		
		sprintf(oidptr, ".%lu", olist[i]);		
		strcat(oidstr, oidptr);	
	}		

	return oidstr;
}


static int oid_regedit(oid_data_t *p_reg)
{
	if(p_reg == NULL)
		return -1;

	//printf("oid: %s\n", print_oid(p_reg->oidname, p_reg->oidlen));
	oid_data_t *p_oid, *prev = NULL;
	int cmp = 0, flag = -1;

	p_reg->next = NULL;
	if(g_ctl_data.regedit == NULL)
	{
		g_ctl_data.regedit = p_reg;
		g_ctl_data.regedit->next = NULL;
		//printf("<<<oid: %s\n", print_oid(g_ctl_data.regedit->oidname, g_ctl_data.regedit->oidlen));
		return 0;
	}

	for(p_oid=g_ctl_data.regedit; p_oid!=NULL; p_oid=p_oid->next)
	{
		cmp = oid_compare(p_oid->oidname, p_oid->oidlen, p_reg->oidname, p_reg->oidlen, &flag);
		if(cmp == 0)
		{
			//sam oid, replace it
			//if(p_reg->priority == -1 || p_reg->priority > p_oid->priority)
			{
				p_reg->next = p_oid->next;
				if(prev)
				{
					prev->next = p_reg;
				}
				else
				{
					g_ctl_data.regedit = p_reg;
				}	
				free(p_oid); //???
				return 0;
			}
		}
		else if(cmp < 0)
		{
			//printf("%s(): do nothing?\n", __FUNCTION__);
			;
		}
		else
		{
			if(flag == 0)
			{
				//replace old one with the new one
				p_reg->next = p_oid->next;
				if(prev)
				{
					prev->next = p_reg;
				}
				else
				{
					g_ctl_data.regedit = p_reg;
				}	
				free(p_oid);
				return 0;
			}
			else
			{
				//insert befor old one
				p_reg->next = p_oid;
				if(prev)
				{
					prev->next = p_reg;
				}
				else
				{
					g_ctl_data.regedit = p_reg;
				}
				return 0;
			}
		}

		prev = p_oid;
	}

	if(prev)
	{
		prev->next = p_reg;
	}
}

static void oid_insert(oid *oidlist, size_t len)
{
	static oid_data_t oiddata;
	memset(&oiddata, 0, sizeof(oiddata));

	memcpy(oiddata.oidname, oidlist, MAX_OID_LEN);
	oiddata.oidlen = len;
	//printf(">>>oid: %s\n", print_oid(oiddata.oidname, oiddata.oidlen));
	oid_regedit(&oiddata);
}

static int oid_unregedit(oid_data_t *p_unreg)
{
	if(p_unreg == NULL)
		return -1;

	int cmp = 0, flag = -1;
	oid_data_t *p_oid = NULL;
	oid_data_t *prev = NULL;

	for(p_oid = g_ctl_data.regedit; p_oid!=NULL; p_oid=p_oid->next)
	{
		cmp = oid_compare(p_oid->oidname, p_oid->oidlen, p_unreg->oidname, p_unreg->oidlen, &flag);
		if(cmp == 0)
		{
			//find the current oid, release it
			if(prev)
			{
				prev->next = p_oid->next;
				free(p_oid);
				return 0;
			}
			else
			{
				oid_data_t *p = g_ctl_data.regedit;
				g_ctl_data.regedit = g_ctl_data.regedit->next;
				free(p);
				//continue;
			}
		}
		else if(cmp < 0)
		{
			printf("%s(): do nothing?\n", __FUNCTION__);
		}
		else 
		{
			/*1.3.6.1.4, unregedit oid: 1.3.6.1 */
			if(flag == 0)
			{
				if(prev)
				{
					prev->next = p_oid->next;
					free(p_oid);
					continue;
				}
				else
				{
					oid_data_t *p = g_ctl_data.regedit;
					g_ctl_data.regedit = g_ctl_data.regedit->next;
					free(p);
					continue;
				}
			}
		}

		prev = p_oid;
	}

	return 0;
}

static void oid_data_print()
{
	if(g_ctl_data.regedit == NULL)
		return;

	oid_data_t *p_oid = NULL;
	for(p_oid=g_ctl_data.regedit; p_oid!=NULL; p_oid=p_oid->next)
	{
		printf("OID: %s\n", print_oid(p_oid->oidname, p_oid->oidlen));
	}
}

int main(int argc, char *argv[])
{
	oid_data_t *p_data = NULL;
	oid_data_t *p_data2 = NULL;
	int len;
	
	#if 1
	unsigned long oid_data1[] = {1, 3, 4, 5, 7, 23};
	len = sizeof(oid_data1)/sizeof(oid_data1[0]);	
	if((p_data = malloc(sizeof(oid_data_t))) == NULL)
		return -1;
	
	memcpy(p_data->oidname, oid_data1, MAX_OID_LEN);
	p_data->oidlen = len;
	oid_regedit(p_data);
	#endif
	
	#if 1
	unsigned long oid_data2[] = {1, 3, 4, 1};
	len = sizeof(oid_data2)/sizeof(oid_data2[0]);	
	if((p_data2 = malloc(sizeof(oid_data_t))) == NULL)
		return -1;
	
	memcpy(p_data2->oidname, oid_data2, MAX_OID_LEN);
	p_data2->oidlen = len;
	oid_regedit(p_data2);
	#endif
	
	oid_data_print();

	oid_unregedit(p_data2);
	oid_data_print();
	
	return 0;
}


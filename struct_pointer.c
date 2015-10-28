#include <stdio.h>

typedef struct _data_t
{
	int size;
	void *p_data;
}data_t;

#define DATA_SET(da, val)	(da).size = sizeof(val); (da).p_data = &(val)
#define DATA_PSET(da, p_val) (da).size = sizeof(*(p_val)); (da).p_data = (p_val);

#define STRING	"Hello Wolf"

void str_checkin(data_t *data)
{
	if(strcmp(data->p_data, STRING) == 0)
		printf("Get it\n");
}

void checkin(const char *str)
{	
	data_t mydata;

	//if not use the (void *) to chang the str, then gcc will give a warining
	DATA_PSET(mydata, (void *)str);
	str_checkin(&mydata);
}

int main(int argc, char *argv[])
{
	checkin(STRING);

	return 0;
}

#ifndef _SHMDATA_H_
#define _SHMDATA_H_

#define TEXT_LEN 	128
typedef struct _shmdata_t
{
	int flag; //not zero, can read, zero: can write
	char text[TEXT_LEN+1];
}shmdata_t;

#endif


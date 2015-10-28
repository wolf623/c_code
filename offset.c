#include <stdio.h>
#include <stdlib.h>

#define OFFSET(a, b) ((int)b - (int)a)

typedef struct video_cfg_t
{
   int a;
   short b;
   char c;
}video_cfg;

int main(void)
{
    static video_cfg *p = NULL;

    int offset =  OFFSET(p, &p->c);   

    printf("offset = %d\n", offset);

    printf("sizeof(video_cfg) = %d\n", sizeof(video_cfg));
    printf("(int)(&p->a) = %d\n", (int)(&p->a));
    printf("(int)(&p->b) = %d\n", (int)(&p->b));
    printf("(int)(&p->c) = %d\n", (int)(&p->c));
    printf("(int)p = %d\n", (int)p);

    exit(0);
}



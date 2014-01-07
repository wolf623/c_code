#include "double_list.h"

int main(void)
{
	plist_t list;
	list = (plist_t)malloc(sizeof(sizeof(list)));
	if(list == NULL)
	{	
		printf("malloc failed\n");
		return -1;
	}

	initList(list);
	insertNodeNext(list, 23);
	insertNodeNext(list, 38);
	insertNodePrev(list, 87);
	printList(list);

	getElem(list, 5, NULL);
	deleteElem(list, 38);
	printList(list);

	//destroyList(&list);	
	//isEmptyList(&list);
	return 0;
}

#include "dlist.h"

int main(void)
{
 	createList(23);

	insertListAtFirst(38);
	//insertListAtFirst(86);
	insertListAtLast(45);

	printList();

	deleteFirstList();
	deleteLastList();

	printList();
	isEmpty();		
	
	//deleteList(23);
	
	//printList();

	//searchList(38);

	return 0;
}


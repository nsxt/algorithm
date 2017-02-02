// SimpleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simple_linked_list.h"

template SimpleLinkedList<int>;

void dump_list_int(const SimpleLinkedList<int>& list) 
{
	POS pos = list.get_head_position();
	while (pos) {
		printf("%d ", list.get_next(pos));
	}
	printf("\n");
}

int main()
{
	SimpleLinkedList<int> list;

	try {
		list.get_head();

	} catch (SimpleLinkedList<int>::Exception e) {
		if (e == SimpleLinkedList<int>::INVALID_POS) {
			printf("catched, Invalid Pointer %d\n", e);
		}
		else if (e == SimpleLinkedList<int>::EMPTY_LIST) {
			printf("catched, Empty List %d\n", e);
		}
	}

	list.add_head(3);
	list.add_head(2);
	list.add_head(1);

	dump_list_int(list);

	POS pos = list.find(3);
	printf("find index 3 is %d \n", list.get_at(pos));

    return 0;
}


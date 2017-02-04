// SimpleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "simple_linked_list.h"
#include <iostream>

template SimpleLinkedList<int>;

void dump_list_int(SimpleLinkedList<int>& list) 
{
	SimpleLinkedList<int>::iterator it = list.begin();

	while (it) {		
		std::cout << list.at(it) << " " << std::endl;
		it = list.next(it);
	}

	std::cout << std::endl;
}

int main()
{
	SimpleLinkedList<int> list;

	try {
		std::cout << "Rise Exception test." << std::endl;
		list.front();

	} catch (SimpleLinkedList<int>::Exception e) {
		if (e == SimpleLinkedList<int>::INVALID_POS) {			
			std::cout << "catched, Invalid Pointer " << e << std::endl;
		}
		else if (e == SimpleLinkedList<int>::EMPTY_LIST) {			
			std::cout << "catched, Empty List " << e << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "Insert three elements as front." << std::endl;
	list.push_front(3);
	list.push_front(2);
	list.push_front(1);
	dump_list_int(list);

	std::cout << "Remove one element as front." << std::endl;
	list.pop_front();
	dump_list_int(list);

    return 0;
}


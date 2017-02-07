// DoubleLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "double_linked_list.h"

template DoubleLinkedList<int>;

void print_list(DoubleLinkedList<int>& list)
{
	DoubleLinkedList<int>::iterator it = list.begin();
	while (it) {
		std::cout << list.at(it) << " ";
		it = list.next(it);
	}

	std::cout << "\n" << std::endl;
}

int main()
{
	DoubleLinkedList<int> list;

	std::cout << "[ Double Linked List Test ] \n" << std::endl;

	try {
		std::cout << "Rise Exception test." << std::endl;
		list.front();

	}
	catch (DoubleLinkedList<int>::Exception e) {
		if (e == DoubleLinkedList<int>::INVALID_POS) {
			std::cout << "[EXCEPTION] catched, Invalid Pointer " << e << std::endl;
		}
		else if (e == DoubleLinkedList<int>::EMPTY_LIST) {
			std::cout << "[EXCEPTION] catched, Empty List " << e << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "Add three element at the front.." << std::endl;
	list.push_front(3);
	list.push_front(2);
	list.push_front(1);
	print_list(list);

	std::cout << "Removes the first element in the list.." << std::endl;
	list.pop_front();
	print_list(list);

	std::cout << "Add three elements at the back.." << std::endl;
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);
	print_list(list);

	std::cout << "Removes the last element in the list.." << std::endl;
	list.pop_back();
	print_list(list);

    return 0;
}


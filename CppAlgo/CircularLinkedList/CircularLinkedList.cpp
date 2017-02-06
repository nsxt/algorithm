// CircularLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "circular_linked_list.h"
#include <iostream>

template CircularLinkedList<char>;

void dump_list(CircularLinkedList<char>& list)
{
	CircularLinkedList<char>::iterator it = list.begin();
	int n = list.size();

	std::cout << "-> ";
	while (n) {
		std::cout << list.at(it) << " ";
		it = list.next(it);
		n--;
	}

	std::cout << std::endl;
}

/*
 Solve the Joseph's solution, Node numbers are 'n' and Step is 'm'
 */
void josephus(CircularLinkedList<char>& list, int m)
{
	CircularLinkedList<char>::iterator it = list.begin();
	CircularLinkedList<char>::iterator it_prev = nullptr;
		
	int i = 0;	
	std::cout << "-> ";

	while (!list.empty()) {
		if ((i % m) == 0) {
			std::cout << list.at(it) << " ";

			if (list.is_front(it)) {
				list.pop_front();
				it = list.begin();
				i++;
				continue;

			} else {
				list.erase(it_prev);
				it = it_prev;
			}

		} else {
			it_prev = it;
		}

		if (!list.empty()) {
			it = list.next(it);
		}

		i++;
	}

	std::cout << std::endl;
}

int main()
{
	CircularLinkedList<char> list;

	try {
		std::cout << "Rise Exception test." << std::endl;
		list.front();

	}
	catch (CircularLinkedList<char>::Exception e) {
		if (e == CircularLinkedList<char>::INVALID_POS) {
			std::cout << "catched, Invalid Pointer " << e << std::endl;
		}
		else if (e == CircularLinkedList<char>::EMPTY_LIST) {
			std::cout << "catched, Empty List " << e << std::endl;
		}
	}
	std::cout << std::endl;
	
	std::cout << "Insert ten elements as front." << std::endl;	
	list.push_front('J');
	list.push_front('I');
	list.push_front('H');
	list.push_front('G');
	list.push_front('F');
	list.push_front('E');
	list.push_front('D');
	list.push_front('C');
	list.push_front('B');
	list.push_front('A');
	dump_list(list);
	std::cout << std::endl;	

	//std::cout << "Remove one element as front." << std::endl;
	//list.pop_front();
	//dump_list(list);
	//std::cout << std::endl;
	
	// Circular Linked List 테스트는 Joseph's solution (요셉의문제) 사용
	std::cout << "Josephus solution...." << std::endl;
	try {
		josephus(list, 4);
	}
	catch (CircularLinkedList<char>::Exception e) {
		if (e == CircularLinkedList<char>::INVALID_POS) {
			std::cout << "catched, Invalid Pointer and Position " << e << std::endl;
		}
		else if (e == CircularLinkedList<char>::EMPTY_LIST) {
			std::cout << "catched, Empty List " << e << std::endl;
		}
	}
	std::cout << std::endl;

    return 0;
}


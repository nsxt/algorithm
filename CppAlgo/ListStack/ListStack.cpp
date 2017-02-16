// ListStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "list_stack.h"

template ListStack<int>;

void print_stack(ListStack<int>& stack)
{
	while (!stack.empty()) {
		std::cout << stack.pop() << " ";		
	}

	std::cout << "\n" << std::endl;
}

int main()
{
	ListStack<int> stack;

	std::cout << "[ List Stack Test ]\n" << std::endl;
	try {
		std::cout << "Rise Exception test.." << std::endl;
		stack.pop();
	}
	catch (ListStack<int>::Exception e) {
		if (e == ListStack<int>::STACK_EMPTY) {
			std::cout << "[EXCEPTION] catched, Empty stack " << e << std::endl;
		}
		else if (e == ListStack<int>::STACK_OVERFLOW) {
			std::cout << "[EXCEPTION] catched, Stack overflow " << e << std::endl;
		}
		else if (e == ListStack<int>::STACK_UNDERFLOW) {
			std::cout << "[EXCEPTION] catched, Stack underflow " << e << std::endl;
		}
	}
	catch (...) {
		std::cout << "\n" << "[EXCEPTION] catched, Unknown exception " << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Inserts five elements at the top of stack.." << std::endl;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);
	print_stack(stack);

	std::cout << "Stack size is " << stack.size() << " after all pop action..\n" << std::endl;

	return 0;
}



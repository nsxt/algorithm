// ArrayStack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "array_stack.h"

template ArrayStack<int, 10>;
typedef ArrayStack<int, 10> ArrayStackType;

void print_stack(ArrayStackType& stack)
{
	while (!stack.empty()) {
		std::cout << stack.top() << " ";
		stack.pop();
	}

	std::cout << "\n" << std::endl;
}

int main()
{
	ArrayStackType stack;

	std::cout << "[ Array Stack Test ]\n" << std::endl;
	try {
		std::cout << "Rise Exception test.." << std::endl;
		stack.pop();
	}
	catch (ArrayStackType::Exception e) {
		if (e == ArrayStackType::STACK_EMPTY) {
			std::cout << "[EXCEPTION] catched, Empty stack " << e << std::endl;
		}
		else if (e == ArrayStackType::STACK_OVERFLOW) {
			std::cout << "[EXCEPTION] catched, Stack overflow " << e << std::endl;
		}
		else if (e == ArrayStackType::STACK_UNDERFLOW) {
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


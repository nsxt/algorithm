// ListQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "list_queue.h"

template ListQueue<int>;
typedef ListQueue<int> ListQueueT;

void print_queue(ListQueueT& queue)
{
	while (!queue.empty()) {
		std::cout << queue.front() << " ";
		queue.pop();
	}

	std::cout << "\n" << std::endl;
}

int main()
{
	ListQueueT queue;

	std::cout << "[ List Queue Test ]\n" << std::endl;
	try {
		std::cout << "Rise Exception test.." << std::endl;
		queue.pop();
	}
	catch (ListQueueT::Exception e) {
		if (e == ListQueueT::QUEUE_EMPTY) {
			std::cout << "[EXCEPTION] catched, Empty stack " << e << std::endl;
		}
		else if (e == ListQueueT::QUEUE_OVERFLOW) {
			std::cout << "[EXCEPTION] catched, Queue overflow " << e << std::endl;
		}
		else if (e == ListQueueT::QUEUE_UNDERFLOW) {
			std::cout << "[EXCEPTION] catched, Queue underflow " << e << std::endl;
		}
	}
	catch (...) {
		std::cout << "\n" << "[EXCEPTION] catched, Unknown exception " << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Inserts five elements at the end of queue.." << std::endl;
	queue.push(1);
	queue.push(2);
	queue.push(3);
	queue.push(4);
	queue.push(5);
	print_queue(queue);

	std::cout << "Queue size is " << queue.size() << " after all pop action..\n" << std::endl;

	return 0;
}


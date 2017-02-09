// CircularArrayQueue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "circular_array_queue.h"

template CircularArrayQueue<int, 5>;
typedef CircularArrayQueue<int, 5> CircularArrayQueueT;

void print_queue(CircularArrayQueueT& queue)
{
	while (!queue.empty()) {
		std::cout << queue.front() << " ";
		queue.pop();
	}

	std::cout << "\n" << std::endl;
}

int main()
{
	CircularArrayQueueT queue;

	std::cout << "[ Circular Array Queue Test ]\n" << std::endl;
	try {
		std::cout << "Rise Exception test.." << std::endl;
		queue.pop();
	}
	catch (CircularArrayQueueT::Exception e) {
		if (e == CircularArrayQueueT::QUEUE_EMPTY) {
			std::cout << "[EXCEPTION] catched, Empty stack " << e << std::endl;
		}
		else if (e == CircularArrayQueueT::QUEUE_OVERFLOW) {
			std::cout << "[EXCEPTION] catched, Queue overflow " << e << std::endl;
		}
		else if (e == CircularArrayQueueT::QUEUE_UNDERFLOW) {
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

	try {
		std::cout << "\nRise Overflow Exception test.." << std::endl;
		queue.push(5);
	}
	catch (CircularArrayQueueT::Exception e) {
		if (e == CircularArrayQueueT::QUEUE_EMPTY) {
			std::cout << "[EXCEPTION] catched, Empty stack " << e << std::endl;
		}
		else if (e == CircularArrayQueueT::QUEUE_OVERFLOW) {
			std::cout << "[EXCEPTION] catched, Queue overflow " << e << std::endl;
		}
		else if (e == CircularArrayQueueT::QUEUE_UNDERFLOW) {
			std::cout << "[EXCEPTION] catched, Queue underflow " << e << std::endl;
		}
	}

	print_queue(queue);

	std::cout << "Queue size is " << queue.size() << " after all pop action..\n" << std::endl;

	return 0;
}


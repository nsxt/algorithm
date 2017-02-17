// DistCounting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "distribution_counting.h"

#define MAX_SIZE 16
size_t array_random[] = { 5, 5, 5, 4, 0, 2, 3, 3, 3, 5, 5, 5, 4, 2, 3, 2 };

void print_array(const char* title, size_t *a, int n)
{
	std::cout << "\n" << title << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::cout << "=========================================";
	print_array("Before Distribution Counting Sort ...", array_random, MAX_SIZE);
	dist_counting_sort(array_random, 16, 6);
	print_array("After Distribution Counting Sort ...", array_random, MAX_SIZE);
	std::cout << std::endl;

	return 0;
}


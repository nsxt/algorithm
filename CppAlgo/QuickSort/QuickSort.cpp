// QuickSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "quick_sort.h"

int array_random[] = { 1, 2, 3 };

void print_array(const char* title, int *a, int n)
{
	std::cout << "\n" << title << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{

	print_array("Before Insertion Sort...", array_random, 3);
	quick_sort<int>(array_random, 3);
	print_array("After Insertion Sort...", array_random, 3);

	std::cout << std::endl;

	return 0;
}

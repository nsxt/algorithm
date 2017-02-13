// InsertionSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "insertion_sort.h"

int array_random[] = { 5, 4, 3, 2, 1 };

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

	print_array("Before Insertion Sort...", array_random, 5);
	insertion_sort<int>(array_random, 5);
	print_array("After Insertion Sort...", array_random, 5);

	std::cout << std::endl;

	return 0;
}
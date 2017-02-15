// QuickSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "quick_sort.h"

int array_random[] = { 5, 4, 3, 2, 1 };
int array_copy[5];


void copy_array(int s[], int d[], int n)
{
	memcpy(d, s, n * sizeof(int));
}

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
	/*
		Recursion Quick Sort
	*/
	copy_array(array_random, array_copy, 5);
	std::cout << "=========================================";
	print_array("Before Quick Sort by recursion version...", array_copy, 5);
	quick_sort<int>(array_copy, 5);
	print_array("After Quick Sort by recursion version...", array_copy, 5);
	std::cout << std::endl;

	/*
		ListStack Quick Sort
	*/
	copy_array(array_random, array_copy, 5);
	std::cout << "=========================================";
	print_array("Before Quick Sort by list stack version...", array_copy, 5);
	quick_sort_liststack<int>(array_copy, 5);
	print_array("After Quick Sort by list stack version...", array_copy, 5);
	std::cout << std::endl;

	/*
		ArrayStack Quick Sort
	*/
	copy_array(array_random, array_copy, 5);
	std::cout << "=========================================";
	print_array("Before Quick Sort by array stack version...", array_copy, 5);
	quick_sort_arraystack<int>(array_copy, 5);
	print_array("After Quick Sort by array stack version...", array_copy, 5);
	std::cout << std::endl;

	/*
		Random Quick Sort
	*/
	copy_array(array_random, array_copy, 5);
	std::cout << "=========================================";
	print_array("Before Quick Sort by random pivot version...", array_copy, 5);
	quick_sort_random<int>(array_copy, 5);
	print_array("After Quick Sort by random pivot version...", array_copy, 5);
	std::cout << std::endl;

	return 0;
}

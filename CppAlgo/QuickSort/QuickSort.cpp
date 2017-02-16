// QuickSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "quick_sort.h"

#define MAX_SIZE 13

int array_random[] = { 1, 1, 8, 7, 6, 5, 4, 3, 2, 1, 10, 11, 9 };
//int array_random[] = { 5, 4, 3, 2, 1 };
int array_copy[MAX_SIZE];


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
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Quick Sort by recursion version...", array_copy, MAX_SIZE);
	quick_sort<int>(array_copy, MAX_SIZE);
	print_array("After Quick Sort by recursion version...", array_copy, MAX_SIZE);
	std::cout << std::endl;

	/*
		ListStack Quick Sort
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Quick Sort by list stack version...", array_copy, MAX_SIZE);
	quick_sort_liststack<int>(array_copy, MAX_SIZE);
	print_array("After Quick Sort by list stack version...", array_copy, MAX_SIZE);
	std::cout << std::endl;

	/*
		ArrayStack Quick Sort
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Quick Sort by array stack version...", array_copy, MAX_SIZE);
	quick_sort_arraystack<int>(array_copy, MAX_SIZE);
	print_array("After Quick Sort by array stack version...", array_copy, MAX_SIZE);
	std::cout << std::endl;

	/*
		Random Quick Sort
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Quick Sort by random pivot version...", array_copy, MAX_SIZE);
	quick_sort_random<int>(array_copy, MAX_SIZE);
	print_array("After Quick Sort by random pivot version...", array_copy, MAX_SIZE);
	std::cout << std::endl;

	/*
		Median Quick Sort
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Quick Sort by median pivot version...", array_copy, MAX_SIZE);
	quick_sort_median<int>(array_copy, MAX_SIZE);
	print_array("After Quick Sort by median pivot version...", array_copy, MAX_SIZE);
	std::cout << std::endl;
	
	/*
		Insertion and Median Combination Quick Sort
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Quick Sort by insertion and median version...", array_copy, MAX_SIZE);
	quick_sort_sub<int>(array_copy, MAX_SIZE);
	print_array("After Quick Sort by insertion and median version...", array_copy, MAX_SIZE);
	std::cout << std::endl;

	return 0;
}

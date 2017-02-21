// HeapSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "heap_sort.h"

#define MAX_SIZE 13

int array_random[] = { 1, 1, 8, 7, 6, 5, 4, 3, 2, 1, 10, 11, 9 };
int array_copy[MAX_SIZE];

template ArrayHeap<int>;

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
	ArrayHeap<int> heap(array_copy, MAX_SIZE);
	
	/*
		Heap Sort by Top-Down build.
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Heap Sort by Top-Down build version...", array_copy, MAX_SIZE);

	heap.sort();

	print_array("After Heap Sort by Top-Down build version...", array_copy, MAX_SIZE);
	std::cout << std::endl;


	/*
		Heap Sort by Bottom-Up build.
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Heap Sort by Bottom-Up build version...", array_copy, MAX_SIZE);	
	
	heap.sort_up(array_copy, MAX_SIZE);

	print_array("After Heap Sort by Bottom-Up build version...", array_copy, MAX_SIZE);
	std::cout << std::endl;

	return 0;
}


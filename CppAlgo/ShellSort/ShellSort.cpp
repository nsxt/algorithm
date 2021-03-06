// ShellSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "shell_sort.h"

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
		Shell Sort
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Shell Sort ...", array_copy, MAX_SIZE);
	shell_sort<int>(array_copy, MAX_SIZE);
	print_array("After Shell ...", array_copy, MAX_SIZE);
	std::cout << std::endl;

	/*
		3*h+1 Sequence Shell Sort
	*/
	copy_array(array_random, array_copy, MAX_SIZE);
	std::cout << "=========================================";
	print_array("Before Shell sort by 3*h+1 sequence ...", array_copy, MAX_SIZE);
	shell_sort_3h<int>(array_copy, MAX_SIZE);
	print_array("After Shell sort by 3*h+1 sequence ...", array_copy, MAX_SIZE);
	std::cout << std::endl;

	return 0;
}


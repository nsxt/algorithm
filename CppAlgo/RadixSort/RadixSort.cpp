// RadixSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <bitset>
#include "radix_sort.h"

#define MAX_SIZE 5
unsigned long array_random[] = { 5, 4, 3, 2, 1 };

void bit_shift_test()
{
	char x = 1;
	std::cout << "x = " << std::bitset<8>(x) << " No shift " << std::endl;
	x = x << 1;
	std::cout << "x = " << std::bitset<8>(x) << " << 1 left shift " << std::endl;
	x = x >> 1;
	std::cout << "x = " << std::bitset<8>(x) << " >> 1 right shift " << std::endl;

	std::cout << std::endl;

	unsigned char y = 0xff;
	std::cout << "y = " << std::bitset<8>(y) << " No shift " << std::endl;
	y = y << 1;
	std::cout << "y = " << std::bitset<8>(y) << " << 1 left shift " << std::endl;
	y = y >> 1;
	std::cout << "y = " << std::bitset<8>(y) << " >> 1 right shift " << std::endl;

	std::cout << std::endl;

	char z = 0xff;
	std::cout << "z = " << std::bitset<8>(z) << " No shift " << std::endl;
	z = z << 1;
	std::cout << "z = " << std::bitset<8>(z) << " << 1 left shift " << std::endl;
	z = z >> 1;
	std::cout << "z = " << std::bitset<8>(z) << " >> 1 right shift " << std::endl;
}

void print_array(const char* title, unsigned long *a, int n)
{
	std::cout << "\n" << title << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << a[i] << " "<< std::bitset<4>(a[i]) << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < n; i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{	
	std::cout << "=========================================";
	print_array("Before Radix Exchange Sort by recursion version...", array_random, MAX_SIZE);
	radix_exchange_sort(array_random, MAX_SIZE);
	print_array("After Radix Exchange Sort by recursion version...", array_random, MAX_SIZE);
	std::cout << std::endl;

	return 0;
}


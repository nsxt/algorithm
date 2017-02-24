// InterpolationSearchMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <chrono>
#include <string>
#include "interpolation_bin_array_map.h"

int main()
{
	std::cout << "\n### Interpolation Sequential Search Map Test.\n" << std::endl;

	InterpolationSeqMap map(100);
	map.insert(5);
	map.insert(3);
	map.insert(2);
	map.insert(1);
	map.insert(3);
	map.insert(6);
	map.insert(3);

	int key;
	int value;

	/*
	Find Test
	*/
	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Find Test **\n" << std::endl;

	key = 1;
	if (map.find(key, value))
		std::printf("\tTest(Find) id=%d name=%d\n", key, value);
	else
		std::printf("\tTest(Find) Error \n");


	/*
	Find First / Find Next Test
	*/
	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Find First / Find Next Test **\n" << std::endl;

	key = 3;
	InterpolationSeqMap::MapPos pos;
	if (map.find_first(key, value, pos)) {
		do {
			std::printf("\tTest(FindFirst) id=%d name=%d\n", key, value);
		} while (map.find_next(value, pos));
	}
	else {
		std::printf("\tTest(FindFirst) Error\n");
	}


	/*
	Remove Test
	*/

	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Remove Test **\n" << std::endl;

	key = 1;
	if (map.remove(key))
		std::printf("\tTest(Remove) id=%d Success\n", key);
	else
		std::printf("\tTest(Remove) id=%d Failed\n", key);

	if (map.find(key, value))
		std::printf("\tTest(Find) id=%d name=%d\n", key, value);
	else
		std::printf("\tTest(Find) id=%d Error \n", key);

	std::cout << "\n=========================================" << std::endl;

	return 0;
}


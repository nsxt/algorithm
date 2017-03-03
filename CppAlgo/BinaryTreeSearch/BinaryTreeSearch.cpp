// BinaryTreeSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <chrono>
#include <string>
#include "binary_tree_map.h"

template BinaryTreeMap<int>;

int main()
{
	std::cout << "\n### Binary Tree Search Map Test.\n" << std::endl;

	BinaryTreeMap<int> map;
	map.insert(20);
	map.insert(10);
	map.insert(30);
	map.insert(5);
	map.insert(15);
	map.insert(25);
	map.insert(35);

	int key;
	int value;

	/*
		Find Test
	*/
	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Find Test **\n" << std::endl;

	key = 35;
	if (map.find(key, value))
		std::printf("\tTest(Find) key=%d found_value=%d\n", key, value);
	else
		std::printf("\tTest(Find) Error \n");

	/*
		Sort Test
	*/
	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Sort Test **\n" << std::endl;

	int a[7];
	std::memset(a, 0, sizeof(int) * 7);
	map.sort(a, 7);
	
	std::cout << "\tSort Result...  ";
	for (int i = 0; i < 7; i++) {
		std::cout << a[i] << " ";
	}

	/*
		Remove Test
	*/
	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Remove Test **\n" << std::endl;

	key = 15;
	if (map.remove(key))
		std::printf("\tTest(Remove) key=%d found and remove success.", key);
	else
		std::printf("\tTest(Remove) Error - key=%d \n", key);

	/*
		Re-Sort and Insert Test
	*/
	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Re-Sort and Insert Test **\n" << std::endl;

	map.insert(1);
	std::printf("\tInserted key=%d \n", 1);

	std::memset(a, 0, sizeof(int) * 7);
	map.sort(a, 7);

	std::cout << "\tSort Result...  ";
	for (int i = 0; i < 7; i++) {
		std::cout << a[i] << " ";
	}

	std::cout << "\n\n";

	return 0;
}


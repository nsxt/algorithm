// ListSeqMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <chrono>
#include <string>
#include "list_seq_map.h"

struct Person {
	int id_;
	std::string name_;

	Person() : id_(0) {}
	Person(int id, const std::string& name) : id_(id), name_(name) {}
	Person(const Person& other) { id_ = other.id_; name_ = other.name_; }

	Person operator = (const Person& other) { id_ = other.id_; name_ = other.name_; return *this; }
	bool operator == (const Person& other) const { return id_ == other.id_; }
	bool operator > (const Person& other) const { return id_ > other.id_; }
	unsigned long operator >> (const unsigned long i) const { return id_ >> i; }
};

template ListSeqMap<Person>;

int main()
{
	std::cout << "\n### List Sequential Search Map Test.\n" << std::endl;

	ListSeqMap<Person> map;
	map.insert(Person(5, "Jake"));
	map.insert(Person(3, "Devil"));
	map.insert(Person(2, "Slash"));
	map.insert(Person(1, "Newmania"));
	map.insert(Person(3, "Franken"));
	map.insert(Person(6, "Stone"));
	map.insert(Person(3, "kosh"));

	Person key;
	Person value;

	/*
	Find Test
	*/
	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Find Test **\n" << std::endl;

	key.id_ = 1;
	if (map.find(key, value))
		std::printf("\tTest(Find) id=%d name=%s\n", key.id_, value.name_.c_str());
	else
		std::printf("\tTest(Find) Error \n");


	/*
	Find First / Find Next Test
	*/
	std::cout << "\n=========================================" << std::endl;
	std::cout << "** Find First / Find Next Test **\n" << std::endl;

	key.id_ = 3;
	ListSeqMap<Person>::MapPos pos;
	if (map.find_first(key, value, pos)) {
		do {
			std::printf("\tTest(FindFirst) id=%d name=%s\n", key.id_, value.name_.c_str());
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

	key.id_ = 1;
	if (map.remove(key))
		std::printf("\tTest(Remove) id=%d Success\n", key.id_);
	else
		std::printf("\tTest(Remove) id=%d Failed\n", key.id_);

	if (map.find(key, value))
		std::printf("\tTest(Find) id=%d name=%s\n", key.id_, value.name_.c_str());
	else
		std::printf("\tTest(Find) id=%d Error \n", key.id_);

	std::cout << "\n=========================================" << std::endl;

    return 0;
}


// ArraySeqMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <string>
#include "array_seq_map.h"

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


template ArraySeqMap<Person>;

int main()
{
	ArraySeqMap<Person> map(100);
	map.insert(Person(5, "Jake"));
	map.insert(Person(3, "Devil"));
	map.insert(Person(2, "Slash"));
	map.insert(Person(1, "Newmania"));
	map.insert(Person(3, "Franken"));
	map.insert(Person(6, "Stone"));
	map.insert(Person(3, "kosh"));
	
	return 0;
}


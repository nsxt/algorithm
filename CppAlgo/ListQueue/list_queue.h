#pragma once
#include "../DoubleLinkedList/double_linked_list.h"

/*
	List Queue using the 'DoubleLinkedList'
*/

template<class T> class ListQueue
{
public:
	enum Exception { QUEUE_OVERFLOW, QUEUE_UNDERFLOW, QUEUE_EMPTY };

public:
	ListQueue() {}
	~ListQueue() {}

public:
	/**
		Element access
	**/

	T front() const
	{
		try {
			return dlist_.front();
		}
		catch (DoubleLinkedList<T>::Exception) {
			throw QUEUE_EMPTY;
		}
	}

	T back() const
	{
		try {
			return dlist_.back();
		}
		catch (DoubleLinkedList<T>::Exception) {
			throw QUEUE_EMPTY;
		}
	}

		
	/**
		Modifires
	**/

	void push(const T& value)
	{
		try {
			dlist_.push_back(value);
		}
		catch (DoubleLinkedList<T>::Exception) {
			throw QUEUE_OVERFLOW;
		}
	}

	void pop()
	{
		try {
			dlist_.pop_front();
		}
		catch (DoubleLinkedList<T>::Exception) {
			throw QUEUE_UNDERFLOW;
		}
	}

	
	/**
		Capacity
	**/

	bool empty() const { return dlist_.empty(); }
	size_t size() const { return dlist_.size(); }

protected:
	DoubleLinkedList<T> dlist_;
};
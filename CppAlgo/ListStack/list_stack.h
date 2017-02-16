#pragma once

#include "../SimpleLinkedList/simple_linked_list.h"

/*
	List Stack using the 'SimpleLinkedList'
*/

template<class T> class ListStack 
{
public:
	enum Exception { STACK_OVERFLOW, STACK_UNDERFLOW, STACK_EMPTY };

public:
	ListStack() {}
	~ListStack() {}

public:
	/**
		Element access
	**/
	
	T top() const 
	{
		try {
			return slist_.front();
		}
		catch (SimpleLinkedList<T>::Exception) {
			throw STACK_EMPTY;
		}
	}
	

	/**
		Modifiers
	**/
	
	void push(const T& value) 
	{
		try {
			slist_.push_front(value);
		} 
		catch (SimpleLinkedList<T>::Exception) {
			throw STACK_OVERFLOW;
		}
	}

	T pop() 
	{
		try {
			return slist_.pop_front();
		} 
		catch (SimpleLinkedList<T>::Exception) {
			throw STACK_UNDERFLOW;
		}
	}


	/**
		Capacity
	**/

	bool empty() const { return slist_.empty(); }
	size_t size() const { return slist_.size(); }

protected:
	SimpleLinkedList<T> slist_;
};

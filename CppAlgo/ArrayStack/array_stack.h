#pragma once

/*
	Array Stack

:: 0 인덱스는 사용하지 않는다.

*/
template<class T> class ArrayStack
{
public:
	enum Exception { 
		STACK_OVERFLOW, STACK_UNDERFLOW, STACK_EMPTY, 
		MEMALLOC_FAILED, INVALID_STACK_SIZE 
	};

public:
	ArrayStack(const int size = 100) : top_(-1) 
	{
		if (size <= 0) {
			throw INVALID_STACK_SIZE;
		}

		elems = new T[size];
		if (elems == nullptr) {
			throw MEMALLOC_FAILED;
		}

		max_size_ = size;
	}

	~ArrayStack() 
	{
		delete[] elems;
	}

public:
	/**
		Element access
	**/

	T top() const 
	{
		if (empty()) {
			throw STACK_EMPTY;
		}

		return elems[top_];
	}


	/**
		Modifiers	
	**/

	void push(const T& value) 
	{
		if (top_ >= max_size_) {
			throw STACK_OVERFLOW;
		}

		elems[++top_] = value;
	}

	T pop() 
	{
		if (empty()) {
			throw STACK_UNDERFLOW;
		}

		return elems[top_--];
	}


	/**
		Capacity
	**/
	bool empty() const { return (top_ < 0); }
	size_t size() const { return (top_ + 1); }

protected:
	T* elems;
	int max_size_;
	int top_;
};
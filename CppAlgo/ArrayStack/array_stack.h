#pragma once

/*
	Array Stack

:: 0 인덱스는 사용하지 않는다.

*/
template<class T, size_t N> class ArrayStack
{
public:
	enum Exception { STACK_OVERFLOW, STACK_UNDERFLOW, STACK_EMPTY };

public:
	ArrayStack() : top_(0) {}
	~ArrayStack() {}

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

	void pop() 
	{
		if (empty()) {
			throw STACK_UNDERFLOW;
		}

		top_--;
	}


	/**
		Capacity
	**/
	bool empty() const { return (top_ <= 0); }
	size_t size() const { return top_; }

protected:
	T elems[N];
	const size_t max_size_ = N;
	size_t top_;
};
#pragma once

/*
	Circular Array Queue
*/

template<class T, size_t N> class CircularArrayQueue
{
public:
	enum Exception { QUEUE_OVERFLOW, QUEUE_UNDERFLOW, QUEUE_EMPTY };

public:
	CircularArrayQueue() : size_(0), rear_(0), front_(0) {};
	~CircularArrayQueue() {};
	
public:
	/** 
		Element access
	**/

	T front() const 
	{
		if (front_ == rear_) {
			throw QUEUE_EMPTY;
		}

		return elems_[front_];
	}

	T back() const 
	{
		if (front_ == rear_) {
			throw QUEUE_EMPTY;
		}

		size_t dec_rear = (rear_ + (max_size_ - 1)) % max_size_;

		return elems_[dec_rear];
	}
	
	
	/** 
		Modifires
	**/

	void push(const T& value) 
	{
		if (((rear_ + 1) % max_size_) == front_) {
			throw QUEUE_OVERFLOW;
		}

		elems_[rear_] = value;

		rear_ = (rear_ + 1) % max_size_;
		size_++;
	}

	void pop() 
	{
		if (front_ == rear_) {
			throw QUEUE_UNDERFLOW;
		}

		front_ = (front_ + 1) % max_size_;
		size_--;
	}


	/**
		Capacity
	**/

	bool empty() const { return (front_ == rear_); }
	size_t size() const { return size_; }

protected:
	T elems_[N];
	const size_t max_size_ = N;
	size_t size_;
	size_t rear_;
	size_t front_;
};
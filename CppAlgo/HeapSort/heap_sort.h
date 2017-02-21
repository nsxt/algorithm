#pragma once

/*
	Heap (Priority Queue)
*/
template<class T> class ArrayHeap
{
public:
	enum Exception { HEAP_OVERFLOW, HEAP_UNDERFLOW, HEAP_EMPTY, INVALID_HEAP };

public:
	ArrayHeap()
		: elems_(nullptr), elems_size_(-1), heap_len_(0) {}

	ArrayHeap(T a[], int n) 
		: elems_(a), elems_size_(n), heap_len_(0) {}

	~ArrayHeap() {}

public:
	/**
		Element access
	**/
	T top() const 
	{
		if (elems_size_ < 0) {
			throw HEAP_EMPTY;
		}

		return elems_[0];
	}


	/**
		Capacity
	**/
	bool empty() const { return (elems_size_ < 0); }
	int size() const { return heap_len_; }


	/**
		Modifiers
	**/
	void clear() noexcept
	{
		elems_ = nullptr;
		elems_size_ = -1;
		heap_len_ = 0;
	}

	T& at(int k) noexcept
	{
		return elems_[k - 1];
	}

	void insert(const T& value)
	{
		if (heap_len_ + 1 > elems_size_) {
			throw HEAP_OVERFLOW;
		}

		at(++heap_len_) = value;
		up_heap(heap_len_);
	}

	T extract()
	{
		if (heap_len_ < 0) {
			throw HEAP_UNDERFLOW;
		}
		
		T v = at(1);
		at(1) = at(heap_len_--);
		down_heap(1);
		return v;
	}

	void down_heap(int k) noexcept
	{
		int i;
		T v = at(k);
		
		while (k <= heap_len_ / 2) {	// Inner Node (N/2)

			i = k * 2;	// Left Child Node

			if (i < heap_len_ && at(i + 1) > at(i)) { // "i + 1" is Right Child Node
				i++;
			}

			if (v > at(i) || v == at(i)) {
				break;
			}

			at(k) = at(i);
			k = i;
		}

		at(k) = v;
	}

	void up_heap(int k) noexcept
	{
		T v = at(k);
		while (v > at(k / 2) && k > 1) {
			at(k) = at(k / 2);
			k /= 2;
		}
		at(k) = v;
	}


	/**
		Operations
	**/
	void sort()
	{
		int i;
		for (i = 1; i <= elems_size_; i++) {
			insert(at(i));
		}

		int n = elems_size_;
		while (n > 1) {
			at(n--) = extract();
		}
	}

	void sort_up(T a[], int n)
	{
		if (a == nullptr || n <= 0) {
			throw INVALID_HEAP;
		}

		elems_ = a;
		elems_size_ = n;
		heap_len_ = n;		

		// Iteration Inner Node (N/2)
		for (int k = n / 2; k >= 1; k--) {
			down_heap(k);
		}

		int j = n;
		while (j > 1) {
			at(j--) = extract();
		}
	}

protected:
	T* elems_;
	int elems_size_;
	int heap_len_;
};
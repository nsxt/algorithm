#pragma once

#include <cstring>
#include <cassert>

/*
	"Sequential Search" by using array.
*/
template<class T> class ArraySeqMap
{
public:
	struct MapPos {
		T key;
		long index;
	};

public:
	ArraySeqMap(int size = 100) 
	{
		elems_ = new T[size];
		assert(elems_);

		max_size_ = size;
		len_ = 0;
	}
	~ArraySeqMap() 
	{
		delete[] elems_;
	}

public:
	/**
		Capacity
	**/
	bool empty() 
	{
		return (len_ <= 0);
	}

	int size() 
	{
		return len_;
	}

	int max_size() 
	{
		return max_size_;
	}


	/**
		Modifiers
	**/
	void clear() 
	{
		std::memset(elems_, 0, sizeof(T) * max_size_);
		len_ = 0;
	}

	bool insert(const T& value) 
	{
		if (len_ + 1 > max_size_)
			return false;
		
		elems_[len_++] = value;

		return true;
	}

	bool remove(const T& key) 
	{
		MapPos pos;
		pos.index = 0;
		pos.key = key;

		if (!_find(pos))
			return false;

		remove_at(pos);

		return true;
	}

	void remove_at(const MapPos& pos) 
	{
		for (int i = pos.index + 1; i < len_; i++)
			elems_[i - 1] = elems_[i];

		len_--;
	}
	

	/**
		Lookup
	**/
	bool find(const T& key, T& found_value)
	{
		MapPos pos;
		pos.index = 0;
		pos.key = key;

		if (!_find(pos))
			return false;

		found_value = elems_[pos.index];

		return true;
	}
	
	bool find_first(const T& key, T& found_value, MapPos& found_pos) const
	{
		found_pos.index = 0;
		found_pos.key = key;

		if (!_find(found_pos))
			return false;

		found_value = elems_[found_pos.index];

		return true;
	}

	bool find_next(T& found_value, MapPos& found_pos) const
	{
		found_pos.index++;

		if (!_find(found_pos))
			return false;

		found_value = elems_[found_pos.index];

		return true;
	}

protected:
	virtual bool _find(MapPos& pos) const
	{
		if (pos.index >= len_)
			return false;

		bool found = false;
		int i = 0;

		for (i = pos.index; i < len_; i++) {
			if (elems_[i] == pos.key) {
				found = true;
				pos.index = i;
				break;
			}
		}

		if (!found)
			return false;
		
		return true;
	}

protected:
	T* elems_;
	long max_size_;
	long len_;
};

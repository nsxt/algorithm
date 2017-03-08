#pragma once

#include <cassert>
#include <cstring>

template<class T, class HASH> class HashMap
{
public:
	enum NodeStatus { EMPTY = 0, DELETED, AVAIL };

	struct MapPos {
		T key;
		long index;
	};

	struct Node {
		T data;
		NodeStatus status;
		Node() { status = EMPTY; }
	};

public:
	HashMap(const HASH& hash, int size = 100) 
	{
		hash_ = hash;

		elems_ = new Node[size];
		assert(elems_);

		size_ = size;
		len_ = 0;
	}

	~HashMap() 
	{
		delete[] elems_;
	}

public:
	/** 
		Capacity
	**/
	bool empty() const { return len_ <= 0; }
	long len() const { return len_; }
	long size() const { return size_; }


	/**
		Modifires
	**/
	void clear() 
	{
		for (int i = 0; i < size_; i++) {
			elems_[i].status = EMPTY;
		}

		len_ = 0;
	}

	bool insert(const T& value) 
	{
		int start = hash_.hash(value) % size_;
		int index = start;

		while (elems_[index].status == AVAIL) {
			index = (index + _next(value)) % size_;

			// Hash Bucket ²Ë Ã¡´ÂÁö?
			if (index == start)
				return false;
		}

		elems_[index].status = AVAIL;
		elems_[index].data = value;
		len_++;

		return true;
	}

	bool remove(const T& key) 
	{
		MapPos pos;
		pos.key = key;
		pos.index = 0;

		if (!_find(pos))
			return false;

		return remove_at(pos);
	}

	/**
		Lookup
	**/
	bool find(const T& key, T& value) const 
	{
		MapPos pos;
		pos.key = key;
		pos.index = 0;

		if (!_find(pos))
			return false;

		value = elems_[pos.index].data;

		return true;
	}

	bool find_first(const T& key, T& value, MapPos& pos) const 
	{
		pos.key = key;
		pos.index = 0;

		if (!_find(pos))
			return false;

		value = elems_[pos.index].data;

		return true;
	}

	bool find_next(T& value, MapPos& pos) const 
	{
		int start = (pos.index + _next(pos.key)) % size_;
		int index = start;

		while (elems_[index].status != EMPTY) {
			if (elems_[index].data == pos.key) {
				pos.index = index;
				value = elems_[index].data;
				return true;
			}

			index = (index + _next(pos.key)) % size_;

			// end of cluster
			if (index == start)
				return false;
		}

		return false;
	}

protected:
	bool _find(MapPos& pos) const 
	{
		int start = hash_.hash(pos.key) % size_;
		int index = start;

		while (elems_[index].status != EMPTY) {
			if (elems_[index].status == AVAIL && elems_[index].data == pos.key) {
				pos.index = index;
				return true;
			}

			index = (index + _next(pos.key)) % size_;
			if (index == start)
				return false;
		}

		return false;
	}

	int _next(const T& key) const { return 1; }

	bool remove_at(const MapPos& pos)
	{
		// Lazy Deletion
		if (len_ <= 0 || pos.index < 0 || pos.index >= size_)
			return false;

		if (elems_[pos.index].status != AVAIL)
			return false;

		elems_[pos.index].status = DELETED;
		len_--;

		return true;
	}

protected:
	Node* elems_;
	HASH hash_;
	long size_;
	long len_;

};


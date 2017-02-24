#pragma once
#include <cstring>
#include <cassert>
#include "../DoubleLinkedList/double_linked_list.h"

/* 
	"Sequential Search" by using double linked list.
*/
template<class T> class ListSeqMap
{
public:
	typedef typename DoubleLinkedList<T>::iterator it_t;

	struct MapPos {
		T key;
		it_t pos;
	};

public:
	ListSeqMap() {}
	~ListSeqMap() {}

public:
	
	/**
		Capacity
	**/

	bool empty() const { return list_.empty(); }
	long size() const { return list_.size(); }



	/**
		Modifiers
	**/

	void clear() 
	{ 
		list_.clear();
	}

	bool insert(const T& value)
	{
		list_.push_back(value);
		return true;
	}

	bool remove(const T& key)
	{
		MapPos pos;
		pos.pos = nullptr;
		pos.key = key;

		if (!_find(pos))
			return false;

		remove_at(pos);

		return true;
	}

	bool remove_at(const MapPos& pos)
	{
		bool result = true;

		try {
			list_.erase(pos.pos);
		}
		catch (DoubleLinkedList<T>::Exception) {
			return false;
		}

		return result;
	}



	/**
		Lookup
	**/

	bool find(const T& key, T& value) const
	{
		MapPos pos;
		pos.pos = nullptr;
		pos.key = key;

		if (!_find(pos))
			return false;

		value = list_.at(pos.pos);

		// MRU Àû¿ë ½Ã
		// list_.erase(pos.pos);
		// list_.push_front(value);

		return true;
	}

	bool find_first(const T& key, T& value, MapPos& pos) const
	{
		pos.pos = nullptr;
		pos.key = key;

		if (!_find(pos))
			return false;

		value = list_.at(pos.pos);

		return true;
	}

	bool find_next(T& value, MapPos& pos) const
	{
		try {
			pos.pos = list_.next(pos.pos);
			if (pos.pos == nullptr)
				return false;
		}
		catch (DoubleLinkedList<T>::Exception) {
			return false;
		}

		if (!_find(pos))
			return false;

		value = list_.at(pos.pos);

		return true;
	}

protected:
	virtual bool _find(MapPos& pos) const
	{
		pos.pos = list_.find(pos.key, pos.pos);

		if (pos.pos == nullptr)
			return false;

		return true;
	}

protected:
	DoubleLinkedList<T> list_;
};
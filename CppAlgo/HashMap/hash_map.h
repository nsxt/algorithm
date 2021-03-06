#pragma once

#include <cassert>
#include <cstring>

/*
	Hash Search Algorithm

	: 중복키가 허용되는 기본 해쉬 검색 알고리즘

- 알고리즘의 핵심적인 기능은 insert 수행 시 Hash Table 의 빈 Bucket 을
Hash Function 으로 결정하고 Hash 값이 동일할 경우 Cluster 로 그룹화 되어 관리된다.
Hash Table 에서 Cluster 가 발생 하는 것을 완전히 막을 수는 없으며, 가급적 분포도가 넓은
해쉬 값을 구하여 Bucket 을 지정하는것이 성늘 개선의 핵심이다.

*/

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

			// Hash Bucket 꽉 찼는지?
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


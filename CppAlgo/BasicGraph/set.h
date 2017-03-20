#pragma once

template<class T> class Set
{
public:
	struct Item {
		T elem;
		int parent;	// parent index
		int height;
	};

public:
	Set(int size = 100) 
	{
		elems_ = new Item[size];
		size_ = size;
		len_ = 0;
	}

	~Set()
	{
		delete[] elems_;
	}

public:
	T& get_item(int index) { return elems_[index].elem; }

	int get_parent(int index) { return elems_[index].parent; }

	int get_index(const T& t) const
	{
		for (int i = 0; i < len_; i++)
			if (elems_[i].elem == t)
				return i;

		return -1;
	}

	long add_set(const T& t)
	{
		if (len_ >= size_)
			return false;

		elems_[len_].elem = t;
		elems_[len_].parent = -1;
		elems_[len_].height = 1;

		return len_++;
	}

	int find(const T& t)
	{
		int i;

		for (i = 0; i < len_ && elems_[i].elem != t; i++);

		if (i >= len_)
			return -1;

		while (elems_[i].parent >= 0)
			i = elems_[i].parent;

		return i;
	}

	void union_sets(const T& t1, const T& t2)
	{
		int i1 = find(t1);
		int l2 = find(t2);

		if (i1 < 0 || i2 < 0)
			return;

		union_by_index(i1, i2);
	}

	void union_by_index(int i1, int i2)
	{
		if (elems_[i1].height > elems_[i2].height) {
			elems_[i2].parent = i1;
		}
		else if (elems_[i1].height < elems_[i2].height) {
			elems_[i1].parent = i2;
		}
		else {
			elems_[i2].parent = i1;
			elems_[i1].height++;
		}
	}

protected:
	Item* elems_;
	long size_;
	long len_;
};

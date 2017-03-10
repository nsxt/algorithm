#pragma once

/*
	B(Balanced)-Tree Search Map
*/

template<class T> class BTreeMap
{
public:
	enum Exception { INVALID_DIMENSION };

public:
	struct Node;
	typedef Node* PNODE;

	struct Node {
		T* keys;
		Node** childrens;
		int len;

		Node(int dim) {
			keys = new T[dim];
			childrens = new Node*[dim + 1];
			len = 0;
			
			for (int i = 0; i <= dim; i++) childrens[i] = nullptr;			
		}

		PNODE& left_child(int n) { return childrens[n]; }
		PNODE& right_child(int n) { return childrens[n + 1]; }
		T& key(int n) { return keys[n]; }
		int& length() { return len; }

		void add_value(const T& value, Node* left, Node* right)
		{		
			int i = len;

			// Insertion Sort
			while (i > 0 && key(i - 1) > value) {
				key(i) = key(i - 1);
				left_child(i + 1) = left_child(i);
				i--;
			}

			len++;

			key(i) = value;
			left_child(i) = left;
			right_child(i) = right;
		}

		// 값 삭제 및 배열의 중간에 빈곳이 없도록 처리
		void del_value(int index)
		{
			if (index < length() - 1) {
				for (int i = index + 1; i < length(); i++) {
					key(i - 1) = key(i);
					left_child(i - 1) = left_child(i);
				}

				left_child(i - 1) = left_child(i);
			}

			len--;
		}

		int find_key(const T& key)
		{
			for (int i = 0; i < length(); i++)
				if (key == key(i))
					return i;

			return -1;
		}

		void clear(int dim)
		{
			len = 0;

			for (int i = 0; i <= dim; i++)
				childrens[i] = nullptr;
		}
	};

public:
	BTreeMap(int dim = 5) 
	{
		if (dim < 3 || dim % 2 == 0)
			throw INVALID_DIMENSION;

		node_head_ = new Node(dim);
		dim_ = dim;
	}

	~BTreeMap() 
	{
		clear();
		delete node_head_;
	}

public:
	/**
		Capacity
	**/	
	long size() const { return size_; }
	bool empty() const { return size_ <= 0; }


	/**
		Modifiers
	**/
	bool insert(const T& value) 
	{

	}

	bool remove(const T& key)
	{

	}

	void clear()
	{

	}


	/**
		Lookup
	**/
	bool find(const T& key, T& value) const
	{
		Node* t;
		int index;

		t = node_head_->left_child(0);

		while (t != nullptr && (index = t->find_key(key)) < 0) {
			for (int i = 0; i < t->length() && key > t->key(i); i++);
			t = t->left_child(i);
		}
		
		if (t == nullptr)
			return false;

		value = t->key(index);

		return true;
	}

protected:
	/**
		Operators
	**/
	void _remove_subtree(Node* node)
	{

	}

	Node* _split(const T& key, Node* pivot)
	{

	}


protected:
	Node* node_head_;
	long size_;
	long dim_;
};
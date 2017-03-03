#pragma once
#include "binary_tree.h"

template<class T> class BinaryTreeMap : public BinaryTree<T>
{
public:
	enum Exception { INSUFFCIENT_MEMORY_FOR_SORT };	

public:
	BinaryTreeMap() : BinaryTree<T>()
	{
		size_ = 0;
	}

	~BinaryTreeMap()
	{
	}

public:
	/**
		Capacity
	**/
	bool empty() const { return size_ <= 0; }

	int size() const { return size_; }


	/**
		Modifiers
	**/
	virtual void clear() override
	{
		BinaryTree<T>::clear();
		size_ = 0;
	}

	void insert(const T& value)
	{
		Node* p = node_head_;
		Node* s = node_head_->left;

		while (s != node_tail_) {
			p = s;
			if (value > s->data)
				s = s->right;
			else
				s = s->left;
		}

		s = new Node;
		s->data = value;
		s->left = node_tail_;
		s->right = node_tail_;

		if (value > p->data && p != node_head_)
			p->right = s;
		else
			p->left = s;

		size_++;
	}

	/*
		여기에서 구현된 삭제 알고리즘의 조건은 오른쪽 서브트리의 최소값을 후보로 만든다.
		인터넷상의 다른 자료들을 보면 왼쪽 서브트리의 최대값을 후보로 올리는 경우가 많다.
		그래서 아래의 Case 를 구분하는 기준이 삭제할 노드를 대신할 노드를 찾는 기준에 따라 변경 될 수 있음을 알고 있어야 한다.
	*/
	bool remove(const T& key)
	{
		if (empty())
			return false;

		Node* delp = node_head_;
		Node* del = node_head_->left;
		Node* cddp;
		Node* cdd;

		// Find del node
		while (key != del->data && del != node_tail_) {
			
			delp = del;

			if (key > del->data)
				del = del->right;
			else
				del = del->left;
		}

		if (del == node_tail_)
			return false;

		// Case 1 : 삭제할 노드의 오른쪽 자식이 없는 경우
		if (del->right == node_tail_) {
			cdd = del->left;
		}
		// Case 2 : 삭제할 노드의 오른쪽 자식의 왼쪽 자식이 없는 경우
		else if (del->right->left == node_tail_) {
			cdd = del->right;
			cdd->left = del->left;
		}		
		// Case 3 : 그외 경우
		else {
			cddp = del;
			cdd = del->right;
			
			while (cdd->left != node_tail_) {
				cddp = cdd;
				cdd = cdd->left;
			}

			cddp->left = cdd->right;
			cdd->left = del->left;
			cdd->right = del->right;
		}

		if (key > delp->data && delp != node_head_)
			delp->right = cdd;
		else
			delp->left = cdd;

		delete del;
		size_--;

		return true;
	}


	/**
		Lookup
	**/
	bool find(const T& key, T& value) const
	{
		Node* s = node_head_->left;
		while (key != s->data && s != node_tail_) {
			if (key > s->data)
				s = s->right;
			else
				s = s->left;
		}

		if (s == node_tail_)
			return false;

		value = s->data;

		return true;
	}


	/**
		Operations
	**/
	void sort(T a[], int n, Node* p = nullptr) const
	{
		static int index = 0;
		if (p == nullptr) {
			if (size_ != n)
				throw INSUFFCIENT_MEMORY_FOR_SORT;

			index = 0;
			p = node_head_->left;
		}

		if (p != node_tail_) {
			sort(a, n, p->left);
			a[index++] = p->data;
			sort(a, n, p->right);
		}

	}

	void balance()
	{
		T* a;
		a = new T[size_];
		sort(a, size_);

		int count = size_;
		clear();

		node_head_ = _balance(a, count, true);
		size_ = count;

		delete[] a;
	}

protected:
	/**
		Operations
	**/
	virtual Node* _balance(T a[], int n, bool start = true)
	{
		static int index = 0;
		if (start)
			index = 0;

		Node* p;
		int nl, nr;
		if (n > 0) {
			nl = (n - 1) / 2;
			nr = n - nl - 1;

			p = new Node;
			p->left = _balance(a, nl, false);
			p->data = a[index++];
			p->right = _balance(a, nr, false);

			return p;
		}
		else {
			return node_tail_;
		}
	}

protected:
	int size_;
	
};
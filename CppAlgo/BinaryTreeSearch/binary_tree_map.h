#pragma once
#include "binary_tree.h"

template<class T> class BinaryTreeMap : public BinaryTree<T>
{
public:
	enum Exception {};

public:
	BinaryTreeMap()
	{

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

	bool remove(const T& key)
	{
		if (empty())
			return false;

		Node* delp = node_head_;
		Node* del = node_head->left;
		Node* cddp, cdd;

		// Find del node
		while (key != del->data && del != node_tail_) {
			del = delp;
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

	}

	void balance()
	{

	}

protected:
	/**
		Operations
	**/
	virtual Node* _balance(T a[], int n, bool start = true)
	{

	}

protected:
	int size_;
	
};
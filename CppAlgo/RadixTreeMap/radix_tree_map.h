#pragma once
#include "../BinaryTreeSearch/binary_tree.h"

/*
	Radix Tree Search Algorithm

- 기수 검색은 중복키를 허용하지 않는다.
- 중복키가 허용되면 tree 의 높이가 비트수보다 커진다.
- 만약 중복키를 허용하려면 Tree + List 개념으로 적용되야됨

*/

template<class T> class RadixTreeMap : public BinaryTree<T>
{
public:
	RadixTreeMap() : BinaryTree<T>(), size_(0) {}
	~RadixTreeMap() {}

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
		Node *p, *t;
		unsigned b = 0;

		p = node_head_;
		t = node_head_->left;

		while (t != node_tail_) {
			if (value == t->data)
				return false;

			p = t;
			t = _bits(value, b++, 1) ? t->right : t->left;
		}

		t = new Node;
		t->data = value;
		t->left = node_tail_;
		t->right = node_tail_;

		if (_bits(value, b - 1, 1) && p != node_head_)
			p->right = t;
		else
			p->left = t;

		size_++;

		return true;
	}

	bool remove(const T& key)
	{
		if (empty())
			return false;

		Node *del, *delp, *cdd, *cddp;
		unsigned b = 0;

		delp = node_head_;
		del = node_head_->left;

		while (del != node_tail_ && key != del->data) {
			delp = del;
			del = _bits(key, b++, 1) ? del->right : del->left;
		}

		if (del == node_tail_)
			return false;
				
		// Case 1, 2, 3 - Binary Tree Map 과 동일함
		if (del->right == node_tail_) {
			cdd = del->left;
		}
		else if (del->right->left == node_tail_) {
			cdd = del->right;
			cdd->left = del->left;
		}
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

		if (_bits(key, b - 1, 1) && delp != node_head_)
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
		Node *t;
		unsigned b = 0;

		t = node_head_->left;

		while (t != node_tail_ && key != t->data) {
			t = _bits(key, b++, 1) ? t->right : t->left;
		}

		if (t == node_tail_)
			return false;

		value = t->data;

		return true;
	}

protected:
	/**
		Utility
	**/
	unsigned long _bits(const T& x, unsigned long k, unsigned long j) const
	{
		return (x >> k) & ~(~0 << j);
	}

protected:
	long size_;
};
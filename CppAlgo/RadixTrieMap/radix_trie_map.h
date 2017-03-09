#pragma once
#include "../BinaryTreeSearch/binary_tree.h"

/*
	Radix Trie Search Algorithm

- RadixTrieMap 의 T 는 비트를 다룰 수 있는 타입만 가능

*/

template<class T> class RadixTrieMap : public BinaryTree<T>
{
public:
	RadixTrieMap() : BinaryTree<T>(), size_(0) {}
	~RadixTrieMap() {}

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
		unsigned b = 0;
		Node *gp, *p, *t;

		gp = p = node_head_;
		t = node_head_->left;

		while (t != node_tail_) {
			if (value == t->data)
				return false;

			gp = p;
			p = t;
			t = _bits(value, b++, 1) ? t->right : t->left;
		}

		b--;
		
		if (p == node_head_) { // Case 1 : 첫번째 데이타(Root)
			t = new Node;
			t->left = node_tail_;
			t->right = node_tail_;
			t->data = value;

			p->left = t;
		}
		else if (is_branch(p)) { // Case 2 : 부모가 분기노드
			t = new Node;
			t->left = node_tail_;
			t->right = node_tail_;
			t->data = value;

			if (_bits(value, b, 1))
				p->right = t;
			else
				p->left = t;
		}
		else {	// Case 3 : 부모가 정보노드
			do {

				// 새로운 Branch 노드 생성
				t = new Node;
				t->left = node_tail_;
				t->right = node_tail_;
				
				if (gp != node_head_ && _bits(value, b - 1, 1))
					gp->right = t;
				else
					gp->left = t;

				// p 에는 부모노드가 지정되어있음.
				// 부모노드는 gp 를 기준으로 분기노드와 모두 완료 되면 최종 부모 분기 노드에 붙임
				gp = t;
				b++;

			} while (_bits(value, b - 1, 1) == _bits(p->data, b - 1, 1));

			t = new Node;
			t->data = value;
			t->left = node_tail_;
			t->right = node_tail_;

			if (_bits(value, b - 1, 1)) {
				gp->right = t;
				gp->left = p;
			}
			else {
				gp->left = t;
				gp->right = p;
			}
		}

		size_++;

		return true;
	}

	/*
		- 삭제의 경우 아래의 두가지 경우로 분류
		  Case 1 : 형제노드가 분기노드
		  Case 2 : 형제노드가 정보노드
	*/
	bool remove(const T& key)
	{
		// cp 는 del 에서 가장 가까운 자식이 둘인 노드
		Node *delp, *del, *sib, *cp;
		unsigned b = 0, cpb = 0;

		cp = delp = node_head_;
		del = node_head_->left;

		while (is_branch(del)) {

			delp = del;

			if (del->left != node_tail_ &&
				del->right != node_tail_ &&
				(is_branch(del->left) || is_branch(del->right))) {

				// 자식이 두개인 노드 cp
				cp = del;
				cpb = b;
			}

			del = _bits(key, b++, 1) ? del->right : del->left;
		}

		if (del->data != key)
			return false;

		// Case 1, 2 공통
		delete del;

		// sib 노드(형제노드) 찾기
		if (delp != node_head_ && _bits(key, b - 1, 1)) {
			delp->right = node_tail_;
			sib = delp->left;
		}
		else {
			delp->left = node_tail_;
			sib = delp->right;
		}

		// sib 노드(형제노드)가 정보노드인 경우
		if (!is_branch(sib)) {
			delp = cp;
			del = _bits(key, cpb, 1) ? delp->right : delp->left;
			b = cpb + 1;

			while (is_branch(del)) {
				delp = del;
				del = _bits(key, b++, 1) ? delp->right : delp->left;
				delete delp;
			}

			if (cp != node_head_ && _bits(key, cpb, 1))
				cp->right = sib;
			else
				cp->left = sib;
		}

		size_--;

		return true;
	}

	virtual void clear() override
	{
		BinaryTree<T>::clear();
		size_ = 0;
	}


	/**
		Lookup
	**/
	bool find(const T& key, T& value) const
	{
		Node *t;
		unsigned b = 0;

		t = node_head_->left;

		while (is_branch(t)) {
			t = _bits(key, b++, 1) ? t->right : t->left;
		}

		if (t->data == key) {
			value = t->data;
			return true;
		}

		return false;
	}

protected:
	/**
		Utility
	**/
	unsigned long _bits(const T& x, unsigned long k, unsigned long j) const
	{
		return (x >> k) & ~(~0 << j);
	}

	bool is_branch(Node* p) const
	{
		return (p->left != node_tail_ || p->right != node_tail_);
	}

protected:
	long size_;
};
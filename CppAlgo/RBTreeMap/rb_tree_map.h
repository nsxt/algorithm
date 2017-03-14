#pragma once

/*
	Red - Black Tree Search Map
*/
template<class T> class RBTreeMap
{
public:
	struct Node {
		T data;
		Node* left;
		Node* right;
		bool red;
		Node() { left = right = nullptr; red = false; }
	};


public:
	RBTreeMap()
	{
		node_head_ = new Node;
		node_head_->left = nullptr;
		node_head_->right = nullptr;

		size_ = 0;
	}

	~RBTreeMap()
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
		Node *t, *p, *gp, *ggp;

		ggp = gp = p = node_head_;
		t = node_head_->left;

		while (t) {

			// 중복키 삽입 금지
			if (value == t->data)
				return false;

			// Color Promotion 이 필요한지 검사
			if (t->left && t->right && t->left->red && t->right->red) {

				t->red = true;
				t->left->red = false;
				t->right->red = false;

				// Rotation 이 필요한지 검사
				if (p->red) {
					gp->red = true;
					
					// Double Rotation 이 필요한지 검사
					if ((value > gp->data) != (value > p->data)) {
						p = _rotate(value, gp);
					}

					t = _rotate(value, ggp);
					t->red = false;
				}

				// Root Node 는 항상 Black
				node_head_->left->red = false;
			}

			ggp = gp;
			gp = p;
			p = t;

			if (value > t->data)
				t = t->right;
			else
				t = t->left;
		}

		t = new Node;
		t->data = value;
		t->left = nullptr;
		t->right = nullptr;
		t->red = true;

		if (value > p->data && p != node_head_)
			p->right = t;
		else
			p->left = t;

		size_++;

		// 부모노드가 Red 이면 한번더 회전을 해야됨
		if (p->red) {
			gp->red = true;

			// Double Rotation 검사
			if ((value > gp->data) != (value > p->data)) {
				p = _rotate(value, gp);
			}

			t = _rotate(value, ggp);
			t->red = false;
		}

		// Root 는 항상 Black
		node_head_->left->red = false;

		return true;
	}

	bool remove(const T& key)
	{
		Node *delgp, *delp, *del, *sib;
		T value = key;

		delgp = delp = node_head_;
		del = node_head_->left;
		sib = nullptr;

		while (!_is_leaf_node(del)) {
			
			// 삭제 노드가 black node 이면 부모를 red node 로 만들기 위한 시도를 한다.
			if (!del->red) {
				if (_red_as_parent(delgp, delp, sib)) {
					delgp = sib;
					if (del->data > delp->data || del->data == delp->data)
						sib = delp->left;
					else
						sib = delp->right;
				}
			}

			// 2노드일결우 3-4노드로 부풀리기 해야된다.
			if (del != node_head_->left && _is_2node(del)) {
				if (!_borrow_key(delgp, delp, del, sib))
					_merge_node(delp);
			}

			if (value == del->data)
				value = _swap_key(del);

			delgp = delp;
			delp = del;

			if (value > del->data || value == del->data) {
				sib = del->left;
				del = del->right;
			}
			else {
				sib = del->right;
				del = del->left;
			}
		}

		if (!del->red) {
			if (_red_as_parent(delgp, delp, sib)) {
				delgp = sib;

				if (del->data > delp->data || del->data == delp->data)
					sib = delp->left;
				else
					sib = delp->right;
			}
		}

		if (del != node_head_->left && _is_2node(del)) {
			if (!_borrow_key(delgp, delp, del, sib))
				_merge_node(delp);
		}

		if (_del_leaf_node(value, delp, del)) {
			size_--;
			return true;
		}
		else {
			return false;
		}
	}

	void clear()
	{
		_remove_subtree(node_head_->left);
		node_head_->left = nullptr;
	}


	/**
		Lookup
	**/
	bool find(const T& key, T& value) const
	{
		Node* s = node_head_->left;
		while (s && key != s->data) {
			if (key > s->data)
				s = s->right;
			else
				s = s->left;
		}

		if (s == 0)
			return false;

		value = s->data;

		return true;
	}


protected:
	/**
		Operators
	**/
	Node* _rotate(const T& key, Node* pivot)
	{
		Node *child, *gchild;

		if ((key > pivot->data || key == pivot->data) && pivot != node_head_)
			child = pivot->right;
		else
			child = pivot->left;

		// Rotate Left
		if (key > child->data || key == child->data) {
			gchild = child->right;
			child->right = gchild->left;
			gchild->left = child;
		}
		// Rotate Right
		else {
			gchild = child->left;
			child->left = gchild->right;
			gchild->right = child;
		}

		if ((key > pivot->data || key == pivot->data) && pivot != node_head_)
			pivot->right = gchild;
		else
			pivot->left = gchild;

		return gchild;
	}

	bool _is_leaf_node(const Node* p) const
	{
		if (p == nullptr)
			return false;

		// 자식노드가 하나도 없거나, 하나만 있을경우는 red node 이다.
		// 즉, 단 하나의 검정노드를 가질 수 없다.
		// 1. 빨간 노드는 자식이 없던가, 있다면 두개의 검정노드여야 한다.
		// 2. 검정노드는 자식이 없던가, 있다면 하나의 빨간 노드나 두개의 빨간 노드나 두개의 검정 노드를 가진다.
		if ((p->left == nullptr || (p->left && p->left->red && !p->left->left && !p->left->right)) &&
			(p->right == nullptr || (p->right && p->right->red && !p->right->left && !p->right->right)))
			return true;
		else
			return false;
	}

	bool _is_2node(const Node* p) const
	{
		if (p == nullptr)
			return false;

		if (p->red == true)
			return false;

		if ((p->left == nullptr && p->right == nullptr) ||
			(p->left && p->right && !p->left->red && !p->right->red))
			return true;
		else
			return false;
	}

	bool _del_leaf_node(const T& key, Node* delp, Node* del)
	{
		// 자식노드가 없는 완전한 leaf node
		if (key == del->data && !del->left && !del->right) {
			delete del;

			if ((key > delp->data || key == delp->data) && delp != node_head_)
				delp->right = nullptr;
			else
				delp->left = nullptr;

			return true;
		}
		// 자식 노드가 하나이상 존재하고 del 은 black 노드
		else if (key == del->data) {
			Node* ret;

			if (del->left) {
				del->left->right = del->right;
				ret = del->left;
				ret->red = false;
				delete del;
			}
			else if (del->right) {
				del->right->left = del->left;
				ret = del->right;
				ret->red = false;
				delete del;
			}

			if ((ret->data > delp->data || ret->data == delp->data) && delp != node_head_)
				delp->right = ret;
			else
				delp->left = ret;

			return true;
		}
		// 삭제 대상이 del 의 왼쪽 자식 노드일 경우
		else if (del->left && key == del->left->data) {
			delete del->left;
			del->left = nullptr;
			return true;
		}
		// 삭제 대상이 del 의 오른쪽 자식 노드일 경우
		else if (del->right && key == del->right->data) {
			delete del->right;
			del->right = nullptr;
			return true;
		}
		else {
			return false;
		}
	}

	// 하향탐색 경로로 빨간노드 옮기기
	bool _red_as_parent(Node* delgp, Node* delp, Node* sib)
	{
		if (sib == nullptr || !sib->red)
			return false;

		_rotate(sib->data, delgp);

		sib->red = false;
		delp->red = true;

		return true;
	}

	// 오른쪽 서브트리의 최소값으로 대체값을 사용한다.
	// 그리고 대체된 값을 삭제 대상으로 해서 노드삭제를 진행한다.
	T _swap_key(Node* del)
	{
		Node* cdd = del->right;
		while (cdd->left) {
			cdd = cdd->left;
		}

		del->data = cdd->data;

		return cdd->data;
	}

	bool _borrow_key(Node* delgp, Node* delp, Node* del, Node* sib)
	{
		Node* sibrc;

		if (_is_2node(sib))
			return false;

		if (del->data > sib->data) {
			if (sib->left && sib->left->red)
				sibrc = sib->left;
			else
				sibrc = sib->right;
		}
		else {
			if (sib->right && sib->right->red)
				sibrc = sib->right;
			else
				sibrc = sib->left;
		}

		// Double Rotation
		if ((delp->data > sib->data) != (sib->data > sibrc->data)) {
			_rotate(sibrc->data, delp);
			_rotate(sibrc->data, delgp);
			sib->red = false;
			sibrc->red = true;
		}
		// Single Rotation
		else {
			_rotate(sib->data, delgp);
			sib->red = true;
			sibrc->red = false;
		}

		// Color Demotion
		del->red = true;
		delp->red = false;

		// root 는 항상 black
		if (node_head_->left->red)
			node_head_->left->red = false;

		return true;
	}

	// sibling 이 black node 이고 sibling 의 두자식도 black node 인 경우,
	// Color Demotion 을 사용하여 노드 병합
	// 조건 검사는 호출한 함수해서 하여야 한다.
	void _merge_node(Node* delp)
	{
		delp->red = false;
		delp->left->red = true;
		delp->right->red = true;
	}

	void _remove_subtree(Node* node)
	{
		if (node != nullptr) {
			_remove_subtree(node->left);
			_remove_subtree(node->right);
			delete node;
		}
	}

protected:
	Node* node_head_;
	long size_;

};

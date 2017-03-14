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

			// �ߺ�Ű ���� ����
			if (value == t->data)
				return false;

			// Color Promotion �� �ʿ����� �˻�
			if (t->left && t->right && t->left->red && t->right->red) {

				t->red = true;
				t->left->red = false;
				t->right->red = false;

				// Rotation �� �ʿ����� �˻�
				if (p->red) {
					gp->red = true;
					
					// Double Rotation �� �ʿ����� �˻�
					if ((value > gp->data) != (value > p->data)) {
						p = _rotate(value, gp);
					}

					t = _rotate(value, ggp);
					t->red = false;
				}

				// Root Node �� �׻� Black
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

		// �θ��尡 Red �̸� �ѹ��� ȸ���� �ؾߵ�
		if (p->red) {
			gp->red = true;

			// Double Rotation �˻�
			if ((value > gp->data) != (value > p->data)) {
				p = _rotate(value, gp);
			}

			t = _rotate(value, ggp);
			t->red = false;
		}

		// Root �� �׻� Black
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
			
			// ���� ��尡 black node �̸� �θ� red node �� ����� ���� �õ��� �Ѵ�.
			if (!del->red) {
				if (_red_as_parent(delgp, delp, sib)) {
					delgp = sib;
					if (del->data > delp->data || del->data == delp->data)
						sib = delp->left;
					else
						sib = delp->right;
				}
			}

			// 2����ϰ�� 3-4���� ��Ǯ���� �ؾߵȴ�.
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

		// �ڽĳ�尡 �ϳ��� ���ų�, �ϳ��� �������� red node �̴�.
		// ��, �� �ϳ��� ������带 ���� �� ����.
		// 1. ���� ���� �ڽ��� ������, �ִٸ� �ΰ��� ������忩�� �Ѵ�.
		// 2. �������� �ڽ��� ������, �ִٸ� �ϳ��� ���� ��峪 �ΰ��� ���� ��峪 �ΰ��� ���� ��带 ������.
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
		// �ڽĳ�尡 ���� ������ leaf node
		if (key == del->data && !del->left && !del->right) {
			delete del;

			if ((key > delp->data || key == delp->data) && delp != node_head_)
				delp->right = nullptr;
			else
				delp->left = nullptr;

			return true;
		}
		// �ڽ� ��尡 �ϳ��̻� �����ϰ� del �� black ���
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
		// ���� ����� del �� ���� �ڽ� ����� ���
		else if (del->left && key == del->left->data) {
			delete del->left;
			del->left = nullptr;
			return true;
		}
		// ���� ����� del �� ������ �ڽ� ����� ���
		else if (del->right && key == del->right->data) {
			delete del->right;
			del->right = nullptr;
			return true;
		}
		else {
			return false;
		}
	}

	// ����Ž�� ��η� ������� �ű��
	bool _red_as_parent(Node* delgp, Node* delp, Node* sib)
	{
		if (sib == nullptr || !sib->red)
			return false;

		_rotate(sib->data, delgp);

		sib->red = false;
		delp->red = true;

		return true;
	}

	// ������ ����Ʈ���� �ּҰ����� ��ü���� ����Ѵ�.
	// �׸��� ��ü�� ���� ���� ������� �ؼ� �������� �����Ѵ�.
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

		// root �� �׻� black
		if (node_head_->left->red)
			node_head_->left->red = false;

		return true;
	}

	// sibling �� black node �̰� sibling �� ���ڽĵ� black node �� ���,
	// Color Demotion �� ����Ͽ� ��� ����
	// ���� �˻�� ȣ���� �Լ��ؼ� �Ͽ��� �Ѵ�.
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

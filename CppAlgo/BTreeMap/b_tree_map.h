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

		// �� ���� �� �迭�� �߰��� ����� ������ ó��
		void del_value(int index)
		{
			int i = 0;

			if (index < length() - 1) {
				for (i = index + 1; i < length(); i++) {
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
				if (key == this->key(i))
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
		size_ = 0;
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
		Node *t, *p;
		int i;

		p = node_head_;
		t = node_head_->left_child(0);

		if (t == nullptr) {
			t = new Node(dim_);
			node_head_->left_child(0) = t;
		}

		while (t != nullptr) {
			if (t->find_key(value) >= 0)
				return false;

			if (t->length() == dim_)
				t = _split(value, p);

			p = t;
			
			for (i = 0; i < t->length() && value > t->key(i); i++);

			t = t->left_child(i);
		}

		p->add_value(value, nullptr, nullptr);
		size_++;

		return true;
	}

	bool remove(const T& key)
	{
		Node *t, *p;
		int pi = 0;		// �θ����� index
		int ti = 0;		// �������� index
		T value = key;

		p = node_head_;
		t = node_head_->left_child(0);

		while (t != nullptr) {

			// Ȯ���� �ʿ䰡 ������ Ȯ��
			if (t->length() <= dim_ / 2 && p != node_head_) {

				// �������Լ� �������� �����ϸ� ������ ����
				if (!_borrow_key(p, pi))
					t = _merge_node(p, pi);
			}

			if ((ti = t->find_key(value)) >= 0) {
				if (t->left_child(0) == nullptr)	// �ܺγ��
					break;
				else                                // ���γ��
					value = _swap_key(t, ti);
			}

			p = t;
			for (pi = 0; pi < t->length() && (value > t->key(pi) || value == t->key(pi)); pi++);
			t = t->left_child(pi);
		}

		if (t == nullptr)
			return false;

		// �ܺγ���ε� Ű���� ������ ������ Ȥ�� ������ ����
		if (t->length() <= dim_ / 2 && p != node_head_) {
			if (!_borrow_key(p, pi))
				t = _merge_node(p, pi);
		}

		t->del_value(t->find_key(value));
		size_--;

		return true;
	}

	void clear()
	{
		_remove_subtree(node_head_->left_child(0));
		node_head_->left_child(0) = nullptr;
		size_ = 0;
	}	


	/**
		Lookup
	**/
	bool find(const T& key, T& value) const
	{
		Node* t;
		int index;
		int i;

		t = node_head_->left_child(0);

		while (t != nullptr && (index = t->find_key(key)) < 0) {
			for (i = 0; i < t->length() && key > t->key(i); i++);
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
		if (node != nullptr) {
			for (int i = 0; i <= node->length(); i++)
				_remove_subtree(node->left_child(i));

			delete node;
		}
	}

	Node* _split(const T& key, Node* pivot)
	{
		Node *left, *right;
		Node *split;
		int i, j;

		right = new Node(dim_);

		// Case 1 : ������ ��尡 root �� ���
		if (pivot == node_head_) {
			
			// ��Ȱ�Ǿ� ���ϵ� �θ� ��� (root)
			split = pivot->left_child(0);
			
			// Left Node
			left = new Node(dim_);
			for (i = 0; i < dim_ / 2; i++) {
				left->key(i) = split->key(i);
				left->left_child(i) = split->left_child(i);
			}
			
			left->left_child(i) = split->left_child(i);
			left->length() = dim_ / 2;


			// right child
			for (i = dim_ / 2 + 1, j = 0; i < dim_; i++, j++) {
				right->key(j) = split->key(i);
				right->left_child(j) = split->left_child(i);
			}
			
			right->left_child(j) = split->left_child(i);
			right->length() = dim_ / 2;

			// �θ��� ���� (�̷��� Ȧ�� ������ ����!!)
			T temp = split->key(dim_ / 2);
			split->clear(dim_);
			split->add_value(temp, left, right);
		}
		// Case 2 : ������ ��尡 root �� �ƴ� ���
		else {			
			// ������ ��� �˻�
			for (i = 0; i < pivot->length() && key > pivot->key(i); i++);

			// ���� �ڽ� ���� �̹� �ִ� ����̹Ƿ� ������ ����
			left = pivot->left_child(i);
			left->length() = dim_ / 2;

			// ������ �ڽ� ���
			for (i = dim_ / 2 + 1, j = 0; i < dim_; i++, j++) {
				right->key(j) = left->key(i);
				right->left_child(j) = left->left_child(i);
			}

			right->left_child(j) = left->left_child(i);
			right->length() = dim_ / 2;

			// �߰�Ű�� �θ� ����
			pivot->add_value(left->key(dim_ / 2), left, right);
			split = pivot;
		}

		return split;
	}

	// p:�θ���, index:�θ��忡�� �������� �ڽĳ���� �ε��� ex) p->left_child(index)
	bool _borrow_key(Node* p, int index)
	{
		int from, to;
		Node *p1, *p2;

		to = index;
		if (index == p->length())	// ���� �������� ��� ������������ ����
			from = index - 1;
		else                        // �ƴϸ� ������ �������� ����
			from = index + 1;

		p1 = p->left_child(from);	// p1 = �����ִ� ���
		p2 = p->left_child(to);		// p2 = ������ ���

		// ������ Ű�� �������� ����
		if (p1->length() <= dim_ / 2)
			return false;

		if (from > to) {	// ������ �������Լ� ����
			p2->add_value(p->key(to), p2->left_child(p2->length()), p1->left_child(0));
			p->key(to) = p1->key(0);
			p1->del_value(0);
		}
		else {				// ���� �������Լ� ����
			p2->add_value(p->key(from), p1->left_child(p1->length()), p2->left_child(0));
			p->key(from) = p1->key(p1->length() - 1);
			p1->del_value(p1->length() - 1);
		}

		return true;
	}

	// p:�θ���, index:�θ��忡�� �պ��ϴ� �ڽĳ���� �ε���
	Node* _merge_node(Node* p, int index)
	{
		Node *left, *right;
		int i;

		// ���� ������ �ڽĳ���̸� index ����
		if (index == p->length())
			index--;

		left = p->left_child(index);
		right = p->right_child(index);

		// ���� ��忡 �θ�Ű�� ����
		left->key(left->length()++) = p->key(index);

		// ���� ��忡 ������ ��带 ����
		for (i = 0; i < right->length(); i++) {
			left->key(left->length()) = right->key(i);
			left->left_child(left->length()++) = right->left_child(i);
		}
		left->left_child(left->length()) = right->left_child(i);

		p->del_value(index);
		p->left_child(index) = left;

		delete right;

		// root ���� M/2 �ּ� ���� ���ǿ� ������ ���� �����Ƿ�, 0 �� �� �� �� �ִ�.
		if (p->length() == 0) {
			delete p;
			node_head_->left_child(0) = left;
		}

		return left;
	}

	// ���� ��� ���� �� ��ü ��带 ã�Ƽ� ��ȯ
	T _swap_key(Node* del, int index)
	{
		// cdd ��ü���, cddp ��ü����� �θ�
		Node *cdd, *cddp;

		cddp = del;
		cdd = cddp->right_child(index);

		while (cdd->left_child(0) != nullptr) {
			cddp = cdd;
			cdd = cdd->left_child(0);
		}

		del->key(index) = cdd->key(0);

		return cdd->key(0);
	}

protected:
	Node* node_head_;
	long size_;
	long dim_;
};
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
		int pi = 0;		// 부모노드의 index
		int ti = 0;		// 현재노드의 index
		T value = key;

		p = node_head_;
		t = node_head_->left_child(0);

		while (t != nullptr) {

			// 확장할 필요가 있으면 확장
			if (t->length() <= dim_ / 2 && p != node_head_) {

				// 형제에게서 빌려보고 실패하면 형제와 결합
				if (!_borrow_key(p, pi))
					t = _merge_node(p, pi);
			}

			if ((ti = t->find_key(value)) >= 0) {
				if (t->left_child(0) == nullptr)	// 외부노드
					break;
				else                                // 내부노드
					value = _swap_key(t, ti);
			}

			p = t;
			for (pi = 0; pi < t->length() && (value > t->key(pi) || value == t->key(pi)); pi++);
			t = t->left_child(pi);
		}

		if (t == nullptr)
			return false;

		// 외부노드인데 키수가 적으면 빌리기 혹은 병합을 수행
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

		// Case 1 : 분할할 노드가 root 인 경우
		if (pivot == node_head_) {
			
			// 분활되어 리턴될 부모 노드 (root)
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

			// 부모노드 정리 (이래서 홀수 차수가 쉽다!!)
			T temp = split->key(dim_ / 2);
			split->clear(dim_);
			split->add_value(temp, left, right);
		}
		// Case 2 : 분할할 노드가 root 가 아닌 경우
		else {			
			// 분할할 노드 검색
			for (i = 0; i < pivot->length() && key > pivot->key(i); i++);

			// 왼쪽 자식 노드는 이미 있는 노드이므로 갯수만 조정
			left = pivot->left_child(i);
			left->length() = dim_ / 2;

			// 오른쪽 자식 노드
			for (i = dim_ / 2 + 1, j = 0; i < dim_; i++, j++) {
				right->key(j) = left->key(i);
				right->left_child(j) = left->left_child(i);
			}

			right->left_child(j) = left->left_child(i);
			right->length() = dim_ / 2;

			// 중간키를 부모에 삽입
			pivot->add_value(left->key(dim_ / 2), left, right);
			split = pivot;
		}

		return split;
	}

	// p:부모노드, index:부모노드에서 빌려가는 자식노드의 인덱스 ex) p->left_child(index)
	bool _borrow_key(Node* p, int index)
	{
		int from, to;
		Node *p1, *p2;

		to = index;
		if (index == p->length())	// 가장 오른쪽인 경우 왼쪽형제에게 빌림
			from = index - 1;
		else                        // 아니면 오른쪽 형제에게 빌림
			from = index + 1;

		p1 = p->left_child(from);	// p1 = 빌려주는 노드
		p2 = p->left_child(to);		// p2 = 빌리는 노드

		// 빌려줄 키가 없을때는 실패
		if (p1->length() <= dim_ / 2)
			return false;

		if (from > to) {	// 오른쪽 형제에게서 빌림
			p2->add_value(p->key(to), p2->left_child(p2->length()), p1->left_child(0));
			p->key(to) = p1->key(0);
			p1->del_value(0);
		}
		else {				// 왼쪽 형제에게서 빌림
			p2->add_value(p->key(from), p1->left_child(p1->length()), p2->left_child(0));
			p->key(from) = p1->key(p1->length() - 1);
			p1->del_value(p1->length() - 1);
		}

		return true;
	}

	// p:부모노드, index:부모노드에서 합병하는 자식노드의 인덱스
	Node* _merge_node(Node* p, int index)
	{
		Node *left, *right;
		int i;

		// 가장 오른쪽 자식노드이면 index 감소
		if (index == p->length())
			index--;

		left = p->left_child(index);
		right = p->right_child(index);

		// 왼쪽 노드에 부모키를 복사
		left->key(left->length()++) = p->key(index);

		// 왼쪽 노드에 오른쪽 노드를 복사
		for (i = 0; i < right->length(); i++) {
			left->key(left->length()) = right->key(i);
			left->left_child(left->length()++) = right->left_child(i);
		}
		left->left_child(left->length()) = right->left_child(i);

		p->del_value(index);
		p->left_child(index) = left;

		delete right;

		// root 노드는 M/2 최소 개수 조건에 영향을 받지 않으므로, 0 이 될 수 도 있다.
		if (p->length() == 0) {
			delete p;
			node_head_->left_child(0) = left;
		}

		return left;
	}

	// 내부 노드 삭제 시 대체 노드를 찾아서 교환
	T _swap_key(Node* del, int index)
	{
		// cdd 대체노드, cddp 대체노드의 부모
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
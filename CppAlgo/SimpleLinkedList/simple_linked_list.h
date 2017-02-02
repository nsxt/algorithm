#pragma once

typedef void* POS;

template <class T> class SimpleLinkedList {
public:
	enum Exception {
		INVALID_POS,
		EMPTY_LIST
	};

public:
	SimpleLinkedList() { _init(); }
	~SimpleLinkedList() { _clear(); }

	/*
		basic operation
	*/

	T delete_next(POS pos)
	{
		// Node type casting
		Node* node = (Node*)pos;

		// Check validation of node
		if (node == nullptr) {
			throw INVALID_POS;
		}

		if (node == tail_node_) {
			throw INVALID_POS;
		}

		// �ܹ��� ��ũ�� ����Ʈ�̹Ƿ� �Է����� �־��� ����� ���� ��带 ����
		// Delete operation of node
		Node* del_node = node->next;
		node->next = del_node->next;

		// ������ ����� ���� ����
		T rt = del_node->data;
		delete del_node;
		count_--;

		return rt;
	}

	POS insert_next(POS pos, const T& new_elem)
	{
		// Node type casting
		Node* node = (Node*)pos;
		
		// Check validation of node
		if (node == nullptr) {
			throw INVALID_POS;
		}

		if (node == tail_node_) {
			throw INVALID_POS;
		}

		// Create new node
		Node* new_node = new Node();
		new_node->data = new_elem;

		// Assign link
		new_node->next = node->next;
		node->next = new_node;

		// Increase node count
		count_++;

		// Return new node
		return new_node;
	}

	void remove_all()
	{
		// remove_head �� ����Ͽ� ����Ʈ ����
		int n = get_count();
		for (int i = 0; i < n; i++) {
			remove_head();
		}
	}

	bool is_empty() const 
	{ 
		return count_ == 0; 
	}
	
	int get_count() const 
	{ 
		return count_; 
	}

	bool is_valid(POS pos) const 
	{
		return (pos != nullptr && pos != (POS)head_node_ && pos != (POS)tail_node_);
	}


	/*
		head operation
	*/

	POS add_head(const T& new_elem)
	{
		// insert_next �� ����Ͽ� �߰�
		return insert_next(head_node_, new_elem);
	}

	T remove_head()
	{
		// delete_next �� ����Ͽ� head ���(���γ��) ������ ����
		return delete_next(head_node_);
	}

	T& get_head() {
		// ���� ������ ������ ��ȿ �����Ͱ� �ִ��� �˻�
		// �뵵�� ���� �����͸� ���� 
		if (count_ > 0) {
			return head_node_->next->data;
		
		} else {
			throw EMPTY_LIST;
		}
	}

	T get_next() const
	{
		// ���� ������ ������ ��ȿ �����Ͱ� �ִ��� �˻�
		// �뵵�� ���� �����͸� ���� 
		if (count_ > 0) {
			return head_node_->next->data;

		}
		else {
			throw EMPTY_LIST;
		}
	}


	/*
		traverse
	*/

	// ���Ե� ������ ��� �� ���� ���� ��带 ����
	POS get_head_position() const 
	{ 
		return (count_ > 0) ? head_node_->next : nullptr;
	}

	// pos �� ���޹��� ����� ���� ��带 ������ �����ϰ�, pos ����� ���� �����Ѵ�.
	// �̷��� �޼ҵ�� �ݺ�������� ��带 ��ȸ�Ҷ� ��� �� �� �ִ�.
	// ���� ��尡 ���ٸ�, ������ ���޹��� pos ��带 null �� �����Ѵ�.
	// ��ȿ���� ���� (head, tail) ��尡 pos �Ķ���� �Է����� ���޵Ǹ� ���ܸ� �߻���Ų��.
	T& get_next(POS& pos)
	{
		// ���� ���� pos ��尡 ��ȿ���� �˻�
		if (!is_valid(pos)) {
			throw INVALID_POS;
		}

		// ���� ���� pos ��� �Ķ���� Ÿ�� ĳ����
		Node* node = static_cast<Node*>(pos);

		// ĳ���� �Ϸ�� node �� ���� ��� ��ȿ�� �˻� �� ��� ����
		if (!is_valid(node->next)) {
			pos = nullptr;

		} else {
			pos = node->next;
		}
		
		return node->data;
	}

	// ��� �������� ������ �����ϴ� get_next() �޼ҵ�� �ڵ� ������ �����ϴ�.
	T get_next(POS& pos) const
	{
		// ���� ���� pos ��尡 ��ȿ���� �˻�
		if (!is_valid(pos)) {
			throw INVALID_POS;
		}

		// ���� ���� pos ��� �Ķ���� Ÿ�� ĳ����
		Node* node = static_cast<Node*>(pos);

		// ĳ���� �Ϸ�� node �� ���� ��� ��ȿ�� �˻� �� ��� ����
		if (!is_valid(node->next)) {
			pos = nullptr;
		} else {
			pos = node->next;
		}

		return node->data;
	}


	/*
		getter / setter
	*/

	// ���� ���� pos ����� �����͸� �����Ѵ�.
	// ��ȿ���� ���� ����� ��� ���ܸ� �߻��Ѵ�.
	T& get_at(POS pos)
	{
		if (!is_valid(pos)) {
			throw INVALID_POS;
		}

		Node* node = static_cast<Node*>(pos);
		if (!is_valid(node)) {
			throw INVALID_POS;
		}

		return node->data;
	}

	// ��� �������� ������ �����ϴ� get_at() �޼ҵ�� �����ϴ�.
	T get_at(POS pos) const
	{
		if (!is_valid(pos)) {
			throw INVALID_POS;
		}

		Node* node = static_cast<Node*>(pos);
		if (!is_valid(node)) {
			throw INVALID_POS;
		}

		return node->data;
	}

	// new_elem ���� pos ����� ���� ������.
	// ��ȿ���� ���� ����� ��� ���ܸ� �߻���.
	void set_at(POS pos, const T& new_elem)
	{
		if (!is_valid(pos)) {
			throw INVALID_POS;
		}

		Node* node = static_cast<Node*>(pos);
		if (!is_valid(pos)) {
			throw INVALID_POS;
		}

		node->data = new_elem;
	}


	/*
		find
	*/

	// start_node �� �������� search_val ���� ��ġ�ϴ� �����͸� ���� ��尡 �ִ��� �˻��ϰ�,
	// �˻� ��� ã�� ��带 �����Ѵ�.
	// �޼ҵ� ȣ�� �� start_node �� ���� �������� head ���� �˻��� �����Ѵ�.
	// �Է����� �־��� ��尡 ��ȿ���� ���� ��� head ���� �˻��� �����ϱ⶧���� ���� �߻��� ����.
	// ����Ʈ�� ��� ���� ��쿡�� nullptr �� ���ϵȴ�.
	// ���� : get_at(), get_next() ���� ���ܰ� �߻� �� �� �ִ�.
	// ���ܰ� �߻� �� �� �ִ� ���� ���� ������� ����� ������ �ּҰ� ���޵Ǹ� �߻��� �� �ִµ�...
	// ���� ���� �������� void* �� ���� ĳ���� �ϸ� �˼� �ֳ�??? 
	// void* �� �ᱹ Ÿ�Կ� �������� �ʴٴ� ����̱���...
	POS find(const T& search_val, POS start_node = nullptr) const
	{
		POS pos;
		if (!is_valid(start_node)) {
			pos = get_head_position();
		} else {
			pos = start_node;
		}

		while (pos) {
			T d = get_at(pos);
			if (search_val == d) {
				break;
			}			
			get_next(pos);
		}

		return pos;
	}

	// ����Ʈ�� ���ӵ� �޸𸮿� ���������� ������ �� ������ ���������� �Ǿ������Ƿ�,
	// ���������� �ε����� ���� ��� ȹ�� ����� �����Ѵ�.
	POS find_index(int index) const
	{
		// ���޵� index �� ��ȿ������ �ִ��� �˻�
		if (index > count_) {
			return nullptr;
		}

		POS pos = get_head_position();
		for (int i = 0; i < index; i++) {
			get_next(pos);
		}

		return pos;
	}


protected:
	struct Node {
		T data;
		Node* next;
		Node() { next = 0; }
	};

	Node* head_node_;
	Node* tail_node_;
	int count_;

	void _init()
	{
		// head, tail ��� ����
		head_node_ = new Node;
		tail_node_ = new Node;

		// head, tail ��� �ʱ�ȭ
		head_node_->next = tail_node_;
		tail_node_->next = tail_node_;

		// count �ʱ�ȭ
		count_ = 0;
	}
	

	void _clear()
	{
		// ���� ��� ��� ����
		remove_all();

		// head, tail �ʱ�ȭ
		if (head_node_) {
			delete head_node_;
		}

		if (tail_node_) {
			delete tail_node_;
		}

		// reset
		head_node_ = nullptr;
		tail_node_ = nullptr;
		count_ = 0;
	}
};
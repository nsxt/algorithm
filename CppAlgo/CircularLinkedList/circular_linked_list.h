#pragma once

/*
	Circular Linked List (ȯ�� ���� ����Ʈ)

- SimpleLinkedList �� ��κ� �����ϳ� CircularLinkedList �� Tail ������ ����.
  �׻� ������ ���� Head �� ���� �Ǿ��ִ�.
  Circular �ڷᱸ���� Ư���� �̸� �ڷᱸ���� ũ�Ⱑ �����Ǿ�� �Ѵ�.

*/
template<class T> class CircularLinkedList 
{
public:
	typedef void* iterator;
	
	enum Exception { INVALID_POS, EMPTY_LIST, NO_IMPLEMENTED };

	struct Node {
		T data;
		Node* next;
		Node() { next = nullptr; }
	};

public:
	CircularLinkedList()
	{
		node_head_ = new Node;
		size_ = 0;

		node_head_->next = node_head_;
	}

	~CirsularLinkedList()
	{
		int n = size();
		for (int i = 0; i < n; i++) {
			pop_front();
		}

		delete node_head_;
	}

public:
	/**
		Element access
	**/
	T& front()
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		return node_head_->next->data;
	}

	T& back()
	{
		// 'Circular Linked List' does not need to be implemented.
		throw NO_IMPLEMENTED;
	}
	
	T& at(iterator pos)
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}
		
		Node* node = static_cast<Node*>(pos);

		if (node == nullptr) {
			throw INVALID_POS;
		}

		if (node == node_head_) {
			return node_head_->next->data;
		}

		return node->data;
	}

	void set(iterator pos, const T& value)
	{
		at(pos) = value;
	}


	/**
		Modifiers
	**/
	void push_front(const T& value)
	{
		insert(node_head_, value);
	}

	void push_back(const T& value)
	{
		// 'Circular Linked List' does not need to be implemented.
		throw NO_IMPLEMENTED;
	}
	
	void pop_front()
	{
		erase(node_head_);
	}

	void pop_back()
	{
		// 'Circular Linkged List' does not need to be implemented.
		throw NO_IMPLEMENTED;
	}
	
	iterator insert(iterator pos, const T& value)
	{
		Node* node = static_cast<Node*>(pos);

		if (node == nullptr) {
			throw INVALID_POS;
		}

		Node* new_node = new Node;
		new_node->data = value;
		new_node->next = node->next;
		node->next = new_node;

		size_++;

		return static_cast<iterator>(new_node);
	}


	void erase(iterator pos)
	{
		Node* node = static_cast<Node*>(pos);

		if (node == nullptr) {
			throw INVALID_POS;
		}

		if (node->next == node_head_) {
			throw INVALID_POS;
		}

		Node* del_node = node->next;
		node->next = del_node->next;
		
		delete del_node;
		size_--;
	}
	

	/**
		Capacity
	**/
	bool empty() const { return (size_ <= 0); }
	int size() const { return size_; }


	/**
		Iterator operations
	**/
	iterator next(iterator pos)
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		Node* node = static_cast<Node*>(pos);

		if (node == nullptr) {
			throw INVALID_POS;
		}
		
		if (node->next == node_head_) {
			return static_cast<iterator>(node_head_->next);
		}
		
		return static_cast<iterator>(node->next);
	}
	
	iterator prev(iterator pos)
	{
		// 'Circular Linkged List' does not need to be implemented.
		throw NO_IMPLEMENTED;
	}


	/**
		Operations
	**/
	iterator index(int pos)
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		if (pos < 0 || pos > size_) {
			throw INVALID_POS;
		}

		Node* rt = node_head_->next;
		int n = ;
		for (int i = 1; i < n; i++) {
			rt = rt->next;
		}

		return static_cast<iterator>(rt);
	}

protected:
	Node* node_head_;
	int size_;
};

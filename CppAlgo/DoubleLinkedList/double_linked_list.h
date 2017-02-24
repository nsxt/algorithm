#pragma once

/*
	Double Linked List
*/
template<class T> class DoubleLinkedList
{
public:
	typedef void* iterator;

	enum Exception { INVALID_POS, EMPTY_LIST, NO_IMPLEMENTED };

	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node() { next = prev = nullptr; }
	};

public:
	DoubleLinkedList()
	{
		node_head_ = new Node;
		node_tail_ = new Node;
		size_ = 0;

		node_head_->prev = node_head_;
		node_head_->next = node_tail_;		

		node_tail_->prev = node_head_;
		node_tail_->next = node_tail_;
	}

	~DoubleLinkedList()
	{
		int n = size();
		for (int i = 0; i < n; i++) {
			pop_front();
		}

		delete node_head_;
		delete node_tail_;
	}

public:
	/**
		Element access
	**/

	T front() const
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		return node_head_->next->data;
	}

	T back() const
	{		
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		return node_tail_->prev->data;
	}

	T at(iterator pos) const
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		Node* node = static_cast<Node*>(pos);

		if (node == nullptr || node == node_head_ || node == node_tail_) {
			throw INVALID_POS;
		}

		return node->data;
	}

	void set(iterator pos, const T& value)
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		Node* node = static_cast<Node*>(pos);

		if (node == nullptr || node == node_head_ || node == node_tail_) {
			throw INVALID_POS;
		}

		node->data = value;
	}


	/**
		Iterator
	**/

	iterator begin() const
	{
		if (size_ <= 0) {
			return nullptr;
		}

		return static_cast<iterator>(node_head_->next);
	}

	iterator end() const
	{
		if (size_ <= 0) {
			return nullptr;
		}

		return static_cast<iterator>(node_tail_->prev);
	}



	/**
		Modifiers
	**/

	void clear()
	{
		int n = size();
		for (int i = 0; i < n; i++) {
			pop_front();
		}
	}

	void push_front(const T& value)
	{
		insert_after(node_head_, value);
	}

	void push_back(const T& value)
	{
		insert_before(node_tail_, value);
	}

	void pop_front()
	{
		erase(node_head_->next);
	}

	void pop_back()
	{
		erase(node_tail_->prev);
	}

	iterator insert_after(iterator pos, const T& value)
	{
		Node* node = static_cast<Node*>(pos);

		if (node == nullptr || node == node_tail_) {
			throw INVALID_POS;
		}

		Node* next_node = node->next;	

		Node* new_node = new Node;
		new_node->data = value;

		next_node->prev = new_node;
		new_node->next = next_node;

		new_node->prev = node;
		node->next = new_node;

		size_++;

		return static_cast<iterator>(new_node);
	}

	iterator insert_before(iterator pos, const T& value)
	{
		Node* node = static_cast<Node*>(pos);

		if (node == nullptr || node == node_head_) {
			throw INVALID_POS;
		}

		Node* prev_node = node->prev;

		Node* new_node = new Node;
		new_node->data = value;

		prev_node->next = new_node;
		new_node->prev = prev_node;

		new_node->next = node;
		node->prev = new_node;

		size_++;

		return static_cast<iterator>(new_node);
	}

	void erase(iterator pos)
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}
		
		Node* node = static_cast<Node*>(pos);

		if (node == nullptr || node == node_head_ || node == node_tail_) {
			throw INVALID_POS;
		}

		Node* prev_node = node->prev;
		Node* next_node = node->next;

		prev_node->next = next_node;
		next_node->prev = prev_node;

		delete node;

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

	iterator next(iterator pos) const
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		Node* node = static_cast<Node*>(pos);

		if (node == nullptr || node == node_head_ || node == node_tail_) {
			throw INVALID_POS;
		}

		if (node->next == node_tail_) {
			return nullptr;
		}

		return static_cast<iterator>(node->next);
	}

	iterator prev(iterator pos)
	{
		if (size_ <= 0) {
			throw EMPTY_LIST;
		}

		Node* node = static_cast<Node*>(pos);

		if (node == nullptr || node == node_head_ || node == node_tail_) {
			throw INVALID_POS;
		}

		if (node->prev == node_head_) {
			return nullptr;
		}

		return static_cast<iterator>(node->prev);
	}


	/**
		Lookup
	**/

	iterator find(const T& value, iterator start_pos) const
	{
		if (empty())
			return nullptr;

		Node* node = static_cast<Node*>(start_pos);
		if (node == node_head_ || node == node_tail_) {
			return nullptr;
		}			

		iterator it = start_pos == nullptr ? begin() : start_pos;
		do {
			if (value == at(it))
				return it;

			it = next(it);

		} while (it != nullptr);

		return nullptr;
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
		int n = pos;
		for (int i = 1; i < n; i++) {
			rt = rt->next;
		}

		return static_cast<iterator>(rt);
	}

protected:
	Node* node_head_;
	Node* node_tail_;
	int size_;
};

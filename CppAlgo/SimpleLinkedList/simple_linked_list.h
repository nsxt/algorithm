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

	T delete_next(POS pos);

	POS insert_next(POS pos, const T& newElem);

	void remove_all();

	bool is_empty() const;

	int get_count() const;

	bool is_valid(POS pos) const;


	/*
		head operation
	*/

	POS add_head(const T& newElem);

	T remove_head();

	T& get_head();

	T get_next() const;


	/*
		traverse
	*/

	POS get_head_position() const;

	T& get_next(POS& pos);

	T get_next(POS& pos) const;


	/*
		getter / setter
	*/

	T& get_at(POS pos);
	T get_at(POS pos) const;
	void set_at(POS pos, const T& newElem);


	/*
		find
	*/

	POS find(const T& searchVal, POS startAfter = 0) const;

	POS find_index(int index) const;


protected:
	struct Node {
		T data;
		Node* next;
		Node() { next = 0; }
	};

	Node* head_node_;
	Node* tail_node_;
	int count_;

	void _init();
	void _clear();
};
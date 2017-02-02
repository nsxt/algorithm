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

		// 단방향 링크드 리스트이므로 입력으로 주어진 노드의 다음 노드를 삭제
		// Delete operation of node
		Node* del_node = node->next;
		node->next = del_node->next;

		// 삭제된 노드의 값을 리턴
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
		// remove_head 를 사용하여 리스트 정리
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
		// insert_next 를 사용하여 추가
		return insert_next(head_node_, new_elem);
	}

	T remove_head()
	{
		// delete_next 를 사용하여 head 노드(선두노드) 데이터 삭제
		return delete_next(head_node_);
	}

	T& get_head() {
		// 리턴 가능한 선두의 유효 데이터가 있는지 검사
		// 노도의 선두 데이터를 리턴 
		if (count_ > 0) {
			return head_node_->next->data;
		
		} else {
			throw EMPTY_LIST;
		}
	}

	T get_next() const
	{
		// 리턴 가능한 선두의 유효 데이터가 있는지 검사
		// 노도의 선두 데이터를 리턴 
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

	// 삽입된 데이터 노드 중 가장 선두 노드를 리턴
	POS get_head_position() const 
	{ 
		return (count_ > 0) ? head_node_->next : nullptr;
	}

	// pos 로 전달받은 노드의 다음 노드를 참조로 설정하고, pos 노드의 값을 리턴한다.
	// 이러한 메소드는 반복구문등에서 노드를 순회할때 사용 될 수 있다.
	// 다음 노드가 없다면, 참조로 전달받은 pos 노드를 null 로 설정한다.
	// 유효하지 않은 (head, tail) 노드가 pos 파라미터 입력으로 전달되면 예외를 발생시킨다.
	T& get_next(POS& pos)
	{
		// 전달 받은 pos 노드가 유효한지 검사
		if (!is_valid(pos)) {
			throw INVALID_POS;
		}

		// 전달 받은 pos 노드 파라미터 타입 캐스팅
		Node* node = static_cast<Node*>(pos);

		// 캐스팅 완료된 node 의 다음 노드 유효성 검사 및 결과 리턴
		if (!is_valid(node->next)) {
			pos = nullptr;

		} else {
			pos = node->next;
		}
		
		return node->data;
	}

	// 노드 데이터의 참조를 리턴하는 get_next() 메소드와 코드 내용은 동일하다.
	T get_next(POS& pos) const
	{
		// 전달 받은 pos 노드가 유효한지 검사
		if (!is_valid(pos)) {
			throw INVALID_POS;
		}

		// 전달 받은 pos 노드 파라미터 타입 캐스팅
		Node* node = static_cast<Node*>(pos);

		// 캐스팅 완료된 node 의 다음 노드 유효성 검사 및 결과 리턴
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

	// 전달 받은 pos 노드의 데이터를 리턴한다.
	// 유효하지 않은 노드일 경우 예외를 발생한다.
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

	// 노드 데이터의 참조를 리턴하는 get_at() 메소드와 동일하다.
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

	// new_elem 으로 pos 노드의 값을 설정함.
	// 유효하지 않은 노드일 경우 예외를 발생함.
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

	// start_node 를 시작으로 search_val 값과 일치하는 데이터를 가진 노드가 있는지 검색하고,
	// 검색 결과 찾은 노드를 리턴한다.
	// 메소드 호출 시 start_node 를 생략 했을때는 head 부터 검색을 시작한다.
	// 입력으로 주어진 노드가 유효하지 않을 경우 head 부터 검색을 시작하기때문에 예외 발생은 없다.
	// 리스트가 비어 있을 경우에는 nullptr 이 리턴된다.
	// 주의 : get_at(), get_next() 의해 예외가 발생 할 수 있다.
	// 예외가 발생 할 수 있는 경우는 전혀 관계없는 노드의 포인터 주소가 전달되면 발생할 수 있는데...
	// 전혀 관계 없는지를 void* 를 정적 캐스팅 하면 알수 있나??? 
	// void* 는 결국 타입에 안전하지 않다는 결론이구나...
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

	// 리스트가 연속된 메모리에 존재하지는 않지만 각 연결이 순차적으로 되어있으므로,
	// 간접적으로 인덱스를 통한 노드 획득 기능을 지원한다.
	POS find_index(int index) const
	{
		// 전달된 index 가 유효범위에 있는지 검사
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
		// head, tail 노드 생성
		head_node_ = new Node;
		tail_node_ = new Node;

		// head, tail 노드 초기화
		head_node_->next = tail_node_;
		tail_node_->next = tail_node_;

		// count 초기화
		count_ = 0;
	}
	

	void _clear()
	{
		// 기존 노드 모두 삭제
		remove_all();

		// head, tail 초기화
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
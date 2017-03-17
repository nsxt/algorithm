#pragma once
#include "../SimpleLinkedList/simple_linked_list.h"
#include "../ListStack/list_stack.h"
#include "../ListQueue/list_queue.h"

/*
	List Graph Algorithm
*/
template<class VERTEX> class ListGraph
{
public:
	typedef long EDGE;

	struct Adj {
		VERTEX vertex;
		EDGE weight;
		bool operator == (const Adj& other) const { return vertex == other.vertex; }
		Adj(const VERTEX& v, EDGE w = 1) { vertex = v; weight = w; }
		Adj() {}
	};

	struct Item {
		VERTEX vertex;
		SimpleLinkedList<Adj> list;
	};

public:
	ListGraph(int size) 
	{
		vertices_ = new Item[size];
		size_ = size;
		count_ = 0;
	}

	~ListGraph()
	{
		delete[] vertices_;
	}

public:
	bool add_edge(const VERTEX& v1, const VERTEX& v2, EDGE w)
	{
		long iv1, iv2;

		iv1 = _find_vertex(v1);
		if (iv1 < 0) {
			iv1 = _add_vertex(v1);
			if (iv1 < 0)
				return false;
		}

		iv2 = _find_vertex(v2);
		if (iv2 < 0) {
			iv2 = _add_vertex(v2);
			if (iv2 < 0)
				return false;
		}

		vertices_[iv1].list.push_front(Adj(v2, w));
		vertices_[iv2].list.push_front(Adj(v1, w));

		return true;
	}

	virtual void visit(const VERTEX& v) {}

	virtual void visit_edge(const VERTEX& v1, const VERTEX& v2) {}

	void dfs() 
	{
		bool* visited = new bool[count_];
		for (long i = 0; i < count_; i++)
			visited[i] = false;

		for (long i = 0; i < count_; i++)
			if (!visited[i])
				_dfs(i, visited);

		delete[] visited;
	}

	void dfs_nr() 
	{
		long i, j;
		ListStack<long> stack;
		
		bool* visited = new bool[count_];
		for (i = 0; i < count_; i++)
			visited[i] = false;

		for (i = 0; i < count_; i++) {
			if (!visited[i]) {
				
				stack.push(i);
				visited[i] = true;

				while (!stack.empty()) {
					j = stack.pop();
					visit(vertices_[j].vertex);

					SimpleLinkedList<Adj>::iterator it = vertices_[j].list.begin();
					while (it) {
						Adj adj = vertices_[j].list.at(it);
						it = vertices_[j].list.next(it);

						int k = _find_vertex(adj.vertex);
						if (!visited[k]) {
							stack.push(k);
							visited[k] = true;
						}
					}
				}
			}
		}
		
		delete[] visited;
	}

	void bfs() 
	{
		long i, j;
		ListQueue<long> queue;

		bool* visited = new bool[count_];
		for (i = 0; i < count_; i++)
			visited[i] = false;
		
		for (i = 0; i < count_; i++) {
			if (!visited[i]) {
				queue.push(i);
				visited[i] = true;

				while (!queue.empty()) {
					j = queue.front();
					queue.pop();

					visit(vertices_[j].vertex);

					SimpleLinkedList<Adj>::iterator it = vertices_[j].list.begin();
					while (it) {
						Adj adj = vertices_[j].list.at(it);
						it = vertices_[j].list.next(it);

						int k = _find_vertex(adj.vertex);
						if (!visited[k]) {
							queue.push(k);
							visited[k] = true;
						}
					}					
				}
			}
		}

		delete[] visited;
	}

	long count_components()
	{
		long count = 0;
		long i, j;
		ListStack<long> stack;
		bool* visited = new bool[count_];

		for (i = 0; i < count_; i++)
			visited[i] = false;

		for (i = 0; i < count_; i++) {
			if (!visited[i]) {
				count++;

				stack.push(i);
				visited[i] = true;

				while (!stack.empty()) {
					
					j = stack.pop();

					SimpleLinkedList<Adj>::iterator it = vertices_[j].list.begin();
					while (it) {
						Adj adj = vertices_[j].list.at(it);
						it = vertices_[j].list.next(it);
						int k = _find_vertex(adj.vertex);
						if (!visited[k]) {
							stack.push(k);
							visited[k] = true;
						}
					}					
				}
			}
		}
		delete[] visited;

		return count;
	}

	void find_ap(SimpleLinkedList<VERTEX>& ap_list)
	{
		long* porder = new long[count_];	// 방문순서 기록
		long son_of_root = 0;

		std::memset(porder, 0, count_ * sizeof(long));

		_find_ap(0, 1, ap_list, porder, son_of_root);
		delete[] porder;

		if (son_of_root > 1)
			ap_list.push_front(vertices_[0].vertex);
	}

protected:
	long _find_vertex(const VERTEX& v)
	{
		for (long i = 0; i < count_; i++) {
			if (vertices_[i].vertex == v)
				return i;
		}
		
		return -1;
	}

	long _add_vertex(const VERTEX& v) 
	{
		if (count_ >= size_)
			return -1;

		vertices_[count_].vertex = v;

		return count_++;
	}

	void _dfs(long i, bool* visited) 
	{
		visited[i] = true;
		visit(vertices_[i].vertex);

		SimpleLinkedList<Adj>::iterator it = vertices_[i].list.begin();
		while (it) {
			Adj adj = vertices_[i].list.at(it);
			it = vertices_[i].list.next(it);

			int k = _find_vertex(adj.vertex);
			if (!visited[k]) {
				_dfs(k, visited);
			}
		}
	}

	long _find_ap(long i, long order, SimpleLinkedList<VERTEX>& ap_list, long* porder, long& son_of_root)
	{
		long min, m;

		porder[i] = min = ++order;

		SimpleLinkedList<VERTEX>::iterator it = vertices_[i].list.begin();
		while (it) {
			Adj adj = vertices_[i].list.at(it);
			it = vertices_[i].list.next(it);

			int k = _find_vertex(adj.vertex);
			if (porder[k] == 0) {	// Tree Edge
				if (i == 0)
					son_of_root++;

				// DFS 탐색
				m = _find_ap(k, order, ap_list, porder, son_of_root);

				if (m < min)
					min = m;

				// Articulation Points
				if (m >= porder[i] && i != 0) {
					if (!ap_list.find(vertices_[i].vertex))
						ap_list.push_front(vertices_[i].vertex);
				}
			}
			else {	// Non-Tree Edge
				if (porder[k] < min)
					min = porder[k];
			}
		}

		return min;
	}



protected:
	Item* vertices_;
	long size_;
	long count_;
};


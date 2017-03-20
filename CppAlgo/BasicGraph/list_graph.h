#pragma once
#include "../SimpleLinkedList/simple_linked_list.h"
#include "../ListStack/list_stack.h"
#include "../ListQueue/list_queue.h"
#include "edge_heap.h"
#include "set.h"

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


	EDGE mcst_pfs()
	{
		long i, j;
		EdgeHeap<char> pq;
		EdgeHeap<char>::Pair p;
		EDGE sum = 0;
		bool* visited = new bool[count_];

		for (i = 0; i < count_; i++)
			visited[i] = false;

		for (i = 0; i < count_; i++) {
			
			if (!visited[i]) {				
				pq.insert(vertices_[i].vertex, vertices_[i].vertex, 0);
				visited[i] = true;

				while (!pq.empty()) {
					p = pq.extract();

					if (p.v1 != p.v2) {
						visit_edge(p.v1, p.v2);
						sum += -p.w;
					}
					j = _find_vertex(p.v2);

					SimpleLinkedList<Adj>::iterator it = vertices_[j].list.begin();
					while (it) {
						Adj adj = vertices_[j].list.at(it);
						it = vertices_[j].list.next(it);

						int k = _find_vertex(adj.vertex);
						if (!visited[k]) {
							pq.insert(vertices_[j].vertex, adj.vertex, -adj.weight);
							visited[k] = true;
						}
						else {
							pq.update(vertices_[j].vertex, adj.vertex, -adj.weight);
						}
					}
				}
			}
		}

		delete[] visited;
		return sum;
	}


	EDGE mcst_kruskal()
	{
		EdgeHeap<char> pq;
		Set<char> set;
		int i;
		EDGE sum = 0;
		int edge_count = 0;

		// 모든 간선을 우선순위큐(힙)에 삽입
		for (i = 0; i < count_; i++) {
			SimpleLinkedList<Adj>::iterator it = vertices_[i].list.begin();
			while (it) {
				Adj adj = vertices_[i].list.at(it);
				it = vertices_[i].list.next(it);

				if (_find_vertex(adj.vertex) > i) // 간선의 중복 검사
					pq.insert(vertices_[i].vertex, adj.vertex, -adj.weight);
			}
		}

		// Kruskal 알고리즘 실행 : MCST 의 간선수 = 정점수 - 1
		while (!pq.empty() && edge_count < count_ - 1) {

			EdgeHeap<char>::Pair p = pq.extract();
			
			int i1 = set.find(p.v1);
			if (i1 < 0)
				i1 = set.add_set(p.v1);

			int i2 = set.find(p.v2);
			if (i2 < 0)
				i2 = set.add_set(p.v2);

			// Cycle 검사
			if (i1 >= 0 && i2 >= 0 && i1 != i2) {
				visit_edge(p.v1, p.v2);
				edge_count++;
				sum += -p.w;
				set.union_by_index(i1, i2);
			}
		}

		return sum;
	}


	void shortest_path_pfs(const VERTEX& start)
	{
		long i, j;
		EdgeHeap<char> pq;
		EdgeHeap<char>::Pair p;
		bool* visited = new bool[count_];

		for (i = 0; i < count_; i++)
			visited[i] = false;

		i = _find_vertex(start);
		if (i < 0)
			return;

		// shortest path 는 연결된 요소에서만 가능. 최상위 루프는 제외
		pq.insert(vertices_[i].vertex, vertices_[i].vertex, 0);
		visited[i] = true;

		while (!pq.empty()) {
			
			p = pq.extract();

			if (p.v1 != p.v2)
				visit_edge(p.v1, p.v2);

			j = _find_vertex(p.v2);

			SimpleLinkedList<Adj>::iterator it = vertices_[j].list.begin();
			while (it) {
				Adj adj = vertices_[j].list.at(it);
				it = vertices_[j].list.next(it);
				
				int k = _find_vertex(adj.vertex);
				if (!visited[k]) {
					pq.insert(vertices_[j].vertex, adj.vertex, p.w - adj.weight);
					visited[k] = true;
				}
				else {
					pq.update(vertices_[j].vertex, adj.vertex, p.w - adj.weight);
				}
			}
		}
		delete[] visited;
	}


	void shortest_path_dijkstra(const VERTEX& start)
	{
		long i;
		long x, y;
		long count = 0;
		long s = _find_vertex(start);
		EDGE* distance = new EDGE[count_];
		bool* visited = new bool[count_];
		int* parent = new int[count_];

		for (i = 0; i < count_; i++) {
			visited[i] = false;
			distance[i] = 0;		// 0 means infinite

			if (i != s)
				parent[i] = s;
			else
				parent[i] = -1;
		}

		// fill distance array
		SimpleLinkedList<Adj>::iterator it = vertices_[s].list.begin();
		while (it) {
			Adj adj = vertices_[s].list.at(it);
			it = vertices_[s].list.next(it);
			distance[_find_vertex(adj.vertex)] = adj.weight;
		}

		visited[s] = true;
		count++;

		while (count < count_) {
			x = 0;

			while (visited[x])
				x++;

			for (i = x; i < count_; i++) {
				if (!visited[i] && distance[i] > 0 && distance[i] < distance[x])
					x = i;
			}

			visited[x] = true;
			count++;

			SimpleLinkedList<Adj>::iterator it = vertices_[x].list.begin();
			while (it) {
				Adj adj = vertices_[x].list.at(it);
				it = vertices_[x].list.next(it);

				y = _find_vertex(adj.vertex);
				
				if (visited[y])
					continue;

				EDGE d = distance[x] + adj.weight;
				if (distance[y] == 0 || d < distance[y]) {
					distance[y] = d;
					parent[y] = x;
				}
			}
		}

		// visit edge
		for (i = 0; i < count_; i++) {
			if (parent[i] >= 0)
				visit_edge(vertices_[parent[i]].vertex, vertices_[i].vertex);
		}

		delete[] distance;
		delete[] visited;
		delete[] parent;
	}

	
	void reach_dfs(const VERTEX& start)
	{
		long i, j;
		ListStack<long> stack;
		bool* visited = new bool[count_];

		for (i = 0; i < count_; i++)
			visited[i] = false;

		i = _find_vertex(start);
		if (i < 0)
			return;

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
		delete[] visited;
	}


	void strong_connect()
	{
		int i;
		ListStack<long> stack;
		long* porder = new long[count_];

		for (i = 0; i < count_; i++) {
			porder[i] = 0;
		}

		for (i = 0; i < count_; i++) {
			if (porder[i] == 0)
				_strong_connect(i, 0, porder, stack);
		}

		delete[] porder;
	}

	int _strong_connect(long i, long order, long* porder, ListStack<long>& stack)
	{
		int m, min;
		int k;
		bool cycle;

		porder[i] = min = ++order;
		stack.push(i);

		SimpleLinkedList<Adj>::iterator it = vertices_[i].list.begin();
		while (it) {
			Adj adj = vertices_[i].list.at(it);
			it = vertices_[i].list.next(it);

			k = _find_vertex(adj.vertex);
			if (porder[k] == 0)
				m = _strong_connect(k, order, porder, stack);
			else
				m = porder[k];

			if (m < min)
				min = m;
		}

		if (min == porder[i]) {
			cycle = false;

			while ((k = stack.pop()) != i) {
				visit(vertices_[k].vertex);
				porder[k] = count_ + 1;
				cycle = true;
			}

			if (cycle)
				visit(vertices_[k].vertex);
		}

		return min;
	}


	void topological_sort()
	{
		int i;
		ListQueue<int> queue;

		int* indegree = new int[count_];
		for (i = 0; i < count_; i++)
			indegree[i] = 0;

		for (i = 0; i < count_; i++) {
			
			SimpleLinkedList<Adj>::iterator it = vertices_[i].list.begin();
			while (it) {
				Adj adj = vertices_[i].list.at(it);
				it = vertices_[i].list.next(it);

				int k = _find_vertex(adj.vertex);
				indegree[k]++;
			}
		}

		for (i = 0; i < count_; i++) {
			if (indegree[i] == 0)
				queue.push(i);
		}

		for (i = 0; i < count_ && !queue.empty(); i++) {

			// 큐가 비면 DAG 가 아니다.
			int j = queue.front();
			queue.pop();

			visit(vertices_[j].vertex);

			SimpleLinkedList<Adj>::iterator it = vertices_[j].list.begin();
			while (it) {
				Adj adj = vertices_[j].list.at(it);
				it = vertices_[j].list.next(it);

				int k = _find_vertex(adj.vertex);
				indegree[k]--;
				if (indegree[k] == 0)
					queue.push(k);
			}
		}

		delete[] indegree;
	}

	void rev_topological_sort()
	{
		int i;
		ListQueue<int> queue;

		int* outdegree = new int[count_];
		for (i = 0; i < count_; i++)
			outdegree[i] = 0;

		for (i = 0; i < count_; i++) {
			outdegree[i] = vertices_[i].list.size();
		}

		for (i = 0; i < count_; i++) {
			if (outdegree[i] == 0)
				queue.push(i);
		}

		for (i = 0; i < count_ && !queue.empty(); i++) {

			// 큐가 비면 DAG가 아니다. (순환이 존재)
			int j = queue.front();
			queue.pop();

			visit(vertices_[j].vertex);

			for (int k = 0; k < count_; k++) {
				SimpleLinkedList<Adj>::iterator it = vertices_[k].list.begin();
				while (it) {
					Adj adj = vertices_[k].list.at(it);
					it = vertices_[k].list.next(it);

					if (adj.vertex == vertices_[j].vertex) {
						outdegree[k]--;
						if (outdegree[k] == 0)
							queue.push(k);
					}
				}
			}
		}
		delete[] outdegree;
	}

	void critical_activity()
	{
		int i;
		int* earliest = new int[count_];
		int* latest = new int[count_];

		_critical_activity_forward(earliest);

		int initial = 0;
		for (i = 0; i < count_; i++) {
			if (initial < earliest[i])
				initial = earliest[i];
		}

		_critical_activity_backward(latest, initial);

		for (i = 0; i < count_; i++) {
			SimpleLinkedList<Adj>::iterator it = vertices_[i].list.begin();
			while (it) {
				Adj adj = vertices_[i].list.at(it);
				it = vertices_[i].list.next(it);

				int e = earliest[i];
				int l = latest[_find_vertex(adj.vertex)] - adj.weight;

				if (l == e && adj.weight > 0)
					visit_edge(vertices_[i].vertex, adj.vertex);
			}
		}

		delete[] earliest;
		delete[] latest;
	}

	void _critical_activity_forward(int* earliest)
	{
		int i;
		ListQueue<int> queue;

		int* indegree = new int[count_];
		for (i = 0; i < count_; i++) {
			indegree[i] = 0;
			earliest[i] = 0;
		}

		for (i = 0; i < count_; i++) {
			SimpleLinkedList<Adj>::iterator it = vertices_[i].list.begin();
			while (it) {
				Adj adj = vertices_[i].list.at(it);
				it = vertices_[i].list.next(it);

				int k = _find_vertex(adj.vertex);
				indegree[k]++;
			}
		}

		for (i = 0; i < count_; i++) {
			if (indegree[i] == 0)
				queue.push(i);
		}

		for (i = 0; i < count_ && !queue.empty(); i++) {

			// 큐가 비면 DAG가 아니다. (순환이 존재)
			int j = queue.front();
			queue.pop();

			SimpleLinkedList<Adj>::iterator it = vertices_[j].list.begin();
			while (it) {
				Adj adj = vertices_[j].list.at(it);
				it = vertices_[j].list.next(it);

				int k = _find_vertex(adj.vertex);
				indegree[k]--;
				if (indegree[k] == 0)
					queue.push(k);

				if (earliest[k] < earliest[j] + adj.weight)
					earliest[k] = earliest[j] + adj.weight;
			}
		}

		delete[] indegree;
	}

	void _critical_activity_backward(int* latest, int initial)
	{
		int i;
		ListQueue<int> queue;

		int* outdegree = new int[count_];
		for (i = 0; i < count_; i++) {
			outdegree[i] = 0;
			latest[i] = initial;
		}

		for (i = 0; i < count_; i++) {
			outdegree[i] = vertices_[i].list.size();
		}

		for (i = 0; i < count_; i++) {
			if (outdegree[i] == 0)
				queue.push(i);
		}

		for (i = 0; i < count_ && !queue.empty(); i++) {

			// 큐가 비면 DAG 가 아니다. (순환이 존재)
			int j = queue.front();
			queue.pop();

			for (int k = 0; k < count_; k++) {
				SimpleLinkedList<Adj>::iterator it = vertices_[k].list.begin();
				while (it) {
					Adj adj = vertices_[k].list.at(it);
					it = vertices_[k].list.next(it);

					if (adj.vertex == vertices_[j].vertex) {
						outdegree[k]--;

						if (outdegree[k] == 0)
							queue.push(k);

						if (latest[k] > latest[j] - adj.weight)
							latest[k] = latest[j] - adj.weight;
					}
				}
			}
		}
		delete[] outdegree;
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


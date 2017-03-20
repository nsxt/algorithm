#pragma once
#include <cstring>
#include "../ListStack/list_stack.h"
#include "../ListQueue/list_queue.h"

template<class VERTEX> class ArrayGraph
{
public:
	typedef long EDGE;

public:
	ArrayGraph(int size = 100)
	{
		vertices_ = new VERTEX[size];
		edges_ = new EDGE[size * size];

		std::memset(edges_, 0, size * size * sizeof(long));

		size_ = size;
		count_ = 0;
	}

	~ArrayGraph()
	{
		delete[] vertices_;
		delete[] edges_;
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

		// 인접행렬(Adjacency Matrix)법으로 무향 Edge 그래프
		_set_edge_by_index(iv1, iv2, w);
		_set_edge_by_index(iv2, iv1, w);

		return true;					
	}

	virtual void visit(const VERTEX& v) {}

	virtual void visit_edge(const VERTEX& v1, const VERTEX& v2) {}

	void dfs()
	{
		int i;
		bool* visited = new bool[count_];
		
		for (i = 0; i < count_; i++)
			visited[i] = false;

		for (i = 0; i < count_; i++)
			if (!visited[i])
				_dfs(i, visited);

		delete[] visited;
	}

	void dfs_nr()
	{
		long i, j, k;
		ListStack<long> stack;
		bool* visited = new bool[count_];

		for (i = 0; i < count_; i++)
			visited[i] = false;

		for (i = 0; i < count_; i++) {

			if (!visited[i]) {
			
				stack.push(i);
				visited[i] = true;

				while (!stack.empty()) {					
					k = stack.pop();
					visit(vertices_[k]);

					for (j = 0; j < count_; j++) {
						if (_get_edge_by_index(k, j) != 0 && !visited[j]) {
							stack.push(j);
							visited[j] = true;
						}
					}
				}
			}
		}

		delete[] visited;
	}

	void bfs()
	{
		long i, j, k;
		ListQueue<long> queue;
		bool* visited = new bool[count_];

		for (i = 0; i < count_; i++)
			visited[i] = false;

		for (i = 0; i < count_; i++) {
			if (!visited[i]) {

				queue.push(i);
				visited[i] = true;

				while (!queue.empty()) {
					k = queue.front();
					queue.pop();

					visit(vertices_[k]);

					for (j = 0; j < count_; j++) {
						if (_get_edge_by_index(k, j) != 0 && !visited[j]) {
							queue.push(j);
							visited[j] = true;
						}
					}
				}
			}
		}

		delete[] visited;	
	}

	// 그래프의 연결 요소 카운팅
	long count_components()
	{
		long count = 0;
		long i, j, k;
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
					k = stack.pop();
					for (j = 0; j < count_; j++)
						if (_get_edge_by_index(k, j) != 0 && !visited[j]) {
							stack.push(j);
							visited[j] = true;
						}
				}
			}
		}

		delete[] visited;

		return count;
	}
	
	void find_ap(SimpleLinkedList<VERTEX>& ap_list)
	{
		long* porder = new long[count_];
		long son_of_root = 0;

		std::memset(porder, 0, count_ * sizeof(long));

		_find_ap(0, 1, ap_list, porder, son_of_root);
		delete[] porder;

		if (son_of_root > 1)
			ap_list.push_front(vertices_[0]);
	}

	EDGE mcst_pfs()
	{
		long i, j, k;
		EdgeHeap<char> pq;
		EdgeHeap<char>::Pair p;
		EDGE sum = 0;
		bool* visited = new bool[count_];

		for (i = 0; i < count_; i++)
			visited[i] = false;

		for (i = 0; i < count_; i++) {
			if (!visited[i]) {
				pq.insert(vertices_[i], vertices_[i], 0);
				visited[i] = true;

				while (!pq.empty()) {
					p = pq.extract();

					if (p.v1 != p.v2) {
						visit_edge(p.v1, p.v2);
						sum += -p.w;
					}
					k = _find_vertex(p.v2);

					for (j = 0; j < count_; j++) {
						if (_get_edge_by_index(k, j) != 0) {
							if (!visited[j]) {
								pq.insert(vertices_[k], vertices_[j], -_get_edge_by_index(k, j));
								visited[j] = true;
							}
							else {
								pq.update(vertices_[k], vertices_[j], -_get_edge_by_index(k, j));
							}
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
		int i, j;
		EDGE sum = 0;
		int edge_count = 0;

		// insert  all edges to heap
		for (i = 0; i < count_; i++) {
			for (j = i + 1; j < count_; j++) {
				if (_get_edge_by_index(i, j)) {
					pq.insert(vertices_[i], vertices_[j], -_get_edge_by_index(i, j));
				}
			}
		}

		// mcst 의 간선수는 정점수 - 1
		while (!pq.empty() && edge_count < count_ - 1) {
			
			EdgeHeap<char>::Pair p = pq.extract();

			int i1 = set.find(p.v1);
			if (i1 < 0)
				i1 = set.add_set(p.v1);

			int i2 = set.find(p.v2);
			if (i2 < 0)
				i2 = set.add_set(p.v2);

			// 회로가 아니라면
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
		long i, j, k;
		EdgeHeap<char> pq;
		EdgeHeap<char>::Pair p;
		EDGE sum = 0;
		bool* visited = new bool[count_];

		for (i = 0; i < count_; i++)
			visited[i] = false;

		i = _find_vertex(start);
		
		pq.insert(vertices_[i], vertices_[i], 0);
		visited[i] = true;

		while (!pq.empty()) {
			p = pq.extract();

			if (p.v1 != p.v2) {
				visit_edge(p.v1, p.v2);
				sum += -p.w;
			}
			k = _find_vertex(p.v2);

			for (j = 0; j < count_; j++) {
				if (_get_edge_by_index(k, j) != 0) {
					if (!visited[j]) {
						pq.insert(vertices_[k], vertices_[j], p.w - _get_edge_by_index(k, j));
						visited[j] = true;
					}
					else {
						pq.update(vertices_[k], vertices_[j], p.w - _get_edge_by_index(k, j));
					}
				}
			}
		}

		delete[] visited;
	}

	void shortest_path_dijkstra(const VERTEX& start)
	{
		int i;
		int count = 0;
		int x, y;
		int s = _find_vertex(start);
		bool* visited = new bool[count_];
		EDGE* distance = new EDGE[count_];
		int* parent = new int[count_];

		for (i = 0; i < count_; i++) {
			visited[i] = false;
			distance[i] = _get_edge_by_index(s, i);

			if (i != s)
				parent[i] = s;
			else
				parent[i] = -1;
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

			for (y = 0; y < count_; y++) {
				if (x == y || _get_edge_by_index(x, y) == 0 || visited[y])
					continue;

				EDGE d = distance[x] + _get_edge_by_index(x, y);
				if (distance[y] == 0 || d < distance[y]) {
					distance[y] = d;
					parent[y] = x;
				}
			}
		}

		// visit edge
		for (i = 0; i < count_; i++) {
			if (parent[i] >= 0)
				visit_edge(vertices_[parent[i]], vertices_[i]);
		}

		delete[] visited;
		delete[] distance;
		delete[] parent;
	}


protected:
	long _find_vertex(const VERTEX& v)
	{
		for (int i = 0; i < count_; i++) {
			if (vertices_[i] == v)
				return i;
		}

		return -1;
	}

	long _add_vertex(const VERTEX& v)
	{
		if (count_ >= size_)
			return -1;

		vertices_[count_] = v;

		return count_++;
	}

	EDGE _get_edge_by_index(long i, long j)
	{
		return edges_[i * size_ + j];
	}

	bool _set_edge_by_index(long i, long j, EDGE w)
	{
		if (i < 0 || i >= count_ || j < 0 || j >= count_)
			return false;

		edges_[i * size_ + j] = w;

		return true;
	}

	void _dfs(long i, bool* visited)
	{		
		visited[i] = true;
		visit(vertices_[i]);
		
		// 재귀 호출때문에 잠시 생각이 많았으나 결구 간선 테이블(V * V) 을 번갈아(i, j) 가면서 확인하고,
		// 정점 방문정보는 단일하게 v[V] 처리한다.		
		for (int j = 0; j < count_; j++) {
			if (_get_edge_by_index(i, j) != 0 && !visited[j])
				_dfs(j, visited);
		}
	}

	long _find_ap(long i, long order, SimpleLinkedList<VERTEX>& ap_list, long* porder, long& son_of_root)
	{
		long min, m;

		porder[i] = min = ++order;

		for (int j = 0; j < count_; j++) {
			if (_get_edge_by_index(i, j) != 0) {

				// Tree-Edge
				if (porder[j] == 0) {

					// Root 의 자식을 카운트
					if (i == 0)
						son_of_root++;

					// DFS 탐색
					m = _find_ap(j, order, ap_list, porder, son_of_root);

					if (m < min)
						min = m;

					// Articulation Points
					if (m >= porder[i] && i != 0) {
						if (!ap_list.find(vertices_[i]))
							ap_list.push_front(vertices_[i]);
					}
				}
				// Non-Tree Edge
				else {
					if (porder[j] < min)
						min = porder[j];
				}
			}
		}

		return min;
	}

protected:
	VERTEX* vertices_;
	EDGE* edges_;
	long size_;
	long count_;
};
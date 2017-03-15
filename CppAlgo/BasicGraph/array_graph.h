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

	virtual void visit(const VERTEX& v)
	{

	}

	virtual void visit_edge(const VERTEX& v1, const VERTEX& v2)
	{

	}

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

protected:
	VERTEX* vertices_;
	EDGE* edges_;
	long size_;
	long count_;
};
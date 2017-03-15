// BasicGraph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <chrono>
#include <string>
#include "array_graph.h"

template ArrayGraph<char>;

class ACharGraph : public ArrayGraph<char>
{
public:
	ACharGraph(int size = 100) : ArrayGraph<char>(size) {}
	void visit(const char& v) override { std::cout << v << " "; }
};

void ag_search()
{
	printf("Array Graph Test\n");

	ACharGraph ag;
	ag.add_edge('A', 'B', 1);
	ag.add_edge('A', 'C', 1);
	ag.add_edge('A', 'D', 1);
	ag.add_edge('B', 'E', 1);
	ag.add_edge('C', 'F', 1);
	ag.add_edge('D', 'H', 1);
	ag.add_edge('E', 'F', 1);
	ag.add_edge('F', 'H', 1);
	ag.add_edge('E', 'G', 1);
	ag.add_edge('G', 'I', 1);
	ag.add_edge('H', 'I', 1);
	ag.add_edge('J', 'K', 1);
	ag.add_edge('J', 'L', 1);
	ag.add_edge('M', 'N', 1);
	ag.add_edge('M', 'O', 1);
	ag.add_edge('N', 'P', 1);
	ag.add_edge('N', 'Q', 1);
	ag.add_edge('O', 'Q', 1);

	printf("Depth First Search = ");
	ag.dfs();
	printf("\n");

	printf("Depth First Search (nr) = ");
	ag.dfs_nr();
	printf("\n");

	printf("Breadth First Search = ");
	ag.bfs();
	printf("\n");
}

int main()
{
	ag_search();

    return 0;
}


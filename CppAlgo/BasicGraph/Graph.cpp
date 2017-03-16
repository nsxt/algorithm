// BasicGraph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <chrono>
#include <string>
#include "array_graph.h"
#include "list_graph.h"

template ArrayGraph<char>;
template ListGraph<char>;

class ACharGraph : public ArrayGraph<char>
{
public:
	ACharGraph(int size = 100) : ArrayGraph<char>(size) {}
	void visit(const char& v) override { std::cout << v << " "; }
};

class LCharGraph : public ListGraph<char>
{
public:
	LCharGraph(int size = 100) : ListGraph<char>(size) {}
	void visit(const char& v) override { std::cout << v << " "; }
};

void lg_search()
{
	printf("List Graph Test\n");

	LCharGraph lg;
	lg.add_edge('A', 'B', 1);
	lg.add_edge('A', 'C', 1);
	lg.add_edge('A', 'D', 1);
	lg.add_edge('B', 'E', 1);
	lg.add_edge('C', 'F', 1);
	lg.add_edge('D', 'H', 1);
	lg.add_edge('E', 'F', 1);
	lg.add_edge('F', 'H', 1);
	lg.add_edge('E', 'G', 1);
	lg.add_edge('G', 'I', 1);
	lg.add_edge('H', 'I', 1);
	lg.add_edge('J', 'K', 1);
	lg.add_edge('J', 'L', 1);
	lg.add_edge('M', 'N', 1);
	lg.add_edge('M', 'O', 1);
	lg.add_edge('N', 'P', 1);
	lg.add_edge('N', 'Q', 1);
	lg.add_edge('O', 'Q', 1);

	printf("Depth First Search = ");
	lg.dfs();
	printf("\n");

	printf("Depth First Search (nr) = ");
	lg.dfs_nr();
	printf("\n");

	printf("Breadth First Search = ");
	lg.bfs();
	printf("\n");


	lg.add_edge('D', 'J', 1);
	lg.add_edge('J', 'M', 1);
	printf("Articulation Point is ");
	SimpleLinkedList<char> aplist;
	lg.find_ap(aplist);

	SimpleLinkedList<int>::iterator it = aplist.begin();
	while (it) {
		std::cout << aplist.at(it) << " ";
		it = aplist.next(it);
	}

	std::cout << std::endl;
}

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

	printf("Count of Connected Components = %d\n", ag.count_components());

	ag.add_edge('D', 'J', 1);
	ag.add_edge('J', 'M', 1);
	printf("Articulation Point is ");
	SimpleLinkedList<char> aplist;
	ag.find_ap(aplist);

	SimpleLinkedList<int>::iterator it = aplist.begin();
	while (it) {
		std::cout << aplist.at(it) << " ";
		it = aplist.next(it);
	}

	std::cout << std::endl;
}

int main()
{
	ag_search();

	std::cout << "\n\n";

	lg_search();

    return 0;
}


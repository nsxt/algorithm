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
	void visit_edge(const char& v1, const char& v2) { std::cout << v1 << v2; }
};

class LCharGraph : public ListGraph<char>
{
public:
	LCharGraph(int size = 100) : ListGraph<char>(size) {}
	void visit(const char& v) override { std::cout << v << " "; }
	void visit_edge(const char& v1, const char& v2) { std::cout << v1 << v2; }
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


void lg_weighted()
{
	printf("Weighted ListGraph\n");
	LCharGraph lg;
	lg.add_edge('A', 'B', 4);
	lg.add_edge('A', 'C', 1);
	lg.add_edge('A', 'D', 2);
	lg.add_edge('A', 'E', 3);
	lg.add_edge('B', 'F', 4);
	lg.add_edge('C', 'D', 2);
	lg.add_edge('D', 'F', 4);
	lg.add_edge('D', 'G', 4);
	lg.add_edge('E', 'F', 4);
	lg.add_edge('F', 'J', 2);
	lg.add_edge('F', 'K', 4);
	lg.add_edge('G', 'H', 3);
	lg.add_edge('G', 'I', 3);
	lg.add_edge('G', 'J', 4);
	lg.add_edge('H', 'I', 2);
	lg.add_edge('I', 'J', 2);
	lg.add_edge('J', 'K', 1);

	printf("MCST: Priority First Search = ");
	LCharGraph::EDGE w = lg.mcst_pfs();
	printf("  (%d)\n", w);

	printf("MCST: Kruskal Algorithm = ");
	w = lg.mcst_kruskal();
	printf("  (%d)\n", w);

	printf("Shortest Path: Priority First Search = ");
	lg.shortest_path_pfs('A');
	printf("\n");

	printf("Shortest Path: Dijkstra = ");
	lg.shortest_path_dijkstra('A');
	printf("\n");

}

void ag_weighted()
{
	printf("Weighted ArrayGraph\n");
	ACharGraph ag;
	ag.add_edge('A', 'B', 4);
	ag.add_edge('A', 'C', 1);
	ag.add_edge('A', 'D', 2);
	ag.add_edge('A', 'E', 3);
	ag.add_edge('B', 'F', 4);
	ag.add_edge('C', 'D', 2);
	ag.add_edge('D', 'F', 4);
	ag.add_edge('D', 'G', 4);
	ag.add_edge('E', 'F', 4);
	ag.add_edge('F', 'J', 2);
	ag.add_edge('F', 'K', 4);
	ag.add_edge('G', 'H', 3);
	ag.add_edge('G', 'I', 3);
	ag.add_edge('G', 'J', 4);
	ag.add_edge('H', 'I', 2);
	ag.add_edge('I', 'J', 2);
	ag.add_edge('J', 'K', 1);

	printf("Priority First Search = ");
	ACharGraph::EDGE w = ag.mcst_pfs();
	printf("  (%d)\n", w);

	printf("Kruskal Algorithm = ");
	w = ag.mcst_kruskal();
	printf("  (%d)\n", w);

	printf("Shortest Path: Priority First Search = ");
	ag.shortest_path_pfs('A');
	printf("\n");

	printf("Shortest Path: Dijkstra = ");
	ag.shortest_path_dijkstra('A');
	printf("\n");
}


int main()
{
	ag_search();

	std::cout << "\n\n";

	lg_search();

	std::cout << "\n\n";

	ag_weighted();

	std::cout << "\n\n";

	lg_weighted();

    return 0;
}


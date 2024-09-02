#include "graph.hpp"

int main(int argc, char const *argv[]) {

	graph Graph;

	Graph.InsertNode();
	Graph.InsertNode();
	Graph.InsertNode();

	Graph.InsertEdge(0, 1);
	Graph.InsertEdge(0, 2);

	Graph.PrintGraph();

	return 0;
}

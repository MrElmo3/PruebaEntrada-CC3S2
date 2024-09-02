#include "graph.hpp"

int main(int argc, char const *argv[]) {

	//Example of use of the graph class and Dijkstra method

	graph Graph;

	Graph.InsertNode();
	Graph.InsertNode();
	Graph.InsertNode();
	Graph.InsertNode();
	Graph.InsertNode();
	Graph.InsertNode();
	Graph.InsertNode();

	Graph.InsertEdge(0, 1, 1);
	Graph.InsertEdge(0, 5, 2);
	Graph.InsertEdge(1, 2, 3);
	Graph.InsertEdge(1, 3, 4);
	Graph.InsertEdge(2, 4, 5);
	Graph.InsertEdge(3, 4, 4);
	Graph.InsertEdge(3, 6, 3);
	Graph.InsertEdge(4, 6, 2);
	Graph.InsertEdge(5, 6, 1);

	Graph.Dijkstra(0, 6).PrintGraph();

	return 0;
}

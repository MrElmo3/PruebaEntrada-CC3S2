#include <iostream>
#include <queue>
#include <vector>

/*
This class contains all the information of the edge:
the node from which it comes,
the node to which it goes,
the weight of the edge and a pointer to the next edge. 
*/
class edge{

public:
	int from;
	int conectionData;
	int weight;
	edge* nextEdge;

public:
	edge(){};

	edge(int from, int data){
		this->from = from;
		this->conectionData = data;
		this->weight = 0;
		this->nextEdge = nullptr;
	};

	edge(int from, int data, int weight) : edge(from, data){
		this->weight = weight;
	};

};
typedef edge* pEdge;

/*
This class contains all the information of the node:
the ID of the node,
the data of the node,
a pointer to the first edge that comes out of the node,
*/
class node{
public:
	int ID;
	int nodeData;
	edge* conection;
	node* nextNode;

	node(){
		this->conection = nullptr;
	};

	node(int ID) : node(){
		this->ID = ID;
	}

	node(int ID, int data) : node(ID){
		this->nodeData = data;
	};
};
typedef node *pNode;


/*
This class uses the list implementation to create a graph.
*/
class graph{
private:

	//ID of the next node to be inserted
	int nodeID = 0;

	//pointer to the first node of the graph
	pNode head;

	//number of nodes in the graph
	int nodeNumber;

	//number of edges in the graph
	int edgeNumer;

public:

	/*
	Base Graph constructor
	*/
	graph(){
		head=nullptr;
		nodeNumber = 0;
		edgeNumer = 0;
	};
	
	/*
	Graph destructor
	*/
	~graph(){
		
		pNode graphHead, nodeAuxiliar;
		pEdge edgeHead, edgeAuxiliar;
		graphHead = head;
		
		while(graphHead!=nullptr){
			edgeHead = graphHead->conection;
			
			while(edgeHead!=nullptr){
				edgeAuxiliar = edgeHead;
				edgeHead = edgeHead->nextEdge;

				delete edgeAuxiliar;
			}
			
			nodeAuxiliar = graphHead;
			graphHead = graphHead->nextNode;

			delete nodeAuxiliar;
		}
	};
	
	/*
	This method inserts a node into the graph using the next ID info stored in the graph.
	*/
	void InsertNode(){
		pNode newNode;
		newNode = new node(nodeID);
		
		newNode->nextNode = head;
		head = newNode;

		nodeID++;
		nodeNumber++;
	};
	
	/*
	This methos inserts a edge between two nodes in the graph.
	*/
	void InsertEdge(int IDx, int IDy){

		if (IDx < 0 || IDy < 0) {
			std::cout << "Invalid ID" << std::endl;
		return;
		}

		if (IDx == IDy) {
			std::cout << "Can't insert an edge between the same node" << std::endl;
			return;
		}

		if (nodeNumber <= 1) {
			std::cout << "graph is empty or only have 1 Node" << std::endl;
			return;
		}

		pNode graphHead;
		pEdge edgeHead;
		
		pNode nodeX = SearchNodeByID(IDx);
		pNode nodeY = SearchNodeByID(IDy);

		if(nodeX == nullptr || nodeY == nullptr) {
			std::cout << "One or both nodes don't exist" << std::endl;
			return;
		}

		//cheking for X
		edgeHead = nodeX->conection;
		while (edgeHead != nullptr) {
			if (edgeHead->conectionData == IDy) {
				std::cout << "the Edge already exists" << std::endl;
				return;
			}
			edgeHead = edgeHead->nextEdge;
		};

		//Inserting for X
		edgeHead = new edge(IDx, IDy);
		edgeHead->nextEdge = nodeX->conection;
		nodeX->conection = edgeHead;

		//cheking for Y
		edgeHead = nodeY->conection;
		while (edgeHead != nullptr) {
			if (edgeHead->conectionData == IDx) {
				std::cout << "the Edge already exists" << std::endl;
				return;
			}
			edgeHead = edgeHead->nextEdge;
		};

		//Inserting for Y
		edgeHead = new edge(IDy, IDx);
		edgeHead->nextEdge = nodeY->conection;
		nodeX->conection = edgeHead;
		
	};

	/*
	This method inserts a edge between two nodes in the graph with a weight.
	*/
	void InsertEdge(int IDx, int IDy, int npeso){
		InsertEdge(IDx, IDy);
		
		pEdge edgeHead;

		pNode nodeX = SearchNodeByID(IDx);
		pNode nodeY = SearchNodeByID(IDy);

		edgeHead = nodeX->conection;
		while(edgeHead != nullptr){
			if(edgeHead->conectionData == IDy){
				edgeHead->weight = npeso;
				break;
			}
			edgeHead = edgeHead->nextEdge;
		}

		edgeHead = nodeY->conection;
		while(edgeHead != nullptr){
			if(edgeHead->conectionData == IDx){
				edgeHead->weight = npeso;
				break;
			}
			edgeHead = edgeHead->nextEdge;
		}
	};

	/*
	This method searches for a node in the graph by its ID.
	*/
	pNode SearchNodeByID(int IDnode){
		pNode graphHead;
		graphHead = head;

		while(graphHead != nullptr){
			if(graphHead->ID == IDnode)
				return graphHead;
			graphHead = graphHead->nextNode;
		}

		return nullptr;

	}
	
	/*
	This method prints a basic representation of the graph.
	*/
	void PrintGraph(){
		pNode graphHead;
		pEdge edgeHead;
		graphHead = head;

		if(nodeNumber == 0) std::cout<<"Grafo vacio"<<std::endl;
		
		else{
			
			while(graphHead != nullptr){
				std::cout<< graphHead-> ID<< " conections: "<<std::endl;
				edgeHead = graphHead->conection;
				
				while(edgeHead != nullptr){
					std::cout<< edgeHead->conectionData<< ", ";
					edgeHead = edgeHead->nextEdge;
				}
				
				std::cout<<std::endl;
				graphHead = graphHead->nextNode;
			}
		}			
	};

	/*
	This methos uses the Dijkstra algorithm to find the shortest path between two nodes.
	It returns a Graph with the shortest path tree.
	*/
	graph Dijkstra(int startNode, int endNode){
		std::vector<bool> visited(nodeNumber);
		std::vector<int> nearPath(nodeNumber);

		std::vector<pEdge> franja;

		int currentNode = startNode;

		//crea el spt
		graph SPT;
		for (int i = 0; i < this->nodeNumber; ++i){
			SPT.InsertNode();
		}

		//crea los visitados y los caminos minimos
		for (int i = 0; i < this->nodeNumber; i++){
			visited[i] = false;
			nearPath[i] = 2147483647;
		}

		//nodo de inicio
		nearPath[currentNode] = 0;

		while(currentNode != endNode){

			//agregar los edges de los nodos no visitados 
			pEdge nearEdges= this->SearchNodeByID(currentNode)->conection;
			while(nearEdges != nullptr){
				if(!visited[nearEdges->conectionData]){

					//pone las distancias tentativas
					if(nearPath[nearEdges->conectionData] > nearPath[currentNode] + nearEdges->weight){

						nearPath[nearEdges->conectionData] = nearPath[currentNode] + nearEdges->weight;
					}
					franja.push_back(nearEdges);
				}


				nearEdges = nearEdges->nextEdge;
			}

			
			visited[currentNode] = true;

			int minDistance = 2147483647;
			int nextNode;
			pEdge selectedEdge = nullptr;
			for (int i = 0; i < this->nodeNumber; ++i){
				if(!visited[i]){
					if(nearPath[i] < minDistance){
						nextNode = i;
						minDistance = nearPath[i];
					}
				}
			}
			for(pEdge edge : franja){
				if( nearPath[edge->from]+ edge->weight == nearPath[edge->conectionData] && nextNode == edge->conectionData){
					selectedEdge = edge;
					break;
					
				}
			}

			auto it = std::find(franja.begin(), franja.end(), selectedEdge);
			if(it != franja.end()){
				franja.erase(it);
			}

			SPT.InsertEdge(selectedEdge->from, selectedEdge->conectionData, selectedEdge->weight);
			currentNode = nextNode;

		}
		return SPT;
	};
};


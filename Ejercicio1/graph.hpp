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

private:
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

	int getFrom(){ return from; };
	int getConectionData(){ return conectionData; };
	int getWeight(){ return weight; };
	void setWeight(int nWeight){ weight = nWeight; };
	edge* getNextEdge(){ return nextEdge; };
	void setNextEdge(edge* nEdge){ nextEdge = nEdge; };

};
typedef edge* pEdge;

/*
This class contains all the information of the node:
the ID of the node,
the data of the node,
a pointer to the first edge that comes out of the node,
*/
class node{
private:
	int ID;
	int nodeData;
	edge* conection;
	node* nextNode;

public:
	node(){
		this->conection = nullptr;
	};

	node(int ID) : node(){
		this->ID = ID;
	}

	node(int ID, int data) : node(ID){
		this->nodeData = data;
	};

	int getID(){ return ID; };
	int getNodeData(){ return nodeData; };
	void setNodeData(int nData){ nodeData = nData; };
	edge* getConection(){ return conection; };
	void setConection(edge* nConection){ conection = nConection; };
	node* getNextNode(){ return nextNode; };
	void setNextNode(node* nNode){ nextNode = nNode; };
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
			edgeHead = graphHead->getConection();
			
			while(edgeHead!=nullptr){
				edgeAuxiliar = edgeHead;
				edgeHead = edgeHead->getNextEdge();

				delete edgeAuxiliar;
			}
			
			nodeAuxiliar = graphHead;
			graphHead = graphHead->getNextNode();

			delete nodeAuxiliar;
		}
	};
	
	/*
	This method inserts a node into the graph using the next ID info stored in the graph.
	*/
	void InsertNode(){
		pNode newNode;
		newNode = new node(nodeID);
		
		newNode->setNextNode(head);
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
		edgeHead = nodeX->getConection();
		while (edgeHead != nullptr) {
			if (edgeHead->getConectionData() == IDy) {
				std::cout << "the Edge already exists" << std::endl;
				return;
			}
			edgeHead = edgeHead->getNextEdge();
		};

		//Inserting for X
		edgeHead = new edge(IDx, IDy);
		edgeHead->setNextEdge(nodeX->getConection());
		nodeX->setConection(edgeHead);

		//cheking for Y
		edgeHead = nodeY->getConection();
		while (edgeHead != nullptr) {
			if (edgeHead->getConectionData() == IDx) {
				std::cout << "the Edge already exists" << std::endl;
				return;
			}
			edgeHead = edgeHead->getNextEdge();
		};

		//Inserting for Y
		edgeHead = new edge(IDy, IDx);
		edgeHead->setNextEdge(nodeY->getConection());
		nodeY->setConection(edgeHead);
		
	};

	/*
	This method inserts a edge between two nodes in the graph with a weight.
	*/
	void InsertEdge(int IDx, int IDy, int npeso){
		InsertEdge(IDx, IDy);
		
		pEdge edgeHead;

		pNode nodeX = SearchNodeByID(IDx);
		pNode nodeY = SearchNodeByID(IDy);

		edgeHead = nodeX->getConection();
		while(edgeHead != nullptr){
			if(edgeHead->getConectionData() == IDy){
				edgeHead->setWeight(npeso);
				break;
			}
			edgeHead = edgeHead->getNextEdge();
		}

		edgeHead = nodeY->getConection();
		while(edgeHead != nullptr){
			if(edgeHead->getConectionData() == IDx){
				edgeHead->setWeight(npeso);
				break;
			}
			edgeHead = edgeHead->getNextEdge();
		}
	};

	/*
	This method searches for a node in the graph by its ID.
	*/
	pNode SearchNodeByID(int IDnode){
		pNode graphHead;
		graphHead = head;

		while(graphHead != nullptr){
			if(graphHead->getID() == IDnode)
				return graphHead;
			graphHead = graphHead->getNextNode();
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
				std::cout<< graphHead->getID()<< " conections: "<<std::endl;
				edgeHead = graphHead->getConection();
				
				while(edgeHead != nullptr){
					std::cout<< edgeHead->getConectionData()<< ", ";
					edgeHead = edgeHead->getNextEdge();
				}
				
				std::cout<<std::endl;
				graphHead = graphHead->getNextNode();
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
			pEdge nearEdges= this->SearchNodeByID(currentNode)->getConection();
			while(nearEdges != nullptr){
				if(!visited[nearEdges->getConectionData()]){

					//pone las distancias tentativas
					if(nearPath[nearEdges->getConectionData()] > nearPath[currentNode] + nearEdges->getWeight()){

						nearPath[nearEdges->getConectionData()] = nearPath[currentNode] + nearEdges->getWeight();
					}
					franja.push_back(nearEdges);
				}


				nearEdges = nearEdges->getNextEdge();
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
				if( nearPath[edge->getFrom()]+ edge->getWeight() == nearPath[edge->getConectionData()] && nextNode == edge->getConectionData()){
					selectedEdge = edge;
					break;
					
				}
			}

			auto it = std::find(franja.begin(), franja.end(), selectedEdge);
			if(it != franja.end()){
				franja.erase(it);
			}

			SPT.InsertEdge(selectedEdge->getFrom(), selectedEdge->getConectionData(), selectedEdge->getWeight());
			currentNode = nextNode;

		}
		return SPT;
	};
};


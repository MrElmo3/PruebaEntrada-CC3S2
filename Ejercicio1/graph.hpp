#include <iostream>
#include <queue>
#include <vector>

struct edge{
	int from;
	int conectionData;
	int weight;
	edge* nextEdge;

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
typedef edge *pEdge;


struct node{
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


class graph{
private:

	int nodeID = 0;

	pNode head;

	int nodeNumber;
	int edgeNumer;

public:

	graph(){
		head=nullptr;
		nodeNumber = 0;
		edgeNumer = 0;
	};
	
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
	
	void InsertNode(){
		pNode newNode;
		newNode = new node(nodeID);
		
		newNode->nextNode = head;
		head = newNode;

		nodeID++;
		nodeNumber++;
	};
	
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

	graph Dijkstra(int startNode){
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

		while(currentNode != -1){

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
			bool flag = true;
			pEdge selectedEdge = nullptr;
			for (int i = 0; i < this->nodeNumber; ++i){
				if(!visited[i]){
					flag = false;
					if(nearPath[i] < minDistance){
						nextNode = i;
						minDistance = nearPath[i];
					}
				}
			}

			if(flag){
				currentNode = -1;
			}
			else{
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

			SPT.PrintGraph();
			std::cout<<"a";
		}
		return SPT;
	};
};


#include <algorithm>
#include <cstdlib>
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
		pNode graphHead;
		pEdge newEdge;
		graphHead = head;
		
		if(nodeNumber <= 1){
			std::cout<<"graph is empty or only have 1 node"<<std::endl;
			
			return;
		}

		while(graphHead != nullptr){
			
			if(graphHead->ID == IDx || graphHead->ID == IDy){
				
				pEdge edgeHead = graphHead->conection;

				while(edgeHead != nullptr){
					if(edgeHead->conectionData == IDx ||
						edgeHead->conectionData == IDy ){

						std::cout<<"the edge already exists"<<std::endl;
						return;
					}
					edgeHead = edgeHead->nextEdge;
				}
				

				newEdge = new edge(graphHead->ID == IDx? IDx: IDy, graphHead->ID == IDx? IDy: IDx);

				newEdge -> nextEdge = graphHead->conection;
				graphHead->conection = newEdge;
			}
			graphHead = graphHead->nextNode;
		}
	};

	void InsertEdge(int IDx, int IDy, int npeso){
		pNode graphHead;
		pEdge newEdge;
		graphHead = head;
		
		if(nodeNumber <= 1){
			std::cout<<"graph is empty or only have 1 node"<<std::endl;
			return;
		}

		while(graphHead != nullptr){
			
			if(graphHead->ID == IDx || graphHead->ID == IDy){
				
				pEdge edgeHead = graphHead->conection;

				while(edgeHead != nullptr){
					if(edgeHead->conectionData == IDx ||
						edgeHead->conectionData == IDy ){
						
						std::cout<<"the edge already exists"<<std::endl;
						return;
					}
					edgeHead = edgeHead->nextEdge;
				}
				

				newEdge = new edge(graphHead->ID == IDx? IDx: IDy, graphHead->ID == IDx? IDy: IDx, npeso);

				newEdge -> nextEdge = graphHead->conection;
				graphHead->conection = newEdge;
			}
			graphHead = graphHead->nextNode;
		}
	};

	void InsertDirigedEdge(int from, int to, int weight){
		pNode graphHead;
		pEdge newEdge;
		graphHead = head;
		
		if(nodeNumber <= 1){
			std::cout<<"graph is empty or only have 1 node"<<std::endl;
			return;
		}
		while(graphHead != nullptr){
			if(graphHead->ID == from){
				newEdge = new edge(from, to, weight);
				newEdge -> nextEdge = graphHead->conection;
				graphHead->conection = newEdge;
			}
			graphHead = graphHead->nextNode;
		}
	}

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
				currentNode =nextNode;
			}

			SPT.PrintGraph();
			std::cout<<"a";
		}
		return SPT;
	};
};


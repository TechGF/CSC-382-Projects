//Gary Feng
//CSC 382 Project 5
//Professor Louis Petingi
//main.cpp
#include <iostream>
using namespace std;

struct node {
	int vertex;
	node* next;
};
bool* Visited;
bool cycles = false;
class Graph {
private:
	int n; //number of vertices
	int e; //number of edges
	node* headnodes;
public:
	Graph(int nodes) //constructor
	{
		n = nodes;
		headnodes = new node[n]; //headnodes is an array of nodes
		for (int i = 0; i < n; i++) {
			headnodes[i].vertex = i;
			headnodes[i].next = 0;
		}
	}

	void create() {
		int v1, v2;
		cout << "Enter number of edges: ";
		cin >> e;
		for (int i = 0; i < e; i++) {
			cout << "Enter number of vertices to connect from (0-" << n - 1 << "): ";
			cin >> v1 >> v2;
			addEdge(v1, v2);
			addEdge(v2, v1);
		}
	}

	void addEdge(int v1, int v2) {
		node* newNode = new node;
		newNode->vertex = v2;
		newNode->next = headnodes[v1].next;
		headnodes[v1].next = newNode;
	}

	void DFS(int father, int v)
	{
		Visited[v] = true;
		node* adjnode = headnodes[v].next;
		while (adjnode) // visit all vertices adjacent to v
		{
			if (!Visited[adjnode->vertex]) //if adjacent vertex to v was not visited previously
				DFS(v, adjnode->vertex); // when we call DFS, we pass the father vertex of the call
			else if (father != adjnode->vertex) // if the vertex adjacent to v is not the father, we have a cycle
			{
				cycles = true;
			}
			adjnode = adjnode->next;
		}
	}

	void printGraph() {
		node* tempNode = new node;
		cout << "Cycle: ";
		for (int i = 0; i < n; i++) {
			tempNode = &headnodes[i];
			cout << "( ";
			while (tempNode != NULL) {
				cout << tempNode->vertex << ' ';
				tempNode = tempNode->next;
			}
			cout << ")  ";
		}
		cout << endl;
	}
};

int main() {
	int n;
	cout << "Enter number of vertices: ";
	cin >> n;
	Visited = new bool[n];
	int Nmbrcmpnts = 0; //we initialize the counter for the number of components
	Graph G(n); // constructor
	G.create(); // to create graph, that is the linked-list
	G.printGraph();
	for (int i = 0; i < n; i++)
		Visited[i] = false;
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			if (!Visited[k]) {
				G.DFS(0, k);
				Nmbrcmpnts++;
			}
		}
	}

	if (cycles) {
		cout << "Graph contains cycle" << endl;
	}
	else {
		cout << "Graph doesn't contain cycle" << endl;
	}
	cout << "Number of connected components: " << Nmbrcmpnts << endl;

	return 0;
}
#include <iostream>
#include <queue>
#include <cmath>

#define Max 200

using namespace std;

struct Edge{
	int v, w;
	friend istream& operator>>(istream& is, Edge& edge){
		is >> edge.v >> edge.w;
		return is;
	}
};

struct Coor{
	int x, y;
	friend istream& operator>>(istream& is, Coor& coor){
		is >> coor.x >> coor.y;
		return is;
	}
	inline int operator-(Coor& coor2){
		return (x - coor2.x)*(x - coor2.x) + (y - coor2.y)*(y - coor2.y);
	}
};

struct Node{
	int No;
	Node* next = nullptr;
};

struct Graph{
	int nVertex;
	int nEdge;
	Node index[Max];
	Graph() { for (int i = 0; i < Max; ++i) index[i].No = i; }
};

void createGraph(Graph&, int, int, Coor*);
void insert(Graph&, Edge&);
void DFS(int*, Graph&, int, int*, int& flag);
void disToBank(Coor* coor, int D, int* toBank, int i){

	int dis = abs(coor[i].x) > abs(coor[i].y) ? (50 - abs(coor[i].x)) : (50 - abs(coor[i].y));
	if (dis > D) toBank[i] = 0;
	else toBank[i] = 1;
}

int main(){

	int N, D;

	cin >> N >> D;

	Coor coor[Max];
	int toBank[Max];

	toBank[0] = 0;

	coor[0].x = 0, coor[0].y = 0;
	for (int i = 1; i <= N; ++i) {
		cin >> coor[i];
		disToBank(coor, D, toBank, i);
	}

	//for (int i = 0; i <= N; ++i) cout << toBank[i] << endl;

	Graph graph;

	createGraph(graph, N, D, coor);
	/*
		Node* node = &graph.index[1];
		while (node){
		cout << node->No << endl;
		node = node->next;

		}
		cout << "dfdsafds" << endl;
		cin.get();
		*/

	int* visited = new int[graph.nVertex];

	for (int i = 0; i < graph.nVertex; ++i) visited[i] = 0;


	int flag = 0;

	visited[0] = 1;
	DFS(visited, graph, 0, toBank, flag);
	if (flag)
		cout << "Yes";

	else cout << "No";

}

void createGraph(Graph& graph, int N, int D, Coor* coor){

	graph.nVertex = N + 1;
	int nEdge = 0;

	Edge edge;

	for (int i = 1; i <= N; ++i){
		if ((coor[i] - coor[0]) <= (D + 7.5)*(D + 7.5))	{
			edge.v = 0, edge.w = i;
			insert(graph, edge);
			nEdge++;
		}
	}

	for (int i = 1; i < N; ++i){
		for (int j = i + 1; j <= N; ++j){
			if ((coor[i] - coor[j]) <= D*D)	 {
				edge.v = i, edge.w = j;
				insert(graph, edge);
				nEdge++;
			}
		}
	}
	graph.nEdge = nEdge;

}

void insert(Graph& graph, Edge& edge){

	Node* g = &graph.index[edge.v];
	while (g->next)  g = g->next;
	g->next = new Node;
	g->next->No = edge.w;

	g = &graph.index[edge.w];
	while (g->next)  g = g->next;
	g->next = new Node;
	g->next->No = edge.v;

}

void DFS(int*visited, Graph& graph, int No, int* toBank, int& flag){

	if (toBank[No]) {
		flag = 1;
		//	cout << No<<toBank[No]<<"flag=1" << endl;
		return;
	}

	Node* node = graph.index[No].next;

	while (node)	{
		if (!visited[node->No]){
			visited[node->No] = 1;
			DFS(visited, graph, node->No, toBank, flag);
		}
		node = node->next;
	}
}


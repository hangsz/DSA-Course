#include <iostream>
#include <queue>
#include<stack>
#include <cmath>

#define Max 110

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
void BFS(Graph&,int*, int*,Coor*, int, int*, int& flag);

void disToBank(Coor* coor, int D, int* toBank, int i){

	int dis = abs(coor[i].x) > abs(coor[i].y) ? (50 - abs(coor[i].x)) : (50 - abs(coor[i].y));
	if (dis > D) toBank[i] = 0;
	else toBank[i] = 1;
}

int firstJump(int* path, Coor* coor, int N);

int main(){

	int N, D;

	cin >> N >> D;

	Coor coor[Max];
	int toBank[Max];

	toBank[0] = 0;

	coor[0].x = 0, coor[0].y = 0;
	disToBank(coor, D, toBank, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> coor[i];
		disToBank(coor, D, toBank, i);
	}

	//for (int i = 0; i <= N; ++i) cout << toBank[i] << endl;

	Graph graph;

	createGraph(graph, N, D, coor);
	
	/*Node* node = &graph.index[0];
	while (node){
	cout << node->No << '\t';
	node = node->next;

	}
	cout << "dfdsafds" << endl;
	cin.get();*/
	

	int dist[Max];
	int path[Max];

	for (int i = 0; i < Max; ++i) {
		dist[i] = -1;
		path[i] = -1;	
	}
	int flag = -1;


	BFS( graph,dist,path,coor,0, toBank, flag);
	if (flag != -1){
		cout << dist[flag]+1 << endl;
		stack<int> istk;
		int N = flag;
		while (path[N] != -1){
			istk.push(N);
			N = path[N];
		}
		
		while (!istk.empty()) {
			N = istk.top();
			istk.pop();
			cout << coor[N].x <<' '<< coor[N].y << endl;
		}
	}
	else cout <<'0';

}

void createGraph(Graph& graph, int N, int D, Coor* coor){

	graph.nVertex = N + 1;
	Edge edge;

	for (int i = 1; i <= N; ++i){
		if ((coor[i] - coor[0]) <= (D + 7.5)*(D + 7.5))	{
			edge.v = 0, edge.w = i;
			insert(graph, edge);
		
		}
	}
	for (int i = 1; i < N; ++i){
		for (int j = i + 1; j <= N; ++j){
			if ((coor[i] - coor[j]) <= D*D)	 {
				edge.v = i, edge.w = j;
				insert(graph, edge);
			}
		}
	}
	

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

void BFS( Graph& graph,int*dist,int* path,Coor* coor, int No, int* toBank, int& flag){

	queue<int> ique;
	ique.push(No);

	dist[No] = 0;
	
	int N;

	int length = 65535;	 
	int first = 65535;

	int firstTemp;
						 
	Node* node;

	while (!ique.empty()){
		N = ique.front();
		ique.pop();	
		

		if (toBank[N]) {
			if (dist[N] == 0)  {
				flag = N; 
				break;
			}
			else{
				if (dist[N] <= length)  {
					if (dist[N] < length){
						flag = N;
						length = dist[N];
						first = firstJump(path, coor, N);
					}
					else{
						firstTemp = firstJump(path, coor, N);
						if (firstTemp < first){
							flag = N;
							length = dist[N];
							first = firstTemp;
						}
					}
				}
			}
		}
		node = graph.index[N].next;
		while (node){
			if (dist[node->No] ==-1) {
				ique.push(node->No);
				dist[node->No] = dist[N]+1;
				path[node->No] = N;	
			}
			node = node->next;
		}
	}
}

int firstJump(int* path,Coor* coor, int N){
	while (path[N] != 0)
		N = path[N];

	return (coor[N] - coor[0]);
}


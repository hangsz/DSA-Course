#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip>

#define Max 10000

using namespace std;

struct Edge{
	int v, w;
	friend istream& operator>>(istream& is, Edge& edge){
		is >> edge.v >> edge.w;
		return is;
	}
};

struct Node{
	int No;
	int dis = 0;
	Node* next = nullptr;
};

struct Graph{
	int nVertex;
	int nEdge;
	Node index[Max];
	Graph() { for (int i = 0; i < Max; ++i) index[i].No = i; }
};

void createGraph(Graph&, int, int);
void insert(Graph&, Edge&);
void BFS(int*, Graph&, int,int&);


int main(){

	int N, M;

	cin >> N >> M;

	Graph graph;

	createGraph(graph, N, M);
	
	/*Node* node = &graph.index[7];
	while (node){
	cout << node->No << endl;
	node = node->next;

	}
	cout << "dfdsafds" << endl;
	cin.get();*/
	

	int* visited = new int[graph.nVertex];

	int sum;
	for (int i = 0; i < N; ++i){
		sum = 0; 
		graph.index[i].dis = 0;

		for (int j = 0; j < N; ++j)   visited[j] = 0;

		visited[i] = 1;

		BFS(visited, graph, i, sum);
		cout << i+1 << ": " << setiosflags(ios::fixed) << setprecision(2)  << sum *100 / double(N) << "%" << endl;  
	}
}

void createGraph(Graph& graph, int N, int M){

	graph.nVertex = N;
	graph.nEdge = M;
	int nEdge = 0;
	Edge edge;

	for (int i = 0; i < M; ++i){
		cin >> edge;
		edge.v--; edge.w--;
		insert(graph, edge);
		nEdge++;
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


void BFS(int* visited, Graph& graph, int No, int& sum){

	queue<int>  que;
	que.push(No);

	visited[No] = 1;

	int N,dis;

	Node* node;

	while (!que.empty()){
		N = que.front();  
		que.pop();	
		if ( graph.index[N].dis < 7)  sum++;
		dis = graph.index[N].dis;
		node = graph.index[N].next;	  
		
		while (node)	{
			if (!visited[node->No]){
				visited[node->No] = 1;
				graph.index[node->No].dis = dis + 1;
				que.push(node->No);
			}
			node = node->next;
		}
	}

}


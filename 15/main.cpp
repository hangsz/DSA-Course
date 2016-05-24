#include <iostream>
#include <queue>

#define Max 10

using namespace std;

struct Edge{
	int v, w;
	friend istream& operator>>(istream& is, Edge& edge){
		is >> edge.v >> edge.w;
		return is;
	}
};

struct Node{
	int No ;	
	Node* next = nullptr;
};

struct Graph{
	int nVertex;
	int nEdge;
	Node index[Max] ;
	Graph() { for(int i = 0; i < Max; ++i) index[i].No = i ; }
};

void createGraph(Graph& );
void insert(Graph& ,Edge&  );
void DFS(int*,Graph&,int,queue<int>& );
void BFS(int*,Graph&,int,queue<int>& );

int main(){

	Graph graph;

	createGraph(graph);

	/*Node* node = &graph.index[5];
	while (node){
	cout << node->No << endl;
	node = node->next;

	}


	cout << "dfdsafds" << endl;
	cin.get();*/
	
											
	int* visited = new int[graph.nVertex];	 
	queue<int> ique;
	for (int i = 0; i < graph.nVertex; ++i) visited[i] = 0;


	for (int i = 0; i < graph.nVertex; ++i){
		if (!visited[i]) {
			visited[i] = 1;
			DFS(visited, graph, i, ique);
			 
			int size = ique.size();

			if (size == 0) continue;
			cout << "{ ";
			for (int i = 0; i < size; ++i){
				cout << ique.front() << " ";
				ique.pop();
			}
			cout << "}" << endl;
		}
	}


	for (int i = 0; i < graph.nVertex; ++i) visited[i] = 0;
	
	for (int i = 0; i < graph.nVertex; ++i){
		if (!visited[i]){
			visited[i] = 1;
			BFS(visited,graph,i,ique);
		}

		int size = ique.size();
		if (size == 0) continue;
		cout << "{ ";
		for (int i = 0; i < size; ++i){
			cout << ique.front() << " ";
			ique.pop();
		}
		cout << "}" << endl;
	}
	
}

void createGraph(Graph& graph){
	int N, E;
	cin >> N >> E;
	graph.nVertex = N;
    graph.nEdge = E;

	Edge edge;
	for (int i = 0; i < E; ++i){
		cin >> edge;
		insert(graph, edge);
	}
  
}

void insert(Graph& graph, Edge& edge){

		Node* g1 = &graph.index[edge.v];

		if (!g1->next) 	 {
			g1->next = new Node;
			g1->next->No = edge.w;
		}
		else{
			g1 = g1->next;
			while (g1->next && g1->next->No < edge.w)  g1 = g1->next;

			if (!g1->next){
				g1->next = new Node;
				if (g1->No < edge.w)  g1->next->No = edge.w;
				else  {
					g1->next->No = g1->No;
					g1->No = edge.w;
				}
			}
			else{
				Node *p1 = new Node;
				p1->No = edge.w;
				p1->next = g1->next;
				g1->next = p1;
			}
		}
	
		Node* g2 = &graph.index[edge.w];
		if (!g2->next) 	 {
			g2->next = new Node;
		    g2->next->No = edge.v;
		}
		else{

			g2 = g2->next;
			while (g2->next && g2->next->No < edge.v)  g2 = g2->next;

			if (!g2->next){
				g2->next = new Node;
				if (g2->No < edge.v)  g2->next->No = edge.v;
				else  {
					g2->next->No = g2->No;
					g2->No = edge.v;
				}
			}
			else{
				Node *p2 = new Node;
				p2->No = edge.v;
				p2->next = g2->next;
				g2->next = p2;
			}
		}
}

void DFS(int*visited,Graph& graph,int No,queue<int>& ique){
	
	ique.push(No);
	Node* node = graph.index[No].next;

	while( node)	{
		if (!visited[node->No]){
			visited[node->No]=1;
			DFS(visited,graph,node->No,ique);	
		}	
		node = node->next;
	}
}

void BFS(int* visited, Graph& graph, int No, queue<int>& ique){

	queue<int> que;

	que.push(No);

	visited[No] = 1;

	int N;

	Node* node;

	while (!que.empty()	){
		N = que.front();
		que.pop();		
		ique.push(N);

		node = graph.index[N].next;
		while (node)	{
			if (!visited[node->No]){
				visited[node->No] = 1;
				que.push(node->No);	 
			}	
			node = node->next;
		}
	}

}
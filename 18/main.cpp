#include<iostream>

#define Max 200
#define Infinity 65535

using namespace std;


struct Edge{
	int v, w;
	int weight;

	friend istream& operator>>(istream& is, Edge& edge){
		is >> edge.v >> edge.w >> edge.weight;
		return is;
	}
};

struct Mgraph{
	int nv;
	int ne;
	int weight[Max][Max];
};


Mgraph* createGraph(int nv);
void insert(Mgraph* graph, Edge& edge);

void Floyd(Mgraph* graph, int D[][Max] );

int main(){

	int N, M;
	cin >> N >> M;

	Mgraph* graph = createGraph(N);
	Edge edge;
	for (int i = 0; i < M; ++i){
		cin >> edge;
		--edge.v; --edge.w;
		insert(graph, edge);
	}						
	
	int D[Max][Max];

	Floyd(graph, D);

	
	int minDist = Infinity;
	int Animal = 0;
	int maxDist;

	for (int i = 0; i < N; ++i){
		maxDist = 0;
		for (int j = 0; j < N; ++j)	   
			if ( i!=j && D[i][j] > maxDist)  maxDist = D[i][j];

		if (maxDist != Infinity && maxDist< minDist) {
			minDist = maxDist;
			Animal = i + 1;
		}
	}

	if (Animal == 0) cout << 0;
	else cout << Animal << ' ' << minDist;

}

Mgraph* createGraph(int nv){

	Mgraph* graph = new Mgraph;
	graph->nv = nv;
	graph->ne = 0;

	for (int v = 0; v < nv; ++v)	  
		for (int w = 0; w < nv; ++w)
			graph->weight[v][w] = Infinity;
	return graph;

}

void insert(Mgraph* graph, Edge& edge)  {

	graph->ne += 2;
	graph->weight[edge.v][edge.w] = edge.weight;
	graph->weight[edge.w][edge.v] = edge.weight;
}

void Floyd(Mgraph* graph, int D[][Max] ){
	int i, j, k;
	int N = graph->nv;
	for (i = 0; i < graph->nv; ++i)
	for (j = 0; j < graph->nv; ++j)	 
		D[i][j] = graph->weight[i][j];

	for (k = 0; k < graph->nv; ++k)
	for (i = 0; i < graph->nv; ++i)
	for (j = 0; j < graph->nv; ++j)
	if ( D[i][k] + D[k][j] < D[i][j]  )
		D[i][j] = D[i][k] + D[k][j];

	
}
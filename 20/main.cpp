#include<iostream>

#define Max 600

#define Infinity 65535
using namespace std;

struct Edge{
	int v, w;
	int length;
	int fare;
	friend istream& operator>>(istream& is, Edge& edge){
		is >> edge.v >> edge.w >> edge.length >> edge.fare;
		return is;
	}
};

struct Mgraph {
	int nv;
	int ne;
	int length[Max][Max];
	int fare[Max][Max];
};

Mgraph* createGraph(int N, int M);
void insert( Mgraph* graph, Edge& edge);
int FindMinDist(Mgraph* graph, int dist[], int collected[]);
void Dijkstra(Mgraph* graph, int S,int D);

int main(){
	int N, M, S, D;

	cin >> N >> M >> S >> D;

	Mgraph* graph = createGraph(N, M);

	Edge edge;
	for (int i = 0; i < M; ++i){
		cin >> edge;
		insert( graph, edge );
	}


	Dijkstra(graph,S,D);


}

Mgraph* createGraph(int N, int M){
	Mgraph* graph = new Mgraph;

	graph->nv = N;
	graph->ne = M;
	for (int i = 0; i < N;++i)
	for (int j = 0; j < N; ++j)	 {
		graph->length[i][j] = Infinity;
		graph->fare[i][j] = Infinity;
	}
	return graph;
}

void insert(Mgraph* graph, Edge& edge){

	graph->length[edge.v][edge.w] = edge.length;
	graph->fare[edge.v][edge.w] = edge.fare;

	graph->length[edge.w][edge.v] = edge.length;
	graph->fare[edge.w][edge.v] = edge.fare;
}




/* 邻接矩阵存储 - 有权图的单源最短路算法 */
int FindMinDist(Mgraph* graph, int dist[], int collected[])
{ /* 返回未被收录顶点中dist最小者 */
	int minV, V;
	int minDist = Infinity;

	for (V = 0; V < graph->nv; V++) {
		if (collected[V] == 0 && dist[V] < minDist) {
			/* 若V未被收录，且dist[V]更小 */
			minDist = dist[V]; /* 更新最小距离 */
			minV = V; /* 更新对应顶点 */
		}
	}
	if (minDist < Infinity) /* 若找到最小dist */
		return minV;     /* 返回对应的顶点下标 */
	else return -1;      /* 若这样的顶点不存在，返回错误标记 */
}

void Dijkstra(Mgraph* graph, int S,int D)
{

	int dist[Max];

	int path[Max];

	int collected[Max];

	int fare[Max];

	int V, W;

	/* 初始化：此处默认邻接矩阵中不存在的边用Infinity表示 */
	for (V = 0; V < graph->nv; V++) {
		dist[V] = graph->length[S][V];
		if (dist[V]< Infinity ) 	path[V] = S;
		else path[V] = -1;

		collected[V] = 0;
		fare[V] = 0;	   //
	}
	/* 先将起点收入集合 */
	dist[S] = 0;
	collected[S] = 1;
	fare[S] = 0;

	while (1) {
		/* V = 未被收录顶点中dist最小者 */
		V = FindMinDist(graph, dist, collected);
		if (V == -1)   break;    /* 若这样的V不存在 */ /* 算法结束 */
			    
		collected[V] = 1;  /* 收录V */
		fare[V] = fare[path[V]] + graph->fare[path[V]][V];

		if (V == D) break;

		for (W = 0; W < graph->nv; W++) /* 对图中的每个顶点W */	  {
			/* 若W是V的邻接点并且未被收录 */
			if (collected[W] == 0 && graph->length[V][W] < Infinity) {
				//if ( graph->length[V][W] < 0) /* 若有负边 */
				//	return false; /* 不能正确解决，返回错误标记 */
				/* 若收录V使得dist[W]变小 */
				if (dist[V] + graph->length[V][W] <= dist[W]) {
					if (dist[V] + graph->length[V][W] < dist[W]) {
						dist[W] = dist[V] + graph->length[V][W]; /* 更新dist[W] */
						path[W] = V; /* 更新S到W的路径 */
					}
					else{
						if ( fare[V] + graph->fare[V][W] < fare[path[W]] + graph->fare[path[W]][W] ){
							dist[W] = dist[V] + graph->length[V][W]; /* 更新dist[W] */
							path[W] = V; /* 更新S到W的路径 */
						}
					}
				}
				
			}
		}
	} /* while结束*/
	//return 1; /* 算法执行完毕，返回正确标记 */

	cout << dist[D] << ' ' << fare[D];

}
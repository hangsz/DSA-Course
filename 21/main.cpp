#include<iostream>

#define Max 1010
#define Infinity 65535

using namespace std;


struct Edge{
	int v, w;
	int cost;
	friend istream& operator>>(istream& is, Edge& edge){
		is >> edge.v >> edge.w>>edge.cost;
		return is;
	}
};
struct Mgraph{
	int nv;
	int ne;
	int cost[Max][Max];
};

struct Lnode{
	int no;
	int cost;
	Lnode* next;
};

struct Lgraph{
	int nv;
	int ne;
	Lnode node[Max];
};


Mgraph* createMgraph(int N, int M);
Lgraph* createLgraph(int N, int M);
void insertM(Mgraph* mgraph, Edge& edge);
void insertL(Lgraph* lgraph, Edge& edge);
int findMin(Mgraph* mgraph, int* dist);

int prim(Mgraph* mgraph, Lgraph* lgraph);

int main(){
	int N, M;
	cin >> N >> M;
	Mgraph* mgraph = createMgraph(N, M);
	Edge edge;
	for (int i = 0; i < M; ++i){
		cin >> edge;
		edge.v--; edge.w--;
		insertM(mgraph, edge);
	}

	Lgraph* lgraph = nullptr;

	int cost = prim(mgraph, lgraph);
	cout << cost;
	

}

Mgraph* createMgraph(int N, int M){
	Mgraph* mgraph = new Mgraph;

	mgraph->nv = N;
	mgraph->ne = M;
	for (int i = 0; i < N; ++i)
	for (int j = 0; j < N; ++j)
		mgraph->cost[i][j] = Infinity;

	return mgraph;
}

Lgraph* createLgraph(int N, int M){
	Lgraph* lgraph = new Lgraph;
	lgraph->nv = N;
	lgraph->ne = M;
	for (int i = 0; i < N; ++i)	  {
		lgraph->node[i].no = i;
		lgraph->node[i].cost = 0;
		lgraph->node[i].next = nullptr;
	}

	return lgraph;
}
void insertM(Mgraph* mgraph, Edge& edge){

	mgraph->cost[edge.v][edge.w] = edge.cost;
	mgraph->cost[edge.w][edge.v] = edge.cost;

}
void insertL(Lgraph* lgraph, Edge& edge){

	Lnode* node = &lgraph->node[edge.v];
	while (node->next) node = node->next;

	node = new Lnode;
	node->no = edge.w;
	node->cost = edge.cost;


	node = &lgraph->node[edge.w];
	while (node->next) node = node->next;

	node = new Lnode;
	node->no = edge.v;
	node->cost = edge.cost;
}

int findMin(Mgraph* mgraph, int* dist){
	int minV, v;
	int minDist = Infinity;

	for (v = 0; v < mgraph->nv; v++) {
		if (dist[v] != 0 && dist[v] < minDist) {
			/* 若V未被收录，且dist[V]更小 */
			minDist = dist[v]; /* 更新最小距离 */
			minV = v; /* 更新对应顶点 */
		}
	}
	if (minDist < Infinity) /* 若找到最小dist */
		return minV; /* 返回对应的顶点下标 */
	else return -1;  
}

int prim(Mgraph* mgraph, Lgraph* lgraph){

	lgraph =  createLgraph(mgraph->nv,mgraph->ne);

	int dist[Max],parent[Max];
	int total,vcount;

	int v, w;
	/* 初始化。默认初始点下标是0 */
	for (v = 0; v < mgraph->nv; v++) {
		/* 这里假设若V到W没有直接的边，则Graph->G[V][W]定义为INFINITY */
		dist[v] = mgraph->cost[0][v];
		parent[v] = 0; /* 暂且定义所有顶点的父结点都是初始点0 */
	}
	total = 0;       /* 初始化权重和     */
	vcount = 0;      /* 初始化收录的顶点数 */

	Edge edge;

	/* 将初始点0收录进MST */
	dist[0] = 0;
	vcount++;
	parent[0] = -1; /* 当前树根是0 */

	while (1) {
		v = findMin(mgraph, dist);
		/* V = 未被收录顶点中dist最小者 */
		if (v == -1) /* 若这样的V不存在 */
			break;   /* 算法结束 */

		/* 将V及相应的边<parent[V], V>收录进MST */
		edge.v = parent[v];
		edge.w = v;
		edge.cost = dist[v];
		insertL(lgraph, edge);

		total += dist[v];
		dist[v] = 0;
		vcount++;

		for (w = 0; w < mgraph->nv; w++) /* 对图中的每个顶点W */
		if (dist[w] != 0 && mgraph->cost[v][w] < Infinity) {
			/* 若W是V的邻接点并且未被收录 */
			if (mgraph->cost[v][w] < dist[w]) {
				/* 若收录V使得dist[W]变小 */
				dist[w] = mgraph->cost[v][w]; /* 更新dist[W] */
				parent[w] = v; /* 更新树 */
			}
		}
	} /* while结束*/

	if (vcount < mgraph->nv) /* MST中收的顶点不到|V|个 */
		total = -1;
	return total;   /* 算法执行完毕，返回最小权重和或错误标记 */

}
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
			/* ��Vδ����¼����dist[V]��С */
			minDist = dist[v]; /* ������С���� */
			minV = v; /* ���¶�Ӧ���� */
		}
	}
	if (minDist < Infinity) /* ���ҵ���Сdist */
		return minV; /* ���ض�Ӧ�Ķ����±� */
	else return -1;  
}

int prim(Mgraph* mgraph, Lgraph* lgraph){

	lgraph =  createLgraph(mgraph->nv,mgraph->ne);

	int dist[Max],parent[Max];
	int total,vcount;

	int v, w;
	/* ��ʼ����Ĭ�ϳ�ʼ���±���0 */
	for (v = 0; v < mgraph->nv; v++) {
		/* ���������V��Wû��ֱ�ӵıߣ���Graph->G[V][W]����ΪINFINITY */
		dist[v] = mgraph->cost[0][v];
		parent[v] = 0; /* ���Ҷ������ж���ĸ���㶼�ǳ�ʼ��0 */
	}
	total = 0;       /* ��ʼ��Ȩ�غ�     */
	vcount = 0;      /* ��ʼ����¼�Ķ����� */

	Edge edge;

	/* ����ʼ��0��¼��MST */
	dist[0] = 0;
	vcount++;
	parent[0] = -1; /* ��ǰ������0 */

	while (1) {
		v = findMin(mgraph, dist);
		/* V = δ����¼������dist��С�� */
		if (v == -1) /* ��������V������ */
			break;   /* �㷨���� */

		/* ��V����Ӧ�ı�<parent[V], V>��¼��MST */
		edge.v = parent[v];
		edge.w = v;
		edge.cost = dist[v];
		insertL(lgraph, edge);

		total += dist[v];
		dist[v] = 0;
		vcount++;

		for (w = 0; w < mgraph->nv; w++) /* ��ͼ�е�ÿ������W */
		if (dist[w] != 0 && mgraph->cost[v][w] < Infinity) {
			/* ��W��V���ڽӵ㲢��δ����¼ */
			if (mgraph->cost[v][w] < dist[w]) {
				/* ����¼Vʹ��dist[W]��С */
				dist[w] = mgraph->cost[v][w]; /* ����dist[W] */
				parent[w] = v; /* ������ */
			}
		}
	} /* while����*/

	if (vcount < mgraph->nv) /* MST���յĶ��㲻��|V|�� */
		total = -1;
	return total;   /* �㷨ִ����ϣ�������СȨ�غͻ������ */

}
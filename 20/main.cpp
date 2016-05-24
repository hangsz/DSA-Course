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




/* �ڽӾ���洢 - ��Ȩͼ�ĵ�Դ���·�㷨 */
int FindMinDist(Mgraph* graph, int dist[], int collected[])
{ /* ����δ����¼������dist��С�� */
	int minV, V;
	int minDist = Infinity;

	for (V = 0; V < graph->nv; V++) {
		if (collected[V] == 0 && dist[V] < minDist) {
			/* ��Vδ����¼����dist[V]��С */
			minDist = dist[V]; /* ������С���� */
			minV = V; /* ���¶�Ӧ���� */
		}
	}
	if (minDist < Infinity) /* ���ҵ���Сdist */
		return minV;     /* ���ض�Ӧ�Ķ����±� */
	else return -1;      /* �������Ķ��㲻���ڣ����ش����� */
}

void Dijkstra(Mgraph* graph, int S,int D)
{

	int dist[Max];

	int path[Max];

	int collected[Max];

	int fare[Max];

	int V, W;

	/* ��ʼ�����˴�Ĭ���ڽӾ����в����ڵı���Infinity��ʾ */
	for (V = 0; V < graph->nv; V++) {
		dist[V] = graph->length[S][V];
		if (dist[V]< Infinity ) 	path[V] = S;
		else path[V] = -1;

		collected[V] = 0;
		fare[V] = 0;	   //
	}
	/* �Ƚ�������뼯�� */
	dist[S] = 0;
	collected[S] = 1;
	fare[S] = 0;

	while (1) {
		/* V = δ����¼������dist��С�� */
		V = FindMinDist(graph, dist, collected);
		if (V == -1)   break;    /* ��������V������ */ /* �㷨���� */
			    
		collected[V] = 1;  /* ��¼V */
		fare[V] = fare[path[V]] + graph->fare[path[V]][V];

		if (V == D) break;

		for (W = 0; W < graph->nv; W++) /* ��ͼ�е�ÿ������W */	  {
			/* ��W��V���ڽӵ㲢��δ����¼ */
			if (collected[W] == 0 && graph->length[V][W] < Infinity) {
				//if ( graph->length[V][W] < 0) /* ���и��� */
				//	return false; /* ������ȷ��������ش����� */
				/* ����¼Vʹ��dist[W]��С */
				if (dist[V] + graph->length[V][W] <= dist[W]) {
					if (dist[V] + graph->length[V][W] < dist[W]) {
						dist[W] = dist[V] + graph->length[V][W]; /* ����dist[W] */
						path[W] = V; /* ����S��W��·�� */
					}
					else{
						if ( fare[V] + graph->fare[V][W] < fare[path[W]] + graph->fare[path[W]][W] ){
							dist[W] = dist[V] + graph->length[V][W]; /* ����dist[W] */
							path[W] = V; /* ����S��W��·�� */
						}
					}
				}
				
			}
		}
	} /* while����*/
	//return 1; /* �㷨ִ����ϣ�������ȷ��� */

	cout << dist[D] << ' ' << fare[D];

}
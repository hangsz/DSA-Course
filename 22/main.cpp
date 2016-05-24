#include <iostream>
#include <queue>

#define Max 110

using namespace std;

struct Edge{
	int v, w;
	int time;
	friend istream& operator>>(istream& is, Edge& edge) {
		is >> edge.v >> edge.w >> edge.time;
		return is;
	}
};


struct Lnode{
	int no;
	int time;
	Lnode* next = nullptr;
	
};

struct Lgraph{
	int nv;
	int ne;
	Lnode node[Max];
};

Lgraph* createLgraph(int N, int M);
void insertL(Lgraph* lgraph, Edge& edge);
int topSort(Lgraph* lgraph, int  topOrder[]);

int main(){

	int N, M;
	cin >> N >> M;		 
	
	Lgraph* lgraph = createLgraph(N, M);

	Edge edge;

	for (int i = 0; i < M; ++i){
		cin >> edge;
		//cout << edge.v<<edge.w<< endl;
		insertL(lgraph, edge);
	}

	Lnode* node = lgraph->node[0].next;

	//while (node){
	// //   cout << node->no ;
	//    node = node->next;

	//}

	//cout << "dfdsafds" << endl;
	//cin.get();


	int topOrder[Max];
	int minTime = topSort(lgraph, topOrder);
	if (minTime == -1) cout << "Impossible";
	else   cout << minTime;
}

Lgraph* createLgraph(int N, int M){
	Lgraph* lgraph = new Lgraph;
	lgraph->nv = N;
	lgraph->ne = M;
	for (int i = 0; i < N; ++i)	  {
		lgraph->node[i].no = i;
		lgraph->node[i].time = 0;
		lgraph->node[i].next = nullptr;
	}

	return lgraph;
}


void insertL(Lgraph* lgraph, Edge& edge){
	Lnode* node = &lgraph->node[edge.v];
	while (node->next) node = node->next;

	node->next = new Lnode;
	node->next->no = edge.w;
	node->next->time = edge.time;
}

/* 邻接表存储 - 拓扑排序算法 */

int topSort(Lgraph* lgraph, int  topOrder[])
{ /* 对lgraph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 */
	int inDegree[Max], cnt;
	int time[Max];
	int v;
	Lnode* w;
	queue<int> ique;

	/* 初始化inDegree[] */
	for (v = 0; v < lgraph->nv; v++)   {
		inDegree[v] = 0;
		time[v] = 0;
	}

	/* 遍历图，得到inDegree[] */
	for (v = 0; v < lgraph->nv; v++)
	for ( w = lgraph->node[v].next; w; w = w->next)
		inDegree[w->no]++;   /* 对有向边<v, w->no>累计终点的入度 */

	/* 将所有入度为0的顶点入列 */
	for (v = 0; v < lgraph->nv; v++)
	if (inDegree[v] == 0) {
	//	cout << v << endl;
		  ique.push(v);
	}
		
	

	/* 下面进入拓扑排序 */
	cnt = 0;
	while (!ique.empty()){
		v = ique.front(); /* 弹出一个入度为0的顶点 */
		ique.pop();
		topOrder[cnt++] = v; /* 将之存为结果序列的下一个元素 */
		/* 对v的每个邻接点w->AdjV */
		for (w = lgraph->node[v].next; w; w = w->next){
			time[w->no] = time[w->no] > (time[v] + w->time) ? time[w->no] : (time[v] + w->time);
			//cout << "w.no" << w->no << "w.time" << time[w->no] << endl;
			if (--inDegree[w->no] == 0)/* 若删除v使得w->no入度为0 */
				ique.push(w->no); /* 则该顶点入列 */
		}
	} /* while结束*/

	if (cnt != lgraph->nv)
		return -1; /* 说明图中有回路, 返回不成功标志 */
	else
	{
		int minTime=0;
		for (int i = 0; i < lgraph->nv; ++i)  {
		//	cout << time[i] << '\t';
			if (minTime < time[i])
				minTime = time[i];
		}
		return minTime;
	}
		
}
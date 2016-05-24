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

/* �ڽӱ�洢 - ���������㷨 */

int topSort(Lgraph* lgraph, int  topOrder[])
{ /* ��lgraph������������,  TopOrder[]˳��洢�����Ķ����±� */
	int inDegree[Max], cnt;
	int time[Max];
	int v;
	Lnode* w;
	queue<int> ique;

	/* ��ʼ��inDegree[] */
	for (v = 0; v < lgraph->nv; v++)   {
		inDegree[v] = 0;
		time[v] = 0;
	}

	/* ����ͼ���õ�inDegree[] */
	for (v = 0; v < lgraph->nv; v++)
	for ( w = lgraph->node[v].next; w; w = w->next)
		inDegree[w->no]++;   /* �������<v, w->no>�ۼ��յ����� */

	/* ���������Ϊ0�Ķ������� */
	for (v = 0; v < lgraph->nv; v++)
	if (inDegree[v] == 0) {
	//	cout << v << endl;
		  ique.push(v);
	}
		
	

	/* ��������������� */
	cnt = 0;
	while (!ique.empty()){
		v = ique.front(); /* ����һ�����Ϊ0�Ķ��� */
		ique.pop();
		topOrder[cnt++] = v; /* ��֮��Ϊ������е���һ��Ԫ�� */
		/* ��v��ÿ���ڽӵ�w->AdjV */
		for (w = lgraph->node[v].next; w; w = w->next){
			time[w->no] = time[w->no] > (time[v] + w->time) ? time[w->no] : (time[v] + w->time);
			//cout << "w.no" << w->no << "w.time" << time[w->no] << endl;
			if (--inDegree[w->no] == 0)/* ��ɾ��vʹ��w->no���Ϊ0 */
				ique.push(w->no); /* ��ö������� */
		}
	} /* while����*/

	if (cnt != lgraph->nv)
		return -1; /* ˵��ͼ���л�·, ���ز��ɹ���־ */
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
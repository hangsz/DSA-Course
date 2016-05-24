#include <iostream>
#include <queue>
#include <vector>
#include <utility>

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
int topSort(Lgraph* lgraph, int  topOrder[], int earTime[]);
int lastest(int start, Lgraph* lgraph, int last, int lasTime[] );
void keyAct(Lgraph* lgraph, int earTime[], int lasTime[],vector<pair<int,int>>& pvet );

int main(){

	int N, M;
	cin >> N >> M;

	Lgraph* lgraph = createLgraph(N, M);

	Edge edge;

	for (int i = 0; i < M; ++i){
		cin >> edge;
		edge.v--; edge.w--;
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
	int earTime[Max];
	int lasTime[Max];
	

	int last,minTime = 0;

	if (!topSort(lgraph, topOrder, earTime))	{
		cout << '0';
		return 0;
	}
	else
	{	  
		for (int i = 0; i < lgraph->nv; ++i)  {
			//	cout << earTime[i] << '\t';
			if (minTime < earTime[i])  {
				minTime = earTime[i];
				last = i;
			}
		}
		cout << minTime << endl;
	}
	for (int i = 0; i < N; ++i)  lasTime[i] = minTime;


	lastest( topOrder[0], lgraph, last, lasTime);
	
	vector<pair<int, int>> pvet;

	keyAct(lgraph, earTime, lasTime, pvet);
	for (int i = 0; i < pvet.size(); ++i){
		cout << pvet[i].first << "->" << pvet[i].second << endl;
	}
	

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

int topSort(Lgraph* lgraph, int  topOrder[], int earTime[])
{ /* ��lgraph������������,  TopOrder[]˳��洢�����Ķ����±� */
	int inDegree[Max], cnt;
	int v;
	Lnode* w;
	queue<int> ique;

	/* ��ʼ��inDegree[] */
	for (v = 0; v < lgraph->nv; v++)   {
		inDegree[v] = 0;
		earTime[v] = 0;
	}

	/* ����ͼ���õ�inDegree[] */
	for (v = 0; v < lgraph->nv; v++)
	for (w = lgraph->node[v].next; w; w = w->next)
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
			earTime[w->no] = earTime[w->no] > (earTime[v] + w->time) ? earTime[w->no] : (earTime[v] + w->time);
			//cout << "w.no" << w->no << "w.earTime" << earTime[w->no] << endl;
			if (--inDegree[w->no] == 0)/* ��ɾ��vʹ��w->no���Ϊ0 */
				ique.push(w->no); /* ��ö������� */
		}
	} /* while����*/

	if (cnt != lgraph->nv)  return 0; /* ˵��ͼ���л�·, ���ز��ɹ���־ */
	else return 1;
	

}

int lastest(int start, Lgraph* lgraph, int last, int lasTime[])	  {

	if (start == last)  return lasTime[last];

	Lnode* node = lgraph->node[start].next;
	int time = 0;
	while (node){
		time = lastest(node->no, lgraph, last, lasTime) - node->time;
		if (time < lasTime[start])
			lasTime[start] = time ;
		node = node->next;
	}

	return lasTime[start];
}

void keyAct(Lgraph* lgraph, int earTime[], int lasTime[], vector<pair<int, int>>& pvet){
	
	Lnode* node;
	pair<int, int> ipair;
	for (int i = 0; i < lgraph->nv; ++i){
		node = lgraph->node[i].next;
		while (node)   {
			if ( (lasTime[node->no] - earTime[i] - node->time) == 0){
				ipair = make_pair(i + 1, node->no + 1);
				pvet.push_back(ipair);
			}
			node = node->next;
		}
	}
}